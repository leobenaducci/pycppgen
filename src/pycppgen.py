import os
import pathlib
import sys
import clang.cindex
import re
import inspect
import itertools
import threading
import json
import contextvars
from typing import Final, Any
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass
from clang.cindex import CursorKind
from clang.cindex import AccessSpecifier

DebugMode = False

@dataclass(frozen=True, slots=True)
class _Kinds:
    Unknown: Final[str] = "kind_unknown"
    Namespace: Final[str] = "kind_namespace"
    Alias: Final[str] = "kind_alias"
    Enum: Final[str] = "kind_enum"
    EnumValue: Final[str] = "kind_enum_value"
    ClassTemplate: Final[str] = "kind_class_template"
    Class: Final[str] = "kind_class"
    Struct: Final[str] = "kind_struct"
    Function: Final[str] = "kind_function"
    Parameter: Final[str] = "kind_parameter"
    Variable: Final[str] = "kind_variable"
    FreeFunction: Final[str] = "kind_free_function"
    FreeVariable: Final[str] = "kind_free_variable"
    TemplateTypeParameter: Final[str] = "kind_template_type_parameter"
    TemplateNonTypeParameter: Final[str] = "kind_template_non_type_parameter"
    TemplateTemplateParameter: Final[str] = "kind_template_template_parameter"

@dataclass(frozen=True, slots=True)
class _NodeType:
    Name: Final[str] = "name"
    FullName: Final[str] = "full_name"
    Kind: Final[str] = "kind"
    Type: Final[str] = "type"
    UnderlyingType: Final[str] = "underlying_type"
    Access: Final[str] = "access"
    Scope: Final[str] = "scope"
    Variables: Final[str] = "variables"
    StaticVariables: Final[str] = "static_variables"
    Functions: Final[str] = "functions"
    StaticFunctions: Final[str] = "static_functions"
    FreeVariables: Final[str] = "free_variables"
    FreeFunctions: Final[str] = "free_functions"
    Parents: Final[str] = "parents"
    Enums: Final[str] = "enums"
    Structs: Final[str] = "structs"
    Namespaces: Final[str] = "namespaces"
    Namespace: Final[str] = "namespace"
    Parameters: Final[str] = "parameters"
    EnumValues: Final[str] = "enum_values"
    MetaTemplateDecl: Final[str] = "meta_template_decl"
    ReturnType: Final[str] = "return_type"
    Attributes: Final[str] = "attributes"
    DefaultValue: Final[str] = "default_value"
    MemberAttributesOverride: Final[str] = "member_attribs_override"
    Const: Final[str] = "is_const"
    Cpp: Final[str] = "cpp"
    Hlsl: Final[str] = "hlsl"

@dataclass(frozen=True, slots=True)
class _ParseCommentsType:
    BeforeDecl: Final[str] = "comments_before_decl"
    AfterDecl: Final[str] = "comments_after_decl"

# Add to global constants
kInvalid: Final[str] = "invalid"
kInclude: Final[str] = "include"
kSerialize: Final[str] = "serialize"
kExclude: Final[str] = "exclude"

EKind = _Kinds()          # use K.Unknown, K.Class … everywhere
ENode = _NodeType()
EParseComments = _ParseCommentsType()

ParseCommentsMode = {
    EKind.Unknown : EParseComments.BeforeDecl,
    EKind.Namespace : EParseComments.BeforeDecl,
    EKind.Alias : EParseComments.BeforeDecl,
    EKind.Enum : EParseComments.BeforeDecl,
    EKind.EnumValue : EParseComments.AfterDecl,
    EKind.ClassTemplate : EParseComments.BeforeDecl,
    EKind.Class : EParseComments.BeforeDecl,
    EKind.Struct : EParseComments.BeforeDecl,
    EKind.Function : EParseComments.BeforeDecl,
    EKind.Parameter : EParseComments.AfterDecl,
    EKind.Variable : EParseComments.BeforeDecl,
    EKind.FreeFunction : EParseComments.BeforeDecl,
    EKind.FreeVariable : EParseComments.BeforeDecl,
    EKind.TemplateTypeParameter : EParseComments.BeforeDecl,
    EKind.TemplateNonTypeParameter : EParseComments.BeforeDecl,
    EKind.TemplateTemplateParameter : EParseComments.BeforeDecl,
}

kHlslTypes: Final[list]= ["float", "int", "uint", "bool", "half", "double", "uint64"]

def GenHlslDeclarations() :
    result = "#define cbuffer struct\n"
    for t in kHlslTypes :
        for m in range(2, 5) :
            for n in range(2, 5) :
                result += f"using {t}{m}x{n} = float;\n"
            result += f"using {t}{m} = float;\n"
    result += "using uint = unsigned int;\n"
    result += "\n"

    return result

kHlslDeclarations : Final[str] = GenHlslDeclarations()

class TLS_Data:
    def __init__(self):
        self.NodesToInclude: list[str] = []
        self.NodeList: dict[str, Any] = {}
        self.NodeTree: dict[str, Any] = {}
        self.NodeStack: list[dict[str, Any]] = [self.NodeTree]
        self.pycppdefine: str = ""

_ctx: contextvars.ContextVar[TLS_Data] = contextvars.ContextVar("tls")
def TLS() -> TLS_Data:
    try:
        return _ctx.get()
    except LookupError:
        data = TLS_Data()
        _ctx.set(data)
        return data
    
FilesWithPyCppGenTag = dict()
TLS_Dict = {}
PrintLock = threading.Lock()

def atomic_print(text : str) :
    with PrintLock :
        print(f"pycppgen: {text}")

#try to parse the comments before or after the cursor (hacky but, cursor.raw_comments isn't working as expected)
def ParseComments(cursor, kind : str = EParseComments.BeforeDecl):
    try:
        preDeclComments = not kind in ParseCommentsMode or ParseCommentsMode[kind] == EParseComments.BeforeDecl
        parent = cursor.semantic_parent

        tokens = list(parent.get_tokens())
        cursorTokens = list(cursor.get_tokens())
        if len(cursorTokens) == 0 :
            return {}
        
        firstToken = cursorTokens[0]
        firstTokenIndex = tokens.index(next(x for x in tokens if x.location.line == firstToken.location.line))

        if preDeclComments:
            lastTokenIndex = firstTokenIndex
            while firstTokenIndex > 0 and tokens[firstTokenIndex - 1].kind == clang.cindex.TokenKind.COMMENT:
                firstTokenIndex -= 1
        else:
            lastTokenIndex = len(tokens)
            while firstTokenIndex < lastTokenIndex and tokens[firstTokenIndex].kind != clang.cindex.TokenKind.COMMENT:
                firstTokenIndex += 1
            lastTokenIndex = firstTokenIndex
            while lastTokenIndex < len(tokens) and tokens[lastTokenIndex].kind == clang.cindex.TokenKind.COMMENT:
                lastTokenIndex += 1

    except StopIteration as e:
        return {}
    except clang.cindex.LibclangError as e:
        if DebugMode:
            atomic_print(f"ParseComments error: {str(e)}")
        return {}
    
    attribs = ""
    if firstTokenIndex != -1 and lastTokenIndex != -1 :
        for t in tokens[firstTokenIndex:lastTokenIndex] :
            if t.kind == clang.cindex.TokenKind.COMMENT :
                attribs += t.spelling + "\n"

    result = {}
    oneMatch = False

    COMMENT_REGEX = re.compile(r".*\$\[\[pycppgen(?>(?>\s+((?>\s|\w|\W)*)\]\])|(?>\]\]))", flags=re.IGNORECASE | re.MULTILINE)    
    for line in attribs.splitlines() :
        m = COMMENT_REGEX.match(line)
        if m == None : continue
        oneMatch = True

        if m.groups() == None : continue

        comments = ""
        for g in m.groups() :
            if g != None and len(g) > 0:
                comments += g

        if len(comments) == 0 : continue

        comments = comments.split(";")
        for g in comments :
            if len(g) == 0 : continue

            key = ""
            value = ""

            kv = g.split("=")
            if len(kv) == 0 : continue
            if len(kv) > 0 : key = kv[0].strip()
            if len(kv) > 1 : value = kv[1].strip()

            if key.lower() == kExclude : result[kInclude] = str(bool(value != None and value == True))
            else : result[key] = value

    if oneMatch and not kExclude.casefold() in result :
        result[kInclude] = True

    return result
    
def GetScope(cursor, accum : str = "") :
    if cursor.semantic_parent and not cursor.semantic_parent.kind.is_translation_unit() :
        if accum != "" :
            accum = "::" + accum
        accum = str(cursor.semantic_parent.canonical.spelling) + accum
        return GetScope(cursor.semantic_parent.canonical, accum)
    
    return accum

#scoped cursor name
def GetFullName(cursor) :
    accum = str(cursor.displayname)
    return GetScope(cursor, accum)

#append the current node to it's parent and optionally (appendToList) to the global list
def AppendToStackTop(node, node_type : str, appendToList : bool = False) :    
    if not node_type in TLS().NodeStack[-1]:
        TLS().NodeStack[-1][node_type] = dict()

    TLS().NodeStack[-1][node_type][node[ENode.FullName]] = node

    if appendToList :
        TLS().NodeList[node[ENode.FullName]] = node

#common node push code
def ParseNode(cursor, kind : str = kInvalid) :
    node = dict()
    node[ENode.Name] = str(cursor.spelling)
    node[ENode.FullName] = GetFullName(cursor)
    node[ENode.Kind] = kind
    if kind == EKind.ClassTemplate :
        node[ENode.Type] = node[ENode.FullName]
    else :
        node[ENode.Type] = str(cursor.type.spelling)
    node[ENode.Access] = str(cursor.access_specifier)
    node[ENode.Scope] = GetScope(cursor)
    node[ENode.Attributes] = ParseComments(cursor, kind)
    node[ENode.Namespace] = ""
    node[ENode.Const] = cursor.type != None and cursor.type.is_const_qualified() or cursor.is_const_method()

    ns_parent = cursor.semantic_parent
    while ns_parent and ns_parent.kind == CursorKind.NAMESPACE :
        node[ENode.Namespace] = ns_parent.spelling + "::" + node[ENode.Namespace]
        ns_parent = ns_parent.semantic_parent

    if node[ENode.Namespace].endswith("::") :
        node[ENode.Namespace] = node[ENode.Namespace][:-2]

    return node

def PushNode(cursor, kind : str = kInvalid) :
    node = ParseNode(cursor, kind)
    node[ENode.Cpp] = True
    TLS().NodeStack.append(node)
    return TLS().NodeStack[-1]

#common node pop code
def PopNode() :
    TLS().NodeStack = TLS().NodeStack[:-1]

#parse a function cursor
def ParseFunction(cursor, isFreeFunction : bool = False) :

    #TODO: support operators and functions with special characters
    if re.fullmatch("[a-zA-Z0-9_-_]+", cursor.spelling) == None:
        return

    #push this function to it's parent
    node = PushNode(cursor, EKind.Function)
    node[ENode.FullName] = node[ENode.FullName][:node[ENode.FullName].find("(")]

    #get the return type
    node[ENode.ReturnType] = cursor.result_type.spelling

    #and parameters
    node[ENode.Parameters] = dict()
    for child in cursor.get_children() :
        if child.kind == CursorKind.PARM_DECL:
            param = PushNode(child, EKind.Parameter)
            param[ENode.DefaultValue] = ParseDefaultValue(child)
            PopNode()

            #append parameter to parent (function)
            AppendToStackTop(param, ENode.Parameters)

    PopNode()

    #append function to parent (struct/class/namespace/translation_unit)
    if isFreeFunction : 
        node[ENode.Kind] = EKind.FreeFunction
        AppendToStackTop(node, ENode.FreeFunctions, True)
    elif cursor.storage_class == clang.cindex.StorageClass.STATIC :
        AppendToStackTop(node, ENode.StaticFunctions)
    else :
        AppendToStackTop(node, ENode.Functions)

    return node

#@todo
def ParseDefaultValue(cursor) :

    for child in cursor.get_children() :
        """
        if child.kind == CursorKind.TYPE_REF:
            result += f"{child.spelling}("
            for it in child.get_children() :
                result = it.spelling + ", "
            result = result[:-2]
            result += ")"
            return result

        if child.kind in [CursorKind.INTEGER_LITERAL, CursorKind.FLOATING_LITERAL, CursorKind.STRING_LITERAL, CursorKind.CHARACTER_LITERAL]:
            tokens = list(child.get_tokens())
            if len(tokens) == 1:
               return tokens[0].spelling
        """
       
    return ""


#parse variable or class/struct field
def ParseVar(cursor, isFreeVariable : bool = False):

    node = PushNode(cursor, EKind.Variable)
    PopNode()

    node[ENode.DefaultValue] = ParseDefaultValue(cursor)

    if isFreeVariable : 
        node[ENode.Kind] = EKind.FreeVariable
        AppendToStackTop(node, ENode.FreeVariables, True)
    elif cursor.storage_class == clang.cindex.StorageClass.STATIC :
        AppendToStackTop(node, ENode.StaticVariables)
    else :
        AppendToStackTop(node, ENode.Variables)
    
    return node

#parse struct/class
def ParseStruct(cursor, isHlslDecl : bool = False) :
    kind = kInvalid
    if cursor.kind == CursorKind.CLASS_TEMPLATE :
        kind = EKind.ClassTemplate
    elif cursor.kind == CursorKind.CLASS_DECL :
        kind = EKind.Class
    else :
        kind = EKind.Struct

    node = PushNode(cursor, kind)
    node[ENode.MetaTemplateDecl] = ""
    node[ENode.Functions] = {}
    node[ENode.MemberAttributesOverride] = {}

    for child in cursor.get_children() :
        
        #inheritance
        if child.kind == CursorKind.CXX_BASE_SPECIFIER :
            if child.referenced :
                childFullName = GetFullName(child.referenced)
                flags = ParseComments(child.referenced, EKind.Unknown)
                if kInclude in flags: 
                    if str(flags[kInclude]) == "False" :
                        continue
                elif not childFullName in TLS().NodesToInclude :
                    continue
                AppendToStackTop({ENode.FullName: childFullName}, ENode.Parents)
            continue

        #template parameters
        if child.kind == CursorKind.TEMPLATE_TYPE_PARAMETER or child.kind == CursorKind.TEMPLATE_NON_TYPE_PARAMETER or child.kind == CursorKind.TEMPLATE_TEMPLATE_PARAMETER:
            
            kind = kInvalid
            if child.kind == CursorKind.TEMPLATE_TYPE_PARAMETER :
                kind = EKind.TemplateTypeParameter
            elif child.kind == CursorKind.TEMPLATE_NON_TYPE_PARAMETER :
                kind = EKind.TemplateNonTypeParameter
            elif child.kind == CursorKind.TEMPLATE_TEMPLATE_PARAMETER :
                kind = EKind.TemplateTemplateParameter

            param = PushNode(child, kind)
            PopNode()

            if child.kind == CursorKind.TEMPLATE_TYPE_PARAMETER :
                node[ENode.MetaTemplateDecl] += "typename " + param[ENode.Name] + ", "
            elif child.kind == CursorKind.TEMPLATE_NON_TYPE_PARAMETER :
                node[ENode.MetaTemplateDecl] += param[ENode.Type] + " " + param[ENode.Name] + ", "
            elif child.kind == CursorKind.TEMPLATE_TEMPLATE_PARAMETER :
                node[ENode.MetaTemplateDecl] += "template " + param[ENode.Name] + ", "

            AppendToStackTop(param, ENode.Parameters)

            continue

        flags = ParseComments(child, EKind.Unknown)

        #member variables (field)
        if child.kind == CursorKind.FIELD_DECL :
            if (kInclude in flags and flags[kInclude] == True) or isHlslDecl:
                var = ParseVar(child, False)
            continue

        if not kInclude in flags or flags[kInclude] == False:
            continue

        #class functions
        if child.kind == CursorKind.CXX_METHOD:
            fn = ParseFunction(child, False)
            continue

        #static variables?
        if child.kind == CursorKind.VAR_DECL :
            var = ParseVar(child, False)
            continue



        #member enum definitions
        if child.kind == CursorKind.ENUM_DECL :
            if child.is_definition() :
                ParseEnum(child, False)
            continue

        if child.kind == CursorKind.USING_DECLARATION :
            name = str(child.spelling)
            attribs = ParseComments(child)
            if name in node[ENode.MemberAttributesOverride] :
                node[ENode.MemberAttributesOverride][name].update(attribs)
            else :
                node[ENode.MemberAttributesOverride][name] = attribs
            continue

        ParseCursor(child)

    #fixup template declaration string
    if ENode.MetaTemplateDecl in node :
        if node[ENode.MetaTemplateDecl].endswith(", ") :
            node[ENode.MetaTemplateDecl] = node[ENode.MetaTemplateDecl][:-2]

    PopNode()

    return node

#parse struct/class
def ParseHlslStruct(cursor) :
    kind = kInvalid
    if cursor.kind == CursorKind.CLASS_TEMPLATE or cursor.kind == CursorKind.CLASS_DECL :
        return
    kind = EKind.Struct

    node = PushNode(cursor, kind)
    node[ENode.MetaTemplateDecl] = ""
    node[ENode.Functions] = {}
    node[ENode.MemberAttributesOverride] = {}

    for child in cursor.get_children() :
        
        #inheritance
        if child.kind == CursorKind.CXX_BASE_SPECIFIER :
            if child.referenced :
                childFullName = GetFullName(child.referenced)
                ParseComments(child.referenced, EKind.Unknown)
                AppendToStackTop({ENode.FullName: childFullName}, ENode.Parents)
            continue

        #member variables (field)
        if child.kind == CursorKind.FIELD_DECL :
            ParseVar(child, False)
            continue

    PopNode()

    return node

#Parse enum definitions
def ParseEnum(cursor, isGlobal : bool = False) :

    node = PushNode(cursor, EKind.Enum)

    #underlying type
    node[ENode.UnderlyingType] = str(cursor.enum_type.spelling)

    #values
    node[ENode.EnumValues] = dict()
    for child in cursor.get_children() :
        if child.kind == CursorKind.ENUM_CONSTANT_DECL :
            node[ENode.EnumValues][child.spelling] = dict()
            node[ENode.EnumValues][child.spelling]["value"] = str(child.enum_value)
            node[ENode.EnumValues][child.spelling][ENode.Attributes] = ParseComments(child, EKind.EnumValue)

    PopNode()

    AppendToStackTop(node, ENode.Enums, isGlobal)

#append to list and recurse
def ParseNamespace(cursor) :
    node = PushNode(cursor, EKind.Namespace)
    for child in cursor.get_children() :
        ParseCursor(child)
    PopNode()

    AppendToStackTop(node, ENode.Namespaces, True)

#using/typedef
def ParseTypeAlias(cursor) :
    node = PushNode(cursor, EKind.Alias)
    node[ENode.UnderlyingType] = str(cursor.underlying_typedef_type.spelling)
    PopNode()

    AppendToStackTop(node, ENode.Variables, True)

#generic parse call
def ParseCursor(cursor, forceInclude : bool = False)  -> None:
    #TODO
    if cursor.kind == CursorKind.UNION_DECL : return
    if cursor.kind == CursorKind.TYPEDEF_DECL : return
    if cursor.kind == CursorKind.PARM_DECL : return    

    fullName = GetFullName(cursor)
    if fullName == "" : return

    #allow namespaces to be "duplicated"
    if cursor.kind != CursorKind.NAMESPACE :
        #ignore already added
        if fullName in TLS().NodeList :
            return
    
    if cursor.kind == CursorKind.NAMESPACE :
        ParseNamespace(cursor)
        return

    #ignore this kind for now
    if cursor.kind == CursorKind.TYPE_REF or cursor.kind == CursorKind.TEMPLATE_REF or cursor.kind == CursorKind.NAMESPACE_REF:
        return

    isStruct = cursor.kind == CursorKind.STRUCT_DECL or cursor.kind == CursorKind.CLASS_DECL
    isStruct |= cursor.kind == CursorKind.CLASS_TEMPLATE or cursor.kind == CursorKind.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION
    isHlslDecl = isStruct and fullName.endswith("_pyhlslgen")

    #check if it should be parsed
    included = True
    if not forceInclude :
        flags = ParseComments(cursor, EKind.Unknown)
        if kInclude in flags : 
            if str(flags[kInclude]) == "False" :
                included = False
        elif not fullName in TLS().NodesToInclude :
            included = False

    if isStruct :
        if cursor.is_definition() and (included or isHlslDecl):
            node = ParseStruct(cursor, isHlslDecl)   
            node[ENode.Cpp] = included
            node[ENode.Hlsl] = isHlslDecl
            AppendToStackTop(node, ENode.Structs)
            TLS().NodeList[fullName] = node
        return

    if not included:
        return
    
    if cursor.kind == CursorKind.ENUM_DECL :
        if cursor.is_definition() :
            node = ParseEnum(cursor, True)
        return

    if cursor.kind == CursorKind.VAR_DECL :
        ParseVar(cursor, True)
        return

    if cursor.kind == CursorKind.FUNCTION_DECL :
        ParseFunction(cursor, True)
        return

    if cursor.kind == CursorKind.TYPE_ALIAS_DECL :
        ParseTypeAlias(cursor)
        return

def ResolvePath(file : str) :
    return str(pathlib.Path(file).resolve())

def GetOutputFilePath(filePath : str, ext : str = "h") :
    extStart = filePath.rfind(".")
    outputPath = filePath[:extStart]
    outputPath += f".gen.{ext}"
    return ResolvePath(outputPath)

def GetOutputFileName(filePath : str, ext  : str = "h") :
    outputPath = pathlib.Path(GetOutputFilePath(filePath, ext))
    return ResolvePath(outputPath.relative_to(outputPath.parent))

def ParseTranslationUnit(tu, file) :
    global FilesToParse

    #initialize data
    TLS().NodesToInclude = []
    TLS().NodeList = {}
    TLS().NodeTree = {}
    TLS().NodeStack = [TLS().NodeTree] 
    
    currentFile = str(pathlib.Path(file).resolve())
    #first = next(x for x in tu.cursor.get_children() if x.location.file and x.location.file.name in FilesToParse)
    #filteredChildren = list(filter(lambda x: x.location.file and str(pathlib.Path(x.location.file.name).resolve()) in FilesToParse, tu.cursor.get_children()))
    filteredChildren = list(filter(lambda x: x.location.file and str(pathlib.Path(x.location.file.name).resolve()) == file, tu.cursor.get_children()))
    for cursor in  filteredChildren :
        ParseCursor(cursor)

    return TLS().NodeList

#parse a header file
def ParseFile(filePath : str, options : list) :

    # Make destFilePath equal to filepath but append "__pycppgen_tmp" before the extension
    extStart = filePath.rfind(".")
    tmpPath = filePath[:extStart] + "__pycppgen_tmp" + filePath[extStart:]

    tu = None

    try:
        contents = kHlslDeclarations

        with open(filePath) as file:
            for line in file.readlines() :
                contents += line
                m = re.match(r"\s*\/\/\s*\$\[\[pycppgen-include\s+((?>\w|\W)*)\]\]", line, flags=re.MULTILINE|re.IGNORECASE)
                if not m : continue
                for g in m.groups() :
                    TLS().NodesToInclude += g.replace(" ", ";").replace(",", ";").split(";")

        with open(tmpPath, "wt") as tmpFile:
            tmpFile.write(contents)

        args = ['-x', 'c++', '-std=c++20', "-DPYCPPGEN", "-D__clang_major__=19", "-Wmacro-redefined", "-D_PYCPPGEN_=1"] + options
        idx = clang.cindex.Index.create()
        tu = idx.parse(tmpPath, args = args, options = clang.cindex.TranslationUnit.PARSE_INCOMPLETE | clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)

        if DebugMode :
            # Print diagnostics
            for diag in tu.diagnostics:
                atomic_print(str(diag))
    except:
        atomic_print(f"error parsing {filePath}")
    finally:
        if os.path.exists(tmpPath):
            os.remove(tmpPath)

    return tu, tmpPath

#codegen: common type header 
def CodeGenOutputHeaderDefines(code, node) :
    
    #make a unique name
    TLS().pycppdefine = "_pycppgen_" + node[ENode.FullName].replace("::", "_").replace("<","_").replace(">","_")
    pycppdefine = TLS().pycppdefine

    lines = [
        f"//<autogen_{pycppdefine}>\n",
        f"#ifndef {pycppdefine}\n",
        f"#define {pycppdefine}\n\n"
    ]

    return code + "".join(lines)

#codegen: common type header 
def CodeGenOutputMetaHeader(code, node) :
    lines = []

    #create the specialized pycppgen struct
    #code 'template<> struct pycppgen<type_name> {
    lines.append("template<")
    if ENode.MetaTemplateDecl in node :
        lines.append(node[ENode.MetaTemplateDecl])
    lines.append(f">\nstruct pycppgen<{node[ENode.FullName]}>")
    
    if node[ENode.Kind] == EKind.Class or node[ENode.Kind] == EKind.ClassTemplate or node[ENode.Kind] == EKind.Struct :
        lines.append(f" : {node[ENode.FullName]}")
        if ENode.Parents in node :
            for p in node[ENode.Parents] :
                    lines.append(f", virtual pycppgen<{p}>")
    lines.extend([
        "{\n",
        f"\tusing pycppgen_t = pycppgen<{node[ENode.FullName]}>;\n",
        "\tstatic constexpr bool is_valid() { return true; }\n",
        "\tstatic constexpr const char* name() { return \"" + node[ENode.Name] + "\"; }\n",
    ])

    code += "".join(lines)

    return code

#codegen: common type footer
def CodeGenOutputMetaFooter(code, node) :
    pycppdefine = TLS().pycppdefine

    code += "};\n\n"
    code += f"#endif //{pycppdefine}\n"

    #tag the end of autogen code
    code += f"//</autogen_{pycppdefine}>\n\n"

    pycppdefine = None

    return code

#codegen: emit attributes as array of pairs
def CodeGenOutputAttributes(node, depth : int = 0) -> str:
    if ENode.Attributes in node and len(node[ENode.Attributes]) > 0 :
        attribs = node[ENode.Attributes]

        depth += 1
        result = "{\n"

        for k, v in attribs.items() :
            if k == kInclude : continue
            result += "\t" * depth
            result += "{ \"" + k + "\", "
            if len(str(v)) > 0 :
                result += "\"" + v + "\" "
            else :
                result += "\"\" "
            result += "},\n"
        if result.endswith(",\n") : 
            result = result[:-2]
        result += "\n" 
        depth -= 1
        result += "\t" * (depth + 1) + "}"
    else :
        result = "{}"

    return result

#codegen: emit call_function definitions
def CodeGenOutputAddFunctionDeclaration(declarations, node, funcNode, isStatic : bool) :
    decl = f"static_{isStatic}_{funcNode[ENode.Type]}"
    numParams = len(funcNode[ENode.Parameters])
    isConst = decl.endswith("const")
      
    #if call_function with the current return value and parameters doesn't exists, create it
    if not decl in declarations :
        #code 'static bool call_function(std::string view name, '
        declarations[decl] = "\tstatic bool call_function(std::string_view name, " 
        if not isStatic :
            if isConst :
                #code 'const '
                declarations[decl] += "const " 
            #code '<type>* obj, '
            declarations[decl] += node[ENode.Type] + "* obj, "

        if funcNode[ENode.ReturnType] != "void" :
            #code '<return_type>& result, '
            declarations[decl] += f"std::remove_cv_t<{funcNode[ENode.ReturnType]}>& result, "

        paramNum = 1
        for _, pv in funcNode[ENode.Parameters].items() :
            #code '_<param_num, '
            declarations[decl] += f"{pv[ENode.Type]} _{str(paramNum)}, "
            paramNum += 1

        #remove last ', ' and close parenthesis 
        declarations[decl] = declarations[decl][:-2] + ") {\n"
    
    #append name comparison + call code
    #code '     if (name == "<function_name>") {
    declarations[decl] += "\t\tif (name == \"" + funcNode[ENode.Name] + "\") {\n"
    declarations[decl] += "\t\t\t"

    if funcNode[ENode.ReturnType] != "void" :
        #code 'result = '
        declarations[decl] += "result = "

    if isStatic :   
        #code '<class_name>::<function_name>('
        declarations[decl] += f"{node[ENode.Type]}::{funcNode[ENode.Name]}("
    else :          
        #code 'obj-><function_name>('
        declarations[decl] += f"static_cast<"
        if isConst :
            #code 'const '
            declarations[decl] += "const " 
        declarations[decl] += f"pycppgen_t*>(obj)->{funcNode[ENode.Name]}("

    #code '[_1, _2...]'
    if numParams > 0 :
        paramNum = 1
        for _, pv in funcNode[ENode.Parameters].items() :
            declarations[decl] += " _" + str(paramNum) + ", "
            paramNum += 1
        declarations[decl] = declarations[decl][:-2] + ");\n"
    else :
        declarations[decl] += ");\n"

    #code '         return true;'
    #code '     }'
    declarations[decl] += "\t\t\treturn true;\n\t\t}\n"

def GenerateMemberVariableStructDefinition(node : dict, var : dict, infoName : str, isStatic : bool = False, tabs : int = 0) :
    result = ""
    
    varName = var[ENode.Name]
    fullVarName = var[ENode.FullName]

    result += "\t" * tabs + f"struct {infoName} : protected {node[ENode.Name]} " + "{\n"
    tabs += 1 
    result += "\t" * tabs + f"using {node[ENode.Name]}::{var[ENode.Name]};\n"
    result += "\t" * tabs + f"using type_t = decltype({infoName}::{varName});\n"
    result += "\t" * tabs + f"using owner_t = {node[ENode.Name]};\n"
    result += "\n"
    result += "\t" * tabs + "static constexpr const char* name() { return \"" + var[ENode.Name] + "\"; }\n"
    result += "\t" * tabs + "static constexpr const char* full_name() { return \"" + fullVarName + "\"; }\n"
    result += "\t" * tabs + "static constexpr const char* type_name() { return \"" + var[ENode.Type] + "\"; }\n"
    result += "\t" * tabs + "static const type_info& type_id() { return typeid(type_t); }\n"
    if isStatic :
        result += "\t" * tabs + f"static type_t* variable_ptr() " + "{ return " + f"&{infoName}::{varName}; " + "}\n"
        result += "\t" * tabs + "static constexpr size_t offset() { return 0; }\n"
    else :
        result += "\t" * tabs + f"static type_t {node[ENode.Name]}::* variable_ptr() " + "{ return " + f"&{infoName}::{varName}; " + "}\n"
        result += "\t" * tabs + "static constexpr size_t offset() { " + f"return std::integral_constant<size_t, (size_t)(&(static_cast<{infoName}*>(nullptr)->{varName}))>::value; " + "}\n"
    result += "\t" * tabs + "static constexpr size_t element_size() { return sizeof(std::remove_all_extents_t<type_t>); }\n"
    result += "\t" * tabs + "static constexpr size_t total_size() { return sizeof(type_t); }\n"
    result += "\t" * tabs + "static constexpr size_t array_rank() { return pycppgen_detail::get_rank<type_t>(); }\n"
    result += "\t" * tabs + "static constexpr auto array_extents() { return pycppgen_detail::get_extents<type_t>(); }\n"
    result += "\t" * tabs + "static constexpr bool is_const() { return std::is_const<type_t>::value; }\n"
    result += "\t" * tabs + "static constexpr bool is_array() { return std::is_array<type_t>::value; }\n"
    result += "\t" * tabs + "static constexpr bool is_pointer() { return std::is_pointer<type_t>::value; }\n"
    result += "\t" * tabs + "static constexpr bool is_integral() { return std::is_integral<type_t>::value; }\n"
    result += "\t" * tabs + "static constexpr bool is_floating_point() { return std::is_floating_point<type_t>::value; }\n"
    result += "\t" * tabs + "static constexpr bool is_enum() { return std::is_enum<type_t>::value; }\n"
    result += "\t" * tabs + "static constexpr bool is_signed() { return std::is_signed<type_t>::value; }\n"
    result += "\t" * tabs + "static constexpr bool is_unsigned() { return std::is_unsigned<type_t>::value; }\n"
    tabs -= 1
    result += "\t" * tabs + "};\n"

    return result

def GenerateMemberFunctionInfo(node, func, infoName) :
    result = ""

    funcName = func[ENode.Name]
    paramsString = func[ENode.Type][len(func[ENode.ReturnType]) + 1:]

    result += f"\t\tstruct {infoName} : protected {node[ENode.FullName]} " + "{\n"
    result += f"\t\t\tusing {node[ENode.Name]}::{func[ENode.Name]};\n"
    result += f"\t\t\tusing type_t = decltype(&{infoName}::{func[ENode.Name]});\n"
    result += f"\t\t\tusing return_type_t = {func[ENode.ReturnType]};\n"
    result += "\n"

    result += "\t\t\tstatic constexpr const char* name() { return \"" + funcName + "\"; }\n"
    result += "\t\t\tstatic constexpr const char* declaration() { return \"" + func[ENode.Type] + "\"; }\n"
    result += "\t\t\tstatic constexpr const char* return_type_name() { return \"" + func[ENode.ReturnType] + "\"; }\n"
    result += "\t\t\tstatic constexpr const char* parameters_string() { return \"" + paramsString + "\"; }\n"
    result += "\t\t\tstatic type_t function_ptr() { return &" + infoName + "::" + func[ENode.Name] + "; }\n"
    result += "\t\t\tstatic constexpr attribute_map_t attributes() { return " + CodeGenOutputAttributes(func, 4) + "; }\n"
    result += "\t\t\tstatic std::vector<function_parameter_info> parameters() {\n"
    result += "\t\t\t\tstd::vector<function_parameter_info> result;\n"
    for _, pv in func[ENode.Parameters].items() :
        paramInfoName = f"{pv[ENode.Name]}_info" + str(result.count('\n'))
        result += f"\t\t\t\tfunction_parameter_info {paramInfoName};\n"
        result += f"\t\t\t\t{paramInfoName}.Name = \"{pv[ENode.Name]}\";\n"
        result += f"\t\t\t\t{paramInfoName}.Type = \"{pv[ENode.Type]}\";\n"
        result += f"\t\t\t\t{paramInfoName}.DefaultValue = \"{pv[ENode.DefaultValue]}\";\n"
        result += f"\t\t\t\tresult.push_back({paramInfoName});\n"
    result += "\t\t\t\treturn result;\n"
    result += "\t\t\t}\n"

    result += "\t\t};\n"
    result += f"\t\tvisitor.template operator()<{infoName}>();\n\n"

    return result

def CalcHlslSize(varType : str) :

    #match type<n>x<m>[s] patterns
    match = re.fullmatch(rf'({"|".join(kHlslTypes)})(\d)?(?:x(\d))?(?:\[(\w+)\])?', varType)
    if match:
        baseType, rows, cols, arraySize = match.groups()
        if rows and cols:
            size = 4 * int(rows) * int(cols)
        elif rows:
            size = 4 * int(rows)
        else:
            size = 4
        if baseType.startswith('uint64') | baseType.startswith('double'):
            size *= 2
        if baseType.startswith('half'):
            size /= 2
        if arraySize:
            size *= int(arraySize)
        return size, baseType, arraySize, rows, cols
    
    return None, None, None, None, None
    

#codegen: emit a hlsl node
def CodeGenHlslNode(hlslCode, node) :
    
    hppResult = ""
    hppResult += f"struct {node[ENode.Name].replace("_pyhlslgen", "")}\n"
    hppResult += "{\n"

    hlslResult = ""
    hlslResult += f"struct {node[ENode.Name].replace("_pyhlslgen", "")}\n"
    hlslResult += "{\n"

    offset = 0
    padNum = 0
    if ENode.Variables in node :
        for _, var in node[ENode.Variables].items() :

            newDecl = ""

            size, baseType, arraySize, rows, cols = CalcHlslSize(var[ENode.Type])
            
            if size == None :
                continue

            if cols and int(cols) > 1:
                rows = "4"
                size = int(16 * int(cols))
                
            if arraySize and int(arraySize) > 1 and rows and int(rows) > 1:
                rows = "4"
                size = int(16 * int(arraySize))
                if cols and int(cols) > 1:
                    size = int(size * int(cols))

            if offset % 16 != 0 and (offset % 16) + size > 16 :
                padNum = padNum + 1
                padSize = int((16 - offset % 16))
                newDecl += f"\tfloat{int(padSize / 4)}\t\t_pad{padNum};\t// Offset: {offset} - Size: {int(padSize)}\n"
                offset = offset + int(padSize)

            newDecl += f"\t{baseType}"
            
            if rows and int(rows) > 1:
                newDecl += f"{rows}"
            if cols and int(cols) > 1:
                newDecl += f"x{cols}"
            else :
                newDecl += f"\t"

            newDecl += f"\t{var[ENode.Name]}"
            if arraySize and int(arraySize) > 1:
                newDecl += f"[{arraySize}]"
            else :
                newDecl += f""

            hppResult += newDecl
            hlslResult += newDecl

            if ENode.DefaultValue in var and var[ENode.DefaultValue] != "" :
                hppResult += f" = {var[ENode.DefaultValue]}"

            hppResult += f";\t// Offset: {offset} - Size: {size}\n"
            hlslResult += f";\t// Offset: {offset} - Size: {size}\n"

            offset += size     

    if offset % 16 != 0 :
        padNum = padNum + 1
        padSize = int((16 - offset % 16))
        hppResult += f"\tfloat{int(padSize / 4)}\t\t_pad{padNum};\t// Offset: {offset} - Size: {int(padSize)}\n"
        hlslResult += f"\tfloat{int(padSize / 4)}\t\t_pad{padNum};\t// Offset: {offset} - Size: {int(padSize)}\n"
        offset = offset + int(padSize)

    hppResult += "};"
    hppResult = f"// Size = {offset}\n{hppResult}\n"

    hlslResult += "};"
    hlslResult = f"// Size = {offset}\n{hlslResult}\n"

    result = "#ifdef __hlsl_dx_compiler\n"
    result += hlslResult
    result += "#else\n"
    result += hppResult
    result += "#endif\n\n"

    return hlslCode + result

#codegen: emit a node
def CodeGenOutputNode(node) :
   
    hppCode = cppCode = ""

    #class or structs
    if node[ENode.Kind] == EKind.Class or node[ENode.Kind] == EKind.ClassTemplate or node[ENode.Kind] == EKind.Struct :
        hppCode = CodeGenOutputHeaderDefines(hppCode, node)
        hppCode = CodeGenOutputMetaHeader(hppCode, node)

        if ENode.Variables in node :
            for _, var in node[ENode.Variables].items() :
                hppCode += f"\tusing {node[ENode.FullName]}::{var[ENode.Name]};\n"
        
        if ENode.Functions in node :
            for _, fn in node[ENode.Functions].items() :
                hppCode += f"\tusing {node[ENode.Name]}::{fn[ENode.Name]};\n"
        hppCode += "\n"

        #declare the attribute map
        hppCode += "\tstatic attribute_map_t attributes() {\n"
        hppCode += "\t\treturn {" + CodeGenOutputAttributes(node, 2) + "};\n" 
        hppCode += "\t};\n\n"
        
        #variables
        if ENode.Variables in node :
            for _, var in node[ENode.Variables].items() :
                if var[ENode.Access] == str(AccessSpecifier.PROTECTED) or var[ENode.Access] == str(AccessSpecifier.PUBLIC) :
                    varName = f"{node[ENode.FullName]}::{var[ENode.Name]}"

                    hppCode += f"\t//{var[ENode.Type]} {var[ENode.Name]}\n"
                    hppCode += f"\tusing {var[ENode.Name]}_type = decltype({varName});\n"
                    if not var[ENode.Const] :
                        hppCode += f"\tvoid set_{var[ENode.Name]}(const {var[ENode.Name]}_type& value)"
                        hppCode += "{ if constexpr (!std::is_array<" + var[ENode.Name] + "_type>::value ) { " + varName + " = value; } }\n"
                    hppCode += "\tconst auto& get_" + var[ENode.Name] + "() const { return " + varName + "; }\n"
                    hppCode += "\tauto& get_" + var[ENode.Name] + "_ref() { return " + varName + "; }\n"
                    hppCode += "\tstatic auto get_" + var[ENode.Name] + "_member_variable_info() {\n"
                    hppCode += GenerateMemberVariableStructDefinition(node, var, f"{var[ENode.Name]}_info", False, 2)           
                    hppCode += f"\t\treturn {var[ENode.Name]}_info();\n"
                    hppCode += "\t}\n\n"
        hppCode += "\n"

        #static variables
        if ENode.StaticVariables in node :
            for _, var in node[ENode.StaticVariables].items() :
                if var[ENode.Access] == str(AccessSpecifier.PROTECTED) or var[ENode.Access] == str(AccessSpecifier.PUBLIC) :
                    varName = f"{node[ENode.FullName]}::{var[ENode.Name]}"
                    hppCode += f"\t//static {var[ENode.Type]} {var[ENode.Name]}\n"
                    hppCode += f"\tusing {var[ENode.Name]}_type = decltype({varName});\n"
                    if not var[ENode.Const] :
                        hppCode += "\tconst void set_" + var[ENode.Name] + "(const " + var[ENode.Name] + "_type& value) { " + varName + " = value; }\n"
                    hppCode += "\tconst auto& get_" + var[ENode.Name] + "() const { return " + varName + "; }\n"
                    hppCode += "\tdecltype(auto) get_" + var[ENode.Name] + "_ref() { return " + varName + "; }\n"
                    hppCode += "\tstatic auto get_" + var[ENode.Name] + "_member_variable_info() {\n"
                    hppCode += GenerateMemberVariableStructDefinition(node, var, f"{var[ENode.Name]}_info", True, 2)           
                    hppCode += f"\t\treturn {var[ENode.Name]}_info();\n"
                    hppCode += "\t}\n\n"
        hppCode += "\n"

        #parent classes 
        hppCode += "\tstatic void for_each_parent(auto visitor, uint32_t maxDepth = UINT_MAX) {\n"
        if ENode.Parents in node :
            hppCode += "\t\tif(maxDepth > 0) {\n"
            for p in node[ENode.Parents] :
                typeName = "type_" + p.replace("::", "_")
                hppCode += "\t\t\tpycppgen<" + p + ">::for_each_parent(visitor, maxDepth - 1);\n"
                hppCode += f"\t\t\tvisitor.template operator()<{p}>();\n"
            hppCode += "\t\t}\n"
        hppCode += "\t};\n\n"
        
        #variable's reflection
        hppCode += "\tstatic void for_each_var(auto visitor, uint32_t maxDepth = UINT_MAX) {\n"
        if ENode.Namespace in node and node[ENode.Namespace] != "" :
            hppCode += f"\t\tusing namespace {node[ENode.Namespace]};\n"
        
        #parent variables
        if ENode.Parents in node :
            hppCode += "\t\tif(maxDepth > 0) {\n"
            for p in node[ENode.Parents] :
                hppCode += f"\t\t\tpycppgen<{p}>::for_each_var(visitor, maxDepth - 1);\n"
            hppCode += "\t\t}\n"
            hppCode += "\n"

        if ENode.Variables in node and len(node[ENode.Variables]) > 0 :
            for _, var in node[ENode.Variables].items() :
                #skip private variables
                if var[ENode.Access] == str(AccessSpecifier.PRIVATE) :
                    continue
                
                #call visitor
                hppCode += f"\t\tvisitor.template operator()<decltype(get_{var[ENode.Name]}_member_variable_info())>();\n"

        hppCode += "\t}\n\n"

        hppCode += "\tstatic void for_each_var(" + node[ENode.Type] + "* obj, auto visitor, uint32_t maxDepth = UINT_MAX) {\n"
        if ENode.Namespace in node and node[ENode.Namespace] != "" :
            hppCode += f"\t\tusing namespace {node[ENode.Namespace]};\n"
        #parent classes
        if ENode.Parents in node :
            hppCode += "\t\tif(maxDepth > 0) {\n"
            for p in node[ENode.Parents] :
                hppCode += f"\t\t\tpycppgen<{p}>::for_each_var(obj, visitor, maxDepth - 1);\n"
            hppCode += "\t\t}\n"

        if ENode.Variables in node and len(node[ENode.Variables]) > 0 :
            for _, var in node[ENode.Variables].items() :
                #skip private variables
                if var[ENode.Access] == str(AccessSpecifier.PRIVATE) :
                    continue
               
                hppCode += f"\t\tvisitor.template operator()<decltype(get_{var[ENode.Name]}_member_variable_info())>(static_cast<pycppgen_t*>(obj)->get_{var[ENode.Name]}_ref());\n"
        hppCode += "\t}\n\n"

        hppCode += "\tstatic void for_each_var(const " + node[ENode.Type] + "* obj, auto visitor, uint32_t maxDepth = UINT_MAX) {\n"
        if ENode.Namespace in node and node[ENode.Namespace] != "" :
            hppCode += f"\t\tusing namespace {node[ENode.Namespace]};\n"
        #parent classes
        if ENode.Parents in node :
            hppCode += "\t\tif(maxDepth > 0) {\n"
            for p in node[ENode.Parents] :
                hppCode += f"\t\t\tpycppgen<{p}>::for_each_var(obj, visitor, maxDepth - 1);\n"
            hppCode += "\t\t}\n"

        if ENode.Variables in node and len(node[ENode.Variables]) > 0 :
            for _, var in node[ENode.Variables].items() :
                #skip private variables
                if var[ENode.Access] == str(AccessSpecifier.PRIVATE) :
                    continue

                #call visitor
                hppCode += f"\t\tvisitor.template operator()<decltype(get_{var[ENode.Name]}_member_variable_info())>(static_cast<const pycppgen_t*>(obj)->get_{var[ENode.Name]}());\n"
        hppCode += "\t}\n\n"

        #do the same for static variables
        hppCode += "\tstatic void for_each_static_var(auto visitor) {\n"
        if ENode.StaticVariables in node and len(node[ENode.StaticVariables]) > 0 :
            for _, var in node[ENode.StaticVariables].items() :
                #skip private variables
                if var[ENode.Access] == str(AccessSpecifier.PRIVATE) :
                    continue
               
                #call visitor
                hppCode += f"\t\tvisitor.template operator()<decltype(get_{var[ENode.Name]}_member_variable_info())>();\n"
        hppCode += "\t}\n\n"
        
        #get_var_attributes
        hppCode += "\tstatic attribute_map_t get_var_attributes(std::string_view name) {\n"
        if ENode.Namespace in node and node[ENode.Namespace] != "" :
            hppCode += f"\t\tusing namespace {node[ENode.Namespace]};\n"
        
        hppCode += f"\t\tattribute_map_t result;\n"

        if ENode.Variables in node and len(node[ENode.Variables]) > 0 :
            for _, var in node[ENode.Variables].items() :
                #skip private variables
                if var[ENode.Access] == str(AccessSpecifier.PRIVATE) :
                    continue
                
                hppCode += f"\t\tif (name == \"{var[ENode.Name]}\")\n"
                hppCode += f"\t\t\t result = {CodeGenOutputAttributes(var, 3)};\n"
            
        #parent classes
        if ENode.Parents in node :
            hppCode += "\n"
            for p in node[ENode.Parents] :
                hppCode += "\t\tif (result.empty())\n"
                hppCode += f"\t\t\tresult = pycppgen<{p}>::get_var_attributes(name);\n"
            hppCode += "\n"

        if ENode.MemberAttributesOverride in node and len(node[ENode.MemberAttributesOverride]) > 0:
            hppCode += f"\t\t//overrides\n"
            overrides = node[ENode.MemberAttributesOverride]
            for o in overrides :
                hppCode += f"\t\tif (name == \"{o}\")\n"
                hppCode += "\t\t{\n"
                for r in overrides[o]:
                    hppCode += f"\t\t\tresult[\"{r}\"] = \"{overrides[o][r]}\";\n"
                hppCode += "\t\t}\n"

        hppCode += "\t\treturn result;\n"
        hppCode += "\t}\n\n"

        #serialization creates a dump (output) and parse (input) functions
        hppCode += "\ttemplate<typename T> static bool dump(T& result, const " + node[ENode.Type] + "* obj) {\n"
        if ENode.Parents in node :
            for parent in node[ENode.Parents] :
                hppCode += f"\t\tpycppgen<{parent}>::dump(result, obj);\n"

        if ENode.Variables in node and len(node[ENode.Variables]) > 0 :
            #serialize the values
            for _, var in node[ENode.Variables].items() :
                if kSerialize in var[ENode.Attributes] and (var[ENode.Access] == str(AccessSpecifier.PUBLIC) or var[ENode.Access] == str(AccessSpecifier.PROTECTED)) :
                    hppCode += f"\t\tresult[\"{var[ENode.Name]}\"] = static_cast<const pycppgen_t*>(obj)->get_{var[ENode.Name]}();\n"
        hppCode += "\t\treturn true;\n"
        hppCode += "\t}\n\n"

        hppCode += "\ttemplate<typename T, typename R> static bool parse(const T& data, R* obj) {\n"
        if ENode.Parents in node :
            for parent in node[ENode.Parents] :
                hppCode += f"\t\tpycppgen<{parent}>::parse(data, obj);\n"
        if ENode.Variables in node and len(node[ENode.Variables]) > 0 :
            for _, var in node[ENode.Variables].items() :
                if kSerialize in var[ENode.Attributes] and (var[ENode.Access] == str(AccessSpecifier.PUBLIC) or var[ENode.Access] == str(AccessSpecifier.PROTECTED)) :
                    hppCode += "\t\tif (data.contains(\"" + var[ENode.Name]+ "\"))\n"
                    hppCode += "\t\t\tstatic_cast<pycppgen_t*>(obj)->set_" + var[ENode.Name] + "(data[\"" + var[ENode.Name]+ "\"]);\n"
        hppCode += "\t\treturn true;\n"
        hppCode += "\t}\n\n"

        #functions
        hppCode += "\tstatic void for_each_function(auto visitor, uint32_t maxDepth = UINT_MAX) {\n"
        if ENode.Namespace in node and node[ENode.Namespace] != "" :
            hppCode += f"\t\tusing namespace {node[ENode.Namespace]};\n"

        if ENode.Parents in node :
            hppCode += "\t\tif(maxDepth > 0) {\n"
            for p in node[ENode.Parents] :
                hppCode += f"\t\t\tpycppgen<{p}>::for_each_function(visitor, maxDepth - 1);\n"
            hppCode += "\t\t}\n"

        if ENode.Functions in node and len(node[ENode.Functions]) > 0 :
            for _, func in node[ENode.Functions].items() :
                if func[ENode.Access] == str(AccessSpecifier.PUBLIC) or func[ENode.Access] == str(AccessSpecifier.PROTECTED) :
                    funcName = func[ENode.Name]
                    infoName = f"{funcName}_info_" + str(hppCode.count('\n'))

                    hppCode += GenerateMemberFunctionInfo(node, func, infoName)
        hppCode += "\t}\n\n"

        #functions
        hppCode += "\tstatic bool find_function_by_name(std::string_view name, auto visitor, uint32_t maxDepth = UINT_MAX) {\n"
        hppCode += "\t\tbool result = false;\n"
        hppCode += "\t\tfor_each_function([&]<typename R>() {\n"
        hppCode += "\t\t\tif (R::name() == name) { result = true; visitor.template operator()<R>(); } \n"
        hppCode += "\t\t}, maxDepth);\n"
        hppCode += "\treturn result;\n"
        hppCode += "\t}\n\n"
        
        #has_function by name declaration
        hppCode += "\tstatic constexpr bool has_function(std::string_view name, uint32_t maxDepth = UINT_MAX) {\n"
        if ENode.Namespace in node and node[ENode.Namespace] != "" :
            hppCode += f"\t\tusing namespace {node[ENode.Namespace]};\n"

        if ENode.Functions in node :
            for _, v in node[ENode.Functions].items() :
                hppCode += f"\t\tif (name == std::string_view(\"{v[ENode.Name]}\")) return true; \n"
        if ENode.StaticFunctions in node :
            for _, v in node[ENode.StaticFunctions].items() :
                hppCode += f"\t\tif (name == std::string_view(\"{v[ENode.Name]}\")) return true; \n"
        if ENode.Parents in node :
            hppCode += "\t\tif(maxDepth > 0) {\n"
            for p in node[ENode.Parents] :
                hppCode += f"\t\t\tif (pycppgen<{p}>::has_function(name, maxDepth)) return true;\n"
            hppCode += "\t\t}\n"
        hppCode += "\t\treturn false;\n\t}\n\n"

        declarations = dict()

        #append functions
        if ENode.Functions in node :
            for _, v in node[ENode.Functions].items() :
                CodeGenOutputAddFunctionDeclaration(declarations, node, v, False)

        #append static functions
        if ENode.StaticFunctions in node and len(node[ENode.StaticFunctions]) > 0 :
            for _, v in node[ENode.StaticFunctions].items() :
                CodeGenOutputAddFunctionDeclaration(declarations, node, v, True)

        for _, v in declarations.items() :
            hppCode += v + "\t\treturn false;\n\t}\n\n"

        hppCode = CodeGenOutputMetaFooter(hppCode, node)

    elif node[ENode.Kind] == EKind.Enum :
        hppCode = CodeGenOutputHeaderDefines(hppCode, node)
        hppCode = CodeGenOutputMetaHeader(hppCode, node)

        #append enum attributes
        hppCode += "\tattribute_map_t attributes() {\n"
        hppCode += "\t\treturn {" + CodeGenOutputAttributes(node, 2) + "};\n" 
        hppCode += "};\n\n"

        if ENode.EnumValues in node :
            #for each enum
            hppCode += "\ttemplate<typename FN> static void for_each_enum_value(FN&& visitor) {\n"
            for k, v in node[ENode.EnumValues].items() :
                hppCode += "\t\tvisitor( " + node[ENode.FullName] + "::" + k + " );\n"
            hppCode += "\t}\n"

            #enum to string
            hppCode += "\tstatic constexpr std::string_view enum_to_string(" + node[ENode.FullName] + " value) {\n"
            for k, v in node[ENode.EnumValues].items() :
                hppCode += "\t\tif (value == " + node[ENode.FullName] + "::" + k + " ) return \"" + k + "\";\n"
            hppCode += "\t\treturn \"\";\n"
            hppCode += "\t}\n"

            hppCode += "\tstatic std::string bitfield_to_string(" + node[ENode.FullName] + " value) {\n"
            hppCode += f"\t\tusing type = std::underlying_type_t<{node[ENode.FullName]}>;\n"
            hppCode += f"\t\tstd::string result;\n"
            for k, v in node[ENode.EnumValues].items() :
                hppCode += f"\t\tif ((type)value & (type){node[ENode.FullName]}::{k}) result += \"|{k}\";\n"
            hppCode += "\t\treturn result.empty() ? result : std::string{result.begin() + 1, result.end()};\n"
            hppCode += "\t}\n"

            #string to enum
            hppCode += "\tstatic constexpr " + node[ENode.FullName] + " string_to_enum(std::string_view value) {\n"
            for k, v in node[ENode.EnumValues].items() :
                hppCode += "\t\tif (value == \"" + k + "\") return " + node[ENode.FullName] + "::" + k + ";\n"
            hppCode += "\t\treturn static_cast<" + node[ENode.FullName] + ">(-1);\n"
            hppCode += "\t}\n"

            hppCode += "\tstatic " + node[ENode.FullName] + " string_to_bitfield(std::string_view value) {\n"
            hppCode += f"\t\tusing type = std::underlying_type_t<{node[ENode.FullName]}>;\n"
            hppCode += f"\t\tstd::string str(value);\n"
            hppCode += f"\t\tstr.erase(std::remove(str.begin(), str.end(), ' '), str.end());\n"
            hppCode += f"\t\tconst std::vector<std::string> tokens = pycppgen_detail::split_string(str, '|');\n"
            hppCode += f"\t\ttype result = 0;\n"
            for k, v in node[ENode.EnumValues].items() :
                hppCode += f"\t\tif (std::ranges::find(tokens, \"{k}\") != tokens.end()) result |= (type){node[ENode.FullName]}::{k};\n"
            hppCode += f"\t\treturn ({node[ENode.FullName]}) result;\n"
            hppCode += "\t}\n"

            #enum value attributes
            hppCode += "\tstatic attribute_map_t enum_value_attributes(" + node[ENode.FullName] + " value) {\n"
            for k, v in node[ENode.EnumValues].items() :
                hppCode += "\t\tif (value == " + node[ENode.FullName] + "::" + k + ") {\n\t\t\treturn " + CodeGenOutputAttributes(v, 3) + ";\n\t\t}\n"
            hppCode += "\t\treturn {};\n"
            hppCode += "\t}\n"

        hppCode = CodeGenOutputMetaFooter(hppCode, node)

    return hppCode, cppCode

#codegen: output file
def CodeGen(filePath : str) :

    #clear data
    TLS().NodesToInclude = []
    TLS().NodeTree = {}
    TLS().NodeStack = [TLS().NodeTree]   

    TLS().NodeList = PerFileData[filePath]["NodeList"]

    cppCode = ""
    hlslCode = ""
    hppCode = "#pragma once\n\n"
    hppCode += "#include \"pycppgen.h\"\n"

    parentPath = pathlib.Path(filePath).parent
    if "IncludedFiles" in PerFileData[filePath] :
        for f in sorted(PerFileData[filePath]["IncludedFiles"]) :
            if f in PerFileData and "NodeList" in PerFileData[f] :
                hppCode += f"#include \"{pathlib.Path(GetOutputFilePath(f)).relative_to(ProjectPath, walk_up=True)}\"\n"

    hppCode += "#include \"" + str(pathlib.Path(filePath).relative_to(ProjectPath, walk_up=True)) + "\"\n\n"

    for key in TLS().NodeList :
        node = TLS().NodeList[key]
        if ENode.Cpp in node and node[ENode.Cpp] :
            newHppCode, newCppCode = CodeGenOutputNode(node)
            hppCode += newHppCode
            cppCode += newCppCode

        if ENode.Hlsl in node and node[ENode.Hlsl]:
            hlslCode += CodeGenHlslNode(hlslCode, node)

    hppCode += "namespace pycppgen_globals {\n"
    
    for _, func in TLS().NodeList.items() :
        if func[ENode.Kind] == EKind.FreeFunction :
            hppCode += "//" + func[ENode.FullName] + "\n"

    for _, var in TLS().NodeList.items() :
        if var[ENode.Kind] == EKind.FreeVariable :
            hppCode += "//" + var[ENode.Type] + " " + var[ENode.FullName] + "\n"

    hppCode += "}\n"

    hppFile = GetOutputFilePath(filePath, "h")
    cppFile = GetOutputFilePath(filePath, "cpp")
    hlslFile = GetOutputFilePath(filePath, "hlsli")
    
    if hppCode == "" :
        if os.path.exists(hppFile) :
            os.remove(hppFile)
    else :
        atomic_print("generating code for: " + hppFile)
        with open(hppFile, mode="wt") as output :
            output.write(hppCode)

    if cppCode == "" :
        if os.path.exists(cppFile) :
            os.remove(cppFile)
    else :
        atomic_print("generating code for: " + cppFile)
        cppCode = f"#include \"{hppFile}\"\n\n" + cppCode
        with open(cppFile, mode="wt") as output :
            output.write(cppCode)

    if hlslCode == "" :
        if os.path.exists(hlslFile) :
            os.remove(hlslFile)
    else :
        atomic_print("generating code for: " + hlslFile)
        with open(hlslFile, mode="wt") as output :
            hlslCode = "#pragma once\n\n" + hlslCode            
            output.write(hlslCode)            

#codegen: emit for each type call
def CodeGenGlobalAddForEachTypeCall(code, node) :
    if node[ENode.Kind] == EKind.Class or node[ENode.Kind] == EKind.Struct : #or node[ENode.Kind] == EKind.ClassTemplate:
        code += f"\t\tvisitor.template operator()<{node[ENode.FullName]}>();\n"
    return code

#codegen: output global file
def CodeGenGlobalHeader(path : str) :
    
    code = """
#pragma once

#ifndef _PYCPPGEN_HEADER_
#define _PYCPPGEN_HEADER_

#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <type_traits>
#include <algorithm>
#include <sstream>
#include <any>

using attribute_map_t = std::unordered_map<std::string_view, std::string_view>;

struct function_parameter_info {
	std::string_view Name;
	std::string_view Type;
	std::string_view DefaultValue;
};

template<typename T = void> struct pycppgen { static constexpr bool is_valid() { return false; } };
template<> struct pycppgen<void> 
{
    inline pycppgen(std::string_view name);
    inline pycppgen(const std::type_info& info) : HashCode(info.hash_code()) {}
    inline const char* name() const;
    inline attribute_map_t get_var_attributes(std::string_view name) const;
    inline void for_each_var(auto visitor, uint32_t maxDepth = UINT_MAX) const;
    template<typename T> static void for_each_var(const T* obj, auto visitor, uint32_t maxDepth = UINT_MAX);
    template<typename T> static void for_each_var(T* obj, auto visitor, uint32_t maxDepth = UINT_MAX);   
    template<typename T, typename R> static bool dump(T& result, const R* obj); 
    template<typename T, typename R> static bool parse(const T& data, R* obj); 

protected:
    decltype(std::declval<std::type_info>().hash_code()) HashCode;
};

template<typename T> requires (!std::is_pointer_v<T>)
auto pycppgen_of(const T& t) 
{
	return pycppgen<std::decay_t<T>>(); 
}

template<typename T> requires (std::is_pointer_v<T>)
auto pycppgen_of(const T t) 
{
	return pycppgen<void>(typeid(*t));
}

namespace pycppgen_detail
{
	template <typename T> constexpr size_t get_rank() { return std::rank_v<T>; }
	template <typename T> constexpr std::vector<size_t> get_extents() { return {}; }

	template <typename T> constexpr std::vector<size_t> get_extents(const T& arr) { return {}; }
	template <typename T, std::size_t N> constexpr std::vector<size_t> get_extents(const std::array<T, N>& arr) { return { N }; }
	template <typename T, std::size_t N> constexpr std::vector<size_t> get_extents(T (&)[N]) { return { N }; }
	
	template <typename T, std::size_t N, std::size_t M, typename... Dims>
	constexpr std::vector<std::size_t> get_extents(T (&)[N][M], Dims... dims) {
	    std::vector<size_t> extents = {N, M};
	    (extents.push_back(dims), ...);
	    return extents;
	}

	template <typename T, std::size_t N, std::size_t M, std::size_t B, typename... Dims>
	constexpr std::vector<std::size_t> get_extents(T (&)[N][M][B], Dims... dims) {
	    std::vector<size_t> extents = {N, M, B};
	    (extents.push_back(dims), ...);
	    return extents;
	}

    inline std::vector<std::string> split_string(const std::string_view str, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(std::string{str});
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
}

#endif //_PYCPPGEN_HEADER_
    """

    with open(path + "/pycppgen.h", mode="wt") as output :
        output.write(code)

def CodeGenGlobal(path : str) :
    global PerFileData
    
    CodeGenGlobalHeader(path)

    #pycppgen.gen.h
    code = ""
    code += "#pragma once\n\n"
    code += "\n"
    code += "#include \"pycppgen.h\"\n"
    for k in sorted(PerFileData) :
        if not k.endswith(".gen.h") :
            relPath = pathlib.Path(GetOutputFilePath(k)).relative_to(ProjectPath, walk_up=True)
            relPath = str(relPath).replace('\\', '/')
            code += f"#include \"{relPath}\"\n"

    code += "\nnamespace pycppgen_globals\n{\n"

    code += "\tstatic void for_each_type(auto visitor) {\n"
    for _, node in TLS().NodeList.items() :
        if ENode.Cpp in node and node[ENode.Cpp]:
            code = CodeGenGlobalAddForEachTypeCall(code, node)
    code += "\t}\n\n"

    code += "\tstatic void for_each_enum(auto visitor)\n"
    code += "\t{\n"
    for _, node in TLS().NodeList.items() :
        if node[ENode.Kind] == EKind.Enum :
            code += f"\t\tvisitor.template operator()<{node[ENode.FullName]}>();\n"
    code += "\t}\n\n"

    code += "\tstatic void for_each_type_call_static_by_name(std::string_view funcName) {\n"
    for _, node in TLS().NodeList.items() :
        if ENode.Cpp in node and node[ENode.Cpp] and (node[ENode.Kind] == EKind.Class or node[ENode.Kind] == EKind.Struct) and ENode.StaticFunctions in node :
            for _, func in node[ENode.StaticFunctions].items() :
                if (not ENode.Parameters in func or len(func[ENode.Parameters]) == 0) and (not ENode.ReturnType in func or func[ENode.ReturnType] == "void"):
                    code += f"\t\tpycppgen<{node[ENode.FullName]}>::call_function(funcName);\n"
    code += "\t}\n"
    code += "}\n\n"

    code += "const char* pycppgen<void>::name() const\n"
    code += "{\n"
    code += "\tif (false) {}\n"
    for _, node in TLS().NodeList.items() :
        if ENode.Cpp in node and node[ENode.Cpp] and node[ENode.Kind] == EKind.Class or node[ENode.Kind] == EKind.Struct :
            code += f"\telse if (HashCode == typeid({node[ENode.FullName]}).hash_code())\n"
            code += f"\t\treturn pycppgen<{node[ENode.FullName]}>::name();\n"
    code += "\treturn \"\";\n"
    code += "}\n\n"

    code += "template<typename T> void pycppgen<void>::for_each_var(const T* obj, auto visitor, uint32_t maxDepth)\n"
    code += "{\n"
    code += f"\tconst auto hashCode = obj ? typeid(*obj).hash_code() : 0;\n"
    code += "\tif (false) {}\n"
    for _, node in TLS().NodeList.items() :
        if ENode.Cpp in node and node[ENode.Cpp] and node[ENode.Kind] == EKind.Class or node[ENode.Kind] == EKind.Struct :
            code += f"\telse if (hashCode == typeid({node[ENode.FullName]}).hash_code())\n"
            code += f"\t\tpycppgen<{node[ENode.FullName]}>::for_each_var((const {node[ENode.FullName]}*)obj, visitor, maxDepth - 1);\n"
    code += "}\n\n"

    code += "template<typename T> void pycppgen<void>::for_each_var(T* obj, auto visitor, uint32_t maxDepth)\n"
    code += "{\n"
    code += f"\tconst auto hashCode = obj ? typeid(*obj).hash_code() : 0;\n"
    code += "\tif (false) {}\n"
    for _, node in TLS().NodeList.items() :
        if ENode.Cpp in node and node[ENode.Cpp] and node[ENode.Kind] == EKind.Class or node[ENode.Kind] == EKind.Struct :
            code += f"\telse if (hashCode == typeid({node[ENode.FullName]}).hash_code())\n"
            code += f"\t\tpycppgen<{node[ENode.FullName]}>::for_each_var(({node[ENode.FullName]}*)obj, visitor, maxDepth - 1);\n"
    code += "}\n\n"

    code += "template<typename T, typename R> bool pycppgen<void>::dump(T& result, const R* obj)\n"
    code += "{\n"
    code += f"\tconst auto hashCode = obj ? typeid(*obj).hash_code() : 0;\n"
    code += "\tif (false) {}\n"
    for _, node in TLS().NodeList.items() :
        if ENode.Cpp in node and node[ENode.Cpp] and (node[ENode.Kind] == EKind.Class or node[ENode.Kind] == EKind.Struct) and kSerialize in node[ENode.Attributes] :
            code += f"\telse if (hashCode == typeid({node[ENode.FullName]}).hash_code())\n"
            code += f"\t\treturn pycppgen<{node[ENode.FullName]}>::dump(result, (const {node[ENode.FullName]}*)obj);\n"
    code += "\treturn false;\n"
    code += "}\n\n"

    code += "template<typename T, typename R> bool pycppgen<void>::parse(const T& data, R* obj)\n"
    code += "{\n"
    code += f"\tconst auto hashCode = obj ? typeid(*obj).hash_code() : 0;\n"
    code += "\tif (false) {}\n"
    for _, node in TLS().NodeList.items() :
        if ENode.Cpp in node and node[ENode.Cpp] and (node[ENode.Kind] == EKind.Class or node[ENode.Kind] == EKind.Struct) and kSerialize in node[ENode.Attributes] :
            code += f"\telse if (hashCode == typeid({node[ENode.FullName]}).hash_code())\n"
            code += f"\t\treturn pycppgen<{node[ENode.FullName]}>::parse(data, (const {node[ENode.FullName]}*)obj);\n"
    code += "\treturn false;\n"
    code += "}\n\n"


    code += "inline pycppgen<void>::pycppgen(std::string_view name)\n"
    code += "{\n"
    for _, node in TLS().NodeList.items() :
        if ENode.Cpp in node and node[ENode.Cpp] and node[ENode.Kind] == EKind.Class or node[ENode.Kind] == EKind.Struct :
            if code.endswith("{\n") : code += "\t"
            else : code += f"\telse "
            code += f"if (name == \"{node[ENode.FullName]}\" || name == \"{node[ENode.Name]}\")\n"
            code += f"\t\tHashCode = typeid({node[ENode.FullName]}).hash_code();\n"
    code += "}\n\n"
    
    code += "inline attribute_map_t pycppgen<void>::get_var_attributes(std::string_view name) const\n"
    code += "{\n"
    code += "\tif (false) {}\n"
    for _, node in TLS().NodeList.items() :
        if ENode.Cpp in node and node[ENode.Cpp] and node[ENode.Kind] == EKind.Class or node[ENode.Kind] == EKind.Struct :
            code += f"\telse if (HashCode == typeid({node[ENode.FullName]}).hash_code())\n"
            code += f"\t\treturn pycppgen<{node[ENode.FullName]}>::get_var_attributes(name);\n"
    code += "\treturn {};\n"
    code += "}\n\n"

    code += "inline void pycppgen<void>::for_each_var(auto visitor, uint32_t maxDepth) const\n"
    code += "{\n"
    for _, node in TLS().NodeList.items() :
        if ENode.Cpp in node and node[ENode.Cpp] and node[ENode.Kind] == EKind.Class or node[ENode.Kind] == EKind.Struct :
            code += f"\tif (HashCode == typeid({node[ENode.FullName]}).hash_code())\n"
            code += f"\t\tpycppgen<{node[ENode.FullName]}>::for_each_var(visitor, maxDepth - 1);\n"
    code += "}\n\n"

    if IsFileDifferent(path + "\\pycppgen.gen.h", code) :
        with open(path + "\\pycppgen.gen.h", mode="wt") as file :
            file.write(code)

def IsFileUpToDate(src : str | None, dst : str | None) :
    if src == None : return False
    if dst == None : return True

    if not os.path.exists(str(dst)) or not os.path.exists(str(src)) :
        return False

    srcTime = os.path.getmtime(str(src))
    dstTime = os.path.getmtime(str(dst))

    return srcTime < dstTime  

def IsOutputUpToDate(file : str) :
    outputFile = GetOutputFilePath(file)

    return IsFileUpToDate(file, outputFile)

def FileContainsPyCppGenTag(file : str) :
    global FilesWithPyCppGenTag

    if file in FilesWithPyCppGenTag :
        return FilesWithPyCppGenTag[file]

    if os.path.exists(file) :
        with open(file) as f :
            data = f.read()
            if data.find("$[[pycppgen") != -1 or data.find("pyhlslgen") != -1:
                FilesWithPyCppGenTag[file] = True
                return True

    FilesWithPyCppGenTag[file] = False
    return False

def IsFileDifferent(file, content) :
    if not os.path.exists(file) :
        return content != ""

    fileContent = ""
    with open(file, "rt") as f :
        fileContent = f.read()
    
    return fileContent != content

def ProcessFile(file : str, compilerOptions) :
    global OutdatedFiles, FilesToCodeGen, PerFileData

    file = ResolvePath(file)

    if file in CachedPerFileData :
        PerFileData[file] = CachedPerFileData[file]
    else :
        PerFileData[file] = {}

    if not "IncludedFiles" in PerFileData[file] :
        PerFileData[file]["IncludedFiles"] = []

    fileTime = 0
    if os.path.exists(GetOutputFilePath(file)) :
        fileTime = os.path.getmtime(GetOutputFilePath(file))

    isOutdated = file in OutdatedFiles
    needsCodeGen = isOutdated
    needsParseTU = False

    # if the input or output files are newer than the cache, force re-parsing
    if not IsFileUpToDate(file, CacheFile) or not IsFileUpToDate(GetOutputFilePath(file), CacheFile) :
        needsParseTU = True
        if not isOutdated :
            atomic_print(f"outdated cache entry for {file}") 

    tu = None
    tmpFilePath = None
    if needsParseTU :
        tu, tmpFilePath = ParseFile(file, compilerOptions)

        includedFiles = []
        for f in tu.get_includes() :
            includedFiles.append(ResolvePath(f.include.name))
        PerFileData[file]["IncludedFiles"] = list(set(includedFiles))

    for f in PerFileData[file]["IncludedFiles"] :
        if not f.endswith("pycppgen.h") and os.path.getmtime(f) > fileTime :
            needsCodeGen = True
            if not f in FilesToParse and FileContainsPyCppGenTag(f) :
                FilesToParse.append(f)
            if not isOutdated : 
                atomic_print(f"outdated include {f} in {file}")

    if needsParseTU : 
        ParseTranslationUnit(tu, tmpFilePath)
        PerFileData[file]["NodeList"] = TLS().NodeList

    if needsParseTU or needsCodeGen :
        FilesToCodeGen.add(file)

def show_usage() :
        print("usage pycppgen.py <project-path> <options>")
        print("options:")
        print("    -I<include_dir>")
        print("    -D<definition>")
        print("    --I<include_dirs_separated_by_semicolons>")
        print("    --D<definitions_separated_by_semicolons>")
        print("    --P<dependency_dirs_separated_by_semicolons>")

def main(args : list) :
    global FilesToParse, PerFileData, ProjectPath, CacheFile, OutdatedFiles, CachedPerFileData, FilesToCodeGen

    if len(args) < 1 :
        show_usage()
        exit(-1)

    ProjectPath = str(pathlib.Path(args[0]).resolve())

    Dependencies = []
    for arg in list(args[1:]) :
        if arg.startswith("--I") :
            args.remove(arg)
            arg = arg[3:]
            if not arg:
                print("error: no includes after --I. Did you add a space?")
                print("Expected format: --I<include_dirs_separated_by_semicolons>")
                exit(-1)
            for i in arg.split(";") :
                if not pathlib.Path(i).is_absolute() :
                    i = ResolvePath(os.path.join(ProjectPath, i))
                args.append(f"-I{i}")
        if arg.startswith("--D") :
            args.remove(arg)
            arg = arg[3:]
            if not arg:
                print("error: no defines after --D. Did you add a space?")
                print("Expected format: --D<definitions_separated_by_semicolons>")
                exit(-1)
            for i in arg.split(";") :
                args.append(f"-D{i}")
        if arg.startswith("--P") :
            args.remove(arg)
            arg = arg[3:]
            if not arg:
                print("error: no dependencies after --P. Did you add a space?")
                print("Expected format: --P<dependency_dirs_separated_by_semicolons>")
                exit(-1)
            for i in arg.split(";") :
                if not pathlib.Path(i).is_absolute() :
                    i = ResolvePath(os.path.join(ProjectPath, i))
                Dependencies.append(i)
                args.append(f"-I{i}")

    OutdatedFiles = set()
    FilesToCodeGen = set()
    CacheFile = os.path.join(ProjectPath, "pycppgen.cache")

    atomic_print("parsing path: " + ProjectPath)

    if os.path.exists(ProjectPath + "\\pycppgen.gen.cpp"):
        os.remove(ProjectPath + "\\pycppgen.gen.cpp")

    #find headers with the pycppgen tag and the previously generated files
    FilesToParse = []
    OldGenFiles = []
    for root, _, files in os.walk(ProjectPath):
        for file in files:
            if file.endswith(".pycppgentmp") or file.find("__pycppgen_tmp") != -1:
                os.remove(root + "\\" + file)
                continue
            if re.match(r".*\.h$", file) and not re.match(r".*\.gen.h$", file) :
                filePath = os.path.join(root, file)
                if FileContainsPyCppGenTag(filePath) :
                    FilesToParse.append(os.path.join(root, file))
            if file != "pycppgen.gen.h" and re.match(r".*\.gen.h$", file) :
                OldGenFiles += [os.path.join(root, file)]
    
    compilerOptions = []
    if len(args) > 1 :
        compilerOptions = args[1:]

    GenFiles = list(map(lambda x : GetOutputFilePath(x), FilesToParse))
    OldGenFiles = list(map(lambda x : ResolvePath(x), OldGenFiles))

    #if the script is newer than the cache, remove all files as we need to rebuild everything
    if not IsFileUpToDate(inspect.getsourcefile(sys.modules[__name__]), CacheFile) :
        atomic_print("Outdated file cache")
        for file in OldGenFiles :
            if os.path.exists(file) :
                os.remove(file)
        OldGenFiles = []
        OutdatedFiles = set(FilesToParse)
    else :
        #mark the outdated files
        for file in FilesToParse :
            if not IsOutputUpToDate(file) :
                atomic_print("Outdated file: " + file)
                OutdatedFiles.add(file)

    FilesToRemove = list(set(OldGenFiles).difference(GenFiles))
    FilesToAdd = list(set(GenFiles).difference(OldGenFiles))
     
    #load cache
    CachedPerFileData = {}
    if os.path.exists(CacheFile) :
        with open(CacheFile, "rt") as file :
            try :
                CachedPerFileData = json.loads(file.read())
            except :
                CachedPerFileData = {}

    PerFileData = {}

    if DebugMode :
        for file in FilesToParse :
            ProcessFile(file, compilerOptions)
    else :
        with ThreadPoolExecutor() as pool :
            for file in FilesToParse :
                pool.submit(ProcessFile, file, compilerOptions)

    if DebugMode :
        for file in FilesToCodeGen :
            CodeGen(file)
    else :
        with ThreadPoolExecutor() as pool :
            for file in FilesToCodeGen :
                pool.submit(CodeGen, file)

    for dep in Dependencies :
        depPath = ResolvePath(os.path.join(dep, "pycppgen.cache"))
        if os.path.exists(depPath) :
            with open(depPath, "rt") as file :
                try :
                    depCachedData = json.loads(file.read())
                    PerFileData.update(depCachedData)
                except :
                    atomic_print("failed to load dependency data: " + dep)

    #clear data
    TLS().NodeList = {}

    for n, v in sorted(PerFileData.items()) : 
        if "NodeList" in v :
            TLS().NodeList.update(v["NodeList"])

    if len(OutdatedFiles) > 0 or not "pycppgen.gen.h" in CachedPerFileData or CachedPerFileData["pycppgen.gen.h"] != TLS().NodeList :
        atomic_print(f"global code gen step, outdated files -> {OutdatedFiles}")
        FilesToParse.append(os.path.join(ProjectPath, "\\pycppgen.h"))
        CodeGenGlobal(ProjectPath)
    PerFileData["pycppgen.gen.h"] = TLS().NodeList

    #save cache
    with open(CacheFile, "wt") as file :
        file.write(json.dumps(PerFileData))

    #remove old files
    for file in FilesToRemove :
        if os.path.exists(file) :
            os.remove(file)

if __name__ == "__main__":
    main(sys.argv[1:])

