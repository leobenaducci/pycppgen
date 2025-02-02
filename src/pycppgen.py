import os
import pathlib
import sys
import clang.cindex
import re
import inspect
import itertools
import threading
import json
from concurrent.futures import ThreadPoolExecutor
from clang.cindex import CursorKind
from clang.cindex import AccessSpecifier

DebugMode = False

ENodeName = "name"
ENodeFullName = "full_name"
ENodeKind = "kind"
ENodeType = "type"
ENodeUnderlyingType = "underlying_type"
ENodeAccess = "access"
ENodeScope = "scope"
ENodeVariables = "variables"
ENodeStaticVariables = "static_variables"
ENodeFunctions = "functions"
ENodeStaticFunctions = "static_functions"
ENodeFreeVariables = "free_variables"
ENodeFreeFunctions = "free_functions"
ENodeParents = "parents"
ENodeEnums = "enums"
ENodeStructs = "structs"
ENodeNamespaces = "namespaces"
ENodeNamespace = "namespace"
ENodeParameters = "parameters"
ENodeEnumValues = "enum_values"
ENodeMetaTemplateDecl = "meta_template_decl"
ENodeReturnType = "return_type"
ENodeAttributes = "attributes"
ENodeDefaultValue = "default_value"
ENodeMemberAttributesOverride = "member_attribs_override"

EKindUnknown = "kind_unknown"
EKindNamespace = "kind_namespace"
EKindAlias = "kind_alias"
EKindEnum = "kind_enum"
EKindEnumValue = "kind_enum_value"
EKindClassTemplate = "kind_class_template"
EKindClass = "kind_class"
EKindStruct = "kind_struct"
EKindFunction = "kind_function"
EKindParameter = "kind_parameter"
EKindVariable = "kind_variable"
EKindFreeFunction = "kind_free_function"
EKindFreeVariable = "kind_free_variable"
EKindTemplateTypeParameter = "kind_template_type_parameter"
EKindTemplateNonTypeParameter = "kind_template_non_type_parameter"
EKindTemplateTemplateParameter = "kind_template_template_parameter"

EParseCommentsBeforeDecl = "comments_before_decl"
EParseCommentsAfterDecl = "comments_after_decl"

EInvalid = "invalid"

ParseCommentsMode = {
    EKindUnknown : EParseCommentsBeforeDecl,
    EKindNamespace : EParseCommentsBeforeDecl,
    EKindAlias : EParseCommentsBeforeDecl,
    EKindEnum : EParseCommentsBeforeDecl,
    EKindEnumValue : EParseCommentsAfterDecl,
    EKindClassTemplate : EParseCommentsBeforeDecl,
    EKindClass : EParseCommentsBeforeDecl,
    EKindStruct : EParseCommentsBeforeDecl,
    EKindFunction : EParseCommentsBeforeDecl,
    EKindParameter : EParseCommentsAfterDecl,
    EKindVariable : EParseCommentsBeforeDecl,
    EKindFreeFunction : EParseCommentsBeforeDecl,
    EKindFreeVariable : EParseCommentsBeforeDecl,
    EKindTemplateTypeParameter : EParseCommentsBeforeDecl,
    EKindTemplateNonTypeParameter : EParseCommentsBeforeDecl,
    EKindTemplateTemplateParameter : EParseCommentsBeforeDecl,
}

FilesWithPyCppGenTag = dict()

TLS_Dict = {}

class TLS_Data:
    def __init__(self):
        self.NodesToInclude = []
        self.NodeList = {}
        self.NodeTree = {}
        self.NodeStack = [self.NodeTree] 

def TLS() :
    global TLS_Dict

    ident = threading.current_thread().ident
    if not ident in TLS_Dict :
        TLS_Dict[ident] = TLS_Data()

    return TLS_Dict[ident]

#try to parse the comments before or after the cursor (hacky but, cursor.raw_comments isn't working as expected)
def ParseComments(cursor, kind : str = EParseCommentsBeforeDecl) :
   
    try :
        preDeclComments = not kind in ParseCommentsMode or ParseCommentsMode[kind] == EParseCommentsBeforeDecl
        parent = cursor.semantic_parent

        tokens = list(parent.get_tokens())
        firstToken = list(cursor.get_tokens())[0]

        firstTokenIndex = tokens.index(next(x for x in tokens if x.location.line == firstToken.location.line))

        if preDeclComments :
            lastTokenIndex = firstTokenIndex
            while firstTokenIndex > 0 and tokens[firstTokenIndex - 1].kind == clang.cindex.TokenKind.COMMENT :
                firstTokenIndex -= 1
        else :
            while firstTokenIndex < lastTokenIndex and tokens[firstTokenIndex].kind != clang.cindex.TokenKind.COMMENT :
                firstTokenIndex += 1
            lastTokenIndex = firstTokenIndex
            while lastTokenIndex < len(tokens) and tokens[lastTokenIndex].kind == clang.cindex.TokenKind.COMMENT :
                lastTokenIndex += 1

    except :
        return {}
    
    attribs = ""
    if firstTokenIndex != -1 and lastTokenIndex != -1 :
        for t in tokens[firstTokenIndex:lastTokenIndex] :
            if t.kind == clang.cindex.TokenKind.COMMENT :
                attribs += t.spelling + "\n"

    result = {}
    oneMatch = False

    for line in attribs.splitlines() :
        m = re.match(r".*\$\[\[pycppgen(?>(?>\s+((?>\s|\w|\W)*)\]\])|(?>\]\]))", line, flags=re.IGNORECASE|re.MULTILINE)
        if m == None : continue
        oneMatch = True

        if m.groups() == None : continue

        comments = ""
        for g in m.groups() :
            if g != None and len(g) > 0:
                comments += g

        if len(comments) == 0 : continue

        comments = comments.replace(" ", "").split(";")
        for g in comments :
            if len(g) == 0 : continue

            key = ""
            value = ""

            kv = g.split("=")
            if len(kv) == 0 : continue
            if len(kv) > 0 : key = kv[0]
            if len(kv) > 1 : value = kv[1]

            if key.lower() == "exclude" : result["include"] = str(bool(value != None and value == True))
            else : result[key] = value

    if oneMatch and not "include".casefold() in result :
        result["include"] = True

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

    TLS().NodeStack[-1][node_type][node[ENodeFullName]] = node

    if appendToList :
        TLS().NodeList[node[ENodeFullName]] = node

#common node push code
def PushNode(cursor, kind : str = EInvalid) :
    node = dict()
    node[ENodeName] = str(cursor.spelling)
    node[ENodeFullName] = GetFullName(cursor)
    node[ENodeKind] = kind
    if kind == EKindClassTemplate :
        node[ENodeType] = node[ENodeFullName]
    else :
        node[ENodeType] = str(cursor.type.spelling)
    node[ENodeAccess] = str(cursor.access_specifier)
    node[ENodeScope] = GetScope(cursor)
    node[ENodeAttributes] = ParseComments(cursor, kind)
    node[ENodeNamespace] = ""

    ns_parent = cursor.semantic_parent
    while ns_parent and ns_parent.kind == CursorKind.NAMESPACE :
        node[ENodeNamespace] = ns_parent.spelling + "::" + node[ENodeNamespace]
        ns_parent = ns_parent.semantic_parent

    if node[ENodeNamespace].endswith("::") :
        node[ENodeNamespace] = node[ENodeNamespace][:-2]
    
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
    node = PushNode(cursor, EKindFunction)
    node[ENodeFullName] = node[ENodeFullName][:node[ENodeFullName].find("(")]

    #get the return type
    node[ENodeReturnType] = cursor.result_type.spelling

    #and parameters
    node[ENodeParameters] = dict()
    for child in cursor.get_children() :
        if child.kind == CursorKind.PARM_DECL:
            param = PushNode(child, EKindParameter)
            param[ENodeDefaultValue] = ""
            PopNode()

            #append parameter to parent (function)
            AppendToStackTop(param, ENodeParameters)

    PopNode()

    #append function to parent (struct/class/namespace/translation_unit)
    if isFreeFunction : 
        node[ENodeKind] = EKindFreeFunction
        AppendToStackTop(node, ENodeFreeFunctions, True)
    elif cursor.storage_class == clang.cindex.StorageClass.STATIC :
        AppendToStackTop(node, ENodeStaticFunctions)
    else :
        AppendToStackTop(node, ENodeFunctions)

    return node

#parse variable or class/struct field
def ParseVar(cursor, isFreeVariable : bool = False) :

    node = PushNode(cursor, EKindVariable)
    PopNode()

    if isFreeVariable : 
        node[ENodeKind] = EKindFreeVariable
        AppendToStackTop(node, ENodeFreeVariables, True)
    elif cursor.storage_class == clang.cindex.StorageClass.STATIC :
        AppendToStackTop(node, ENodeStaticVariables)
    else :
        AppendToStackTop(node, ENodeVariables)
    
    return node

#parse struct/class
def ParseStruct(cursor) :
    kind = EInvalid
    if cursor.kind == CursorKind.CLASS_TEMPLATE :
        kind = EKindClassTemplate
    elif cursor.kind == CursorKind.CLASS_DECL :
        kind = EKindClass
    else :
        kind = EKindStruct

    node = PushNode(cursor, kind)
    node[ENodeMetaTemplateDecl] = ""
    node[ENodeFunctions] = {}
    node[ENodeMemberAttributesOverride] = {}

    for child in cursor.get_children() :
        
        #inheritance
        if child.kind == CursorKind.CXX_BASE_SPECIFIER :
            if child.referenced :
                childFullName = GetFullName(child.referenced)
                flags = ParseComments(child.referenced, EKindUnknown)
                if "include" in flags : 
                    if str(flags["include"]) == "False" :
                        continue
                elif not childFullName in TLS().NodesToInclude :
                    continue
                AppendToStackTop({ENodeFullName: childFullName}, ENodeParents)
            continue

        #template parameters
        if child.kind == CursorKind.TEMPLATE_TYPE_PARAMETER or child.kind == CursorKind.TEMPLATE_NON_TYPE_PARAMETER or child.kind == CursorKind.TEMPLATE_TEMPLATE_PARAMETER:
            
            kind = EInvalid
            if child.kind == CursorKind.TEMPLATE_TYPE_PARAMETER :
                kind = EKindTemplateTypeParameter
            elif child.kind == CursorKind.TEMPLATE_NON_TYPE_PARAMETER :
                kind = EKindTemplateNonTypeParameter
            elif child.kind == CursorKind.TEMPLATE_TEMPLATE_PARAMETER :
                kind = EKindTemplateTemplateParameter

            param = PushNode(child, kind)
            PopNode()

            if child.kind == CursorKind.TEMPLATE_TYPE_PARAMETER :
                node[ENodeMetaTemplateDecl] += "typename " + param[ENodeName] + ", "
            elif child.kind == CursorKind.TEMPLATE_NON_TYPE_PARAMETER :
                node[ENodeMetaTemplateDecl] += param[ENodeType] + " " + param[ENodeName] + ", "
            elif child.kind == CursorKind.TEMPLATE_TEMPLATE_PARAMETER :
                node[ENodeMetaTemplateDecl] += "template " + param[ENodeName] + ", "

            AppendToStackTop(param, ENodeParameters)

            continue

        flags = ParseComments(child, EKindUnknown)
        if not "include" in flags or flags["include"] == False :
            continue

        #class functions
        if child.kind == CursorKind.CXX_METHOD:
            fn = ParseFunction(child, False)
            continue

        #static variables?
        if child.kind == CursorKind.VAR_DECL :
            var = ParseVar(child, False)
            continue

        #member variables (field)
        if child.kind == CursorKind.FIELD_DECL :
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
            if name in node[ENodeMemberAttributesOverride] :
                node[ENodeMemberAttributesOverride][name].update(attribs)
            else :
                node[ENodeMemberAttributesOverride][name] = attribs
            continue

        ParseCursor(child)

    #fixup template declaration string
    if ENodeMetaTemplateDecl in node :
        if node[ENodeMetaTemplateDecl].endswith(", ") :
            node[ENodeMetaTemplateDecl] = node[ENodeMetaTemplateDecl][:-2]

    PopNode()

    return node

#Parse enum definitions
def ParseEnum(cursor, isGlobal : bool = False) :

    node = PushNode(cursor, EKindEnum)

    #underlying type
    node[ENodeUnderlyingType] = str(cursor.enum_type.spelling)

    #values
    node[ENodeEnumValues] = dict()
    for child in cursor.get_children() :
        if child.kind == CursorKind.ENUM_CONSTANT_DECL :
            node[ENodeEnumValues][child.spelling] = dict()
            node[ENodeEnumValues][child.spelling]["value"] = str(child.enum_value)
            node[ENodeEnumValues][child.spelling][ENodeAttributes] = ParseComments(child, EKindEnumValue)

    PopNode()

    AppendToStackTop(node, ENodeEnums, isGlobal)

#append to list and recurse
def ParseNamespace(cursor) :
    node = PushNode(cursor, EKindNamespace)
    for child in cursor.get_children() :
        ParseCursor(child)
    PopNode()

    AppendToStackTop(node, ENodeNamespaces, True)

#using/typedef
def ParseTypeAlias(cursor) :
    node = PushNode(cursor, EKindAlias)
    node[ENodeUnderlyingType] = str(cursor.underlying_typedef_type.spelling)
    PopNode()

    AppendToStackTop(node, ENodeVariables, True)

#generic parse call
def ParseCursor(cursor, forceInclude = False) :
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

    #check if it should be parsed
    if not forceInclude :
        flags = ParseComments(cursor, EKindUnknown)
        if "include" in flags : 
            if str(flags["include"]) == "False" :
                return
        elif not fullName in TLS().NodesToInclude :
            return

    #ignore this kind for now
    if cursor.kind == CursorKind.TYPE_REF or cursor.kind == CursorKind.TEMPLATE_REF or cursor.kind == CursorKind.NAMESPACE_REF:
        return

    isStruct = cursor.kind == CursorKind.STRUCT_DECL or cursor.kind == CursorKind.CLASS_DECL
    isStruct |= cursor.kind == CursorKind.CLASS_TEMPLATE or cursor.kind == CursorKind.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION
    if isStruct :
        if cursor.is_definition() :
            node = ParseStruct(cursor)   
            AppendToStackTop(node, ENodeStructs)
            TLS().NodeList[node[ENodeFullName]] = node
        return

    if cursor.kind == CursorKind.ENUM_DECL :
        if cursor.is_definition() :
            ParseEnum(cursor, True)
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

def GetOutputFilePath(filePath : str, ext : str = "h") :
    extStart = filePath.rfind(".")
    outputPath = filePath[:extStart]
    outputPath += f".gen.{ext}"
    return str(pathlib.Path(outputPath).resolve())

def GetOutputFileName(filePath : str, ext  : str = "h") :
    outputPath = pathlib.Path(GetOutputFilePath(filePath, ext))
    return str(outputPath.relative_to(outputPath.parent))

#parse a header file
def CompileFile(filePath : str, options : list) :
    args = ['-x', 'c++', '-std=c++20', "-DPYCPPGEN"] + options
    idx = clang.cindex.Index.create()
    tu = idx.parse(filePath, args = args, options = clang.cindex.TranslationUnit.PARSE_INCOMPLETE | clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)

    if DebugMode :
        # Print diagnostics
        for diag in tu.diagnostics:
            print(diag)

    return tu

def ParseTranslationUnit(tu) :
    global FilesToParse

    #initialize data
    TLS().NodesToInclude = []
    TLS().NodeList = {}
    TLS().NodeTree = {}
    TLS().NodeStack = [TLS().NodeTree] 
    
    #first = next(x for x in tu.cursor.get_children() if x.location.file and x.location.file.name in FilesToParse)
    filteredChildren = list(filter(lambda x: x.location.file and str(pathlib.Path(x.location.file.name).resolve()) in FilesToParse, tu.cursor.get_children()))
    for cursor in  filteredChildren :
        ParseCursor(cursor)

    return {
            "NodeList": TLS().NodeList,
            "NodesToInclude": TLS().NodesToInclude,
            "NodeTree": TLS().NodeTree,
            "NodeStack": TLS().NodeStack
        }

#parse a header file
def ParseFile(filePath : str, options : list) :
    with open(filePath) as file:
        for line in file.readlines() :
            m = re.match(r"\s*\/\/\s*\$\[\[pycppgen-include\s+((?>\w|\W)*)\]\]", line, flags=re.MULTILINE|re.IGNORECASE)
            if not m : continue
            for g in m.groups() :
                TLS().NodesToInclude += g.replace(" ", ";").replace(",", ";").split(";")

    tu = CompileFile(filePath, options)

    return ParseTranslationUnit(tu)

#codegen: common type header 
def CodeGenOutputMetaHeader(code, node) :
    global pycppdefine

    #make a unique name
    pycppdefine = "_pycppgen_" + node[ENodeFullName].replace("::", "_").replace("<","_").replace(">","_")

    #tag the begining of autogen code
    code += f"//<autogen_{pycppdefine}>\n\n"

    #ifndef pycppgen_<nodefullname>
    code += f"#ifndef {pycppdefine}\n"
    #define pycppgen_<nodefullname>
    code += f"#define {pycppdefine}\n\n"

    #create the specialized pycppgen struct
    #code 'template<> struct pycppgen<type_name> {
    code += "template<"
    if ENodeMetaTemplateDecl in node :
        code += node[ENodeMetaTemplateDecl]
    code += ">\nstruct pycppgen<" + node[ENodeFullName] + "> {\n"
    code += "\tstatic constexpr bool is_valid() { return true; }\n"

    return code

#codegen: common type footer
def CodeGenOutputMetaFooter(code, node) :
    global pycppdefine

    code += "};\n\n"

    code += f"#endif //{pycppdefine}\n"

    #tag the end of autogen code
    code += f"//</autogen_{pycppdefine}>\n\n"

    pycppdefine = None

    return code

#codegen: emit attributes as array of pairs
def CodeGenOutputAttributes(node, depth = 0) :
    if ENodeAttributes in node and len(node[ENodeAttributes]) > 0 :
        attribs = node[ENodeAttributes]

        depth += 1
        result = "{\n"

        for k, v in attribs.items() :
            if k == "include" : continue
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
    decl = f"static_{isStatic}_{funcNode[ENodeType]}"
    numParams = len(funcNode[ENodeParameters])
    isConst = decl.endswith("const")
      
    #if call_function with the current return value and parameters doesn't exists, create it
    if not decl in declarations :
        #code 'static bool call_function(std::string view name, '
        declarations[decl] = "\tstatic bool call_function(std::string_view name, " 
        if not isStatic :
            if isConst :
                #code 'const '
                declarations[decl] += "const " 
            #code '<type>* object, '
            declarations[decl] += node[ENodeType] + "* object, "

        if funcNode[ENodeReturnType] != "void" :
            #code '<return_type>& result, '
            declarations[decl] += f"{funcNode[ENodeReturnType]}& result, "

        paramNum = 1
        for _, pv in funcNode[ENodeParameters].items() :
            #code '_<param_num, '
            declarations[decl] += f"{pv[ENodeType]} _{str(paramNum)}, "
            paramNum += 1

        #remove last ', ' and close parenthesis 
        declarations[decl] = declarations[decl][:-2] + ") {\n"
    
    #append name comparison + call code
    #code '     if (name == "<function_name>") {
    declarations[decl] += "\t\tif (name == \"" + funcNode[ENodeName] + "\") {\n"
    declarations[decl] += "\t\t\t"

    if funcNode[ENodeReturnType] != "void" :
        #code 'result = '
        declarations[decl] += "result = "

    if isStatic :   
        #code '<class_name>::<function_name>('
        declarations[decl] += f"{node[ENodeType]}::{funcNode[ENodeName]}("
    else :          
        #code 'object-><function_name>('
        declarations[decl] += f"((access_helper*)object)->{funcNode[ENodeName]}("

    #code '[_1, _2...]'
    if numParams > 0 :
        paramNum = 1
        for _, pv in funcNode[ENodeParameters].items() :
            declarations[decl] += " _" + str(paramNum) + ", "
            paramNum += 1
        declarations[decl] = declarations[decl][:-2] + ");\n"
    else :
        declarations[decl] += ");\n"

    #code '         return true;'
    #code '     }'
    declarations[decl] += "\t\t\treturn true;\n\t\t}\n"

def GenerateMemberInfo(node, var, infoName) :
    result = ""

    varName = var[ENodeName]
    varType = f"decltype(access_helper::{varName})"

    result += f"\t\tmember_variable_info {infoName};\n"
    #variable name
    result += f"\t\t{infoName}.Name = \"{varName}\";\n"
    #full name
    result += f"\t\t{infoName}.FullName = \"{var[ENodeFullName]}\";\n"
    #get the variable typeid name using the access_helper
    result += f"\t\t{infoName}.Type = access_helper().{varName}_TypeName;\n"
    #get the variable offset using the access_helper
    result += f"\t\t{infoName}.Offset = access_helper().{varName}_Offset;\n"
    #single element size
    result += f"\t\t{infoName}.ElementSize = access_helper().{varName}_ElementSize;\n"
    #total size
    result += f"\t\t{infoName}.TotalSize = access_helper().{varName}_TotalSize;\n"
    #array dimensions
    result += f"\t\t{infoName}.ArrayRank = access_helper().{varName}_ArrayRank;\n"
    result += f"\t\t{infoName}.ArrayExtents = access_helper().{varName}_ArrayExtents;\n"
 
    return result

#codegen: emit a node5
def CodeGenOutputNode(node) :
   
    hppCode = cppCode = ""

    #class or structs
    if node[ENodeKind] == EKindClass or node[ENodeKind] == EKindClassTemplate or node[ENodeKind] == EKindStruct :
        hppCode += CodeGenOutputMetaHeader(hppCode, node)

        #declare the attribute map
        hppCode += "\tstd::map<std::string_view, std::string_view> Attributes = "
        hppCode += CodeGenOutputAttributes(node, 1) 
        hppCode += ";\n\n"

        #create the access helper
        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            #create an access_helper to read protected variables
            hppCode += "\tstruct access_helper : public " + node[ENodeFullName] + " {\n"
            for _, var in node[ENodeVariables].items() :
                if var[ENodeAccess] == str(AccessSpecifier.PROTECTED) or var[ENodeAccess] == str(AccessSpecifier.PUBLIC) :
                    varName = f"{node[ENodeFullName]}::{var[ENodeName]}"
                    hppCode += f"\t\tusing {var[ENodeName]}_t = decltype({varName});\n"
                    hppCode += f"\t\tconst size_t {var[ENodeName]}_Offset = offsetof(access_helper, {varName});\n"
                    hppCode += f"\t\tconst size_t {var[ENodeName]}_ElementSize = sizeof(std::remove_all_extents_t<{var[ENodeName]}_t>);\n"
                    hppCode += f"\t\tconst size_t {var[ENodeName]}_TotalSize = sizeof({var[ENodeName]}_t);\n"
                    hppCode += f"\t\tconst size_t {var[ENodeName]}_ArrayRank = pycppgen_detail::get_rank({var[ENodeName]});\n"
                    hppCode += f"\t\tconst std::vector<size_t> {var[ENodeName]}_ArrayExtents = pycppgen_detail::get_extents({var[ENodeName]});\n"
                    hppCode += f"\t\tconst std::string {var[ENodeName]}_TypeName = typeid(decltype({node[ENodeFullName]}::{var[ENodeName]})).name();\n"
                    hppCode += "\t\tconst void Set" + var[ENodeName] + "(const decltype(" + node[ENodeFullName] + "::" + var[ENodeName] +" )& value) { " +  node[ENodeFullName] + "::" + var[ENodeName] + " = value; }\n"
                    hppCode += "\t\tconst auto& Get" + var[ENodeName] + "() const { return " + node[ENodeFullName] + "::" + var[ENodeName] + "; }\n"
                    hppCode += "\t\tauto& Get" + var[ENodeName] + "Ref() { return " + node[ENodeFullName] + "::" + var[ENodeName] + "; }\n"
            for _, fn in node[ENodeFunctions].items() :
                    hppCode += f"\t\tusing {node[ENodeName]}::{fn[ENodeName]};\n"
            hppCode += "\t};\n\n"

        #parent classes 
        hppCode += "\tstatic void for_each_parent(auto fn, uint32_t maxDepth = UINT_MAX) {\n"
        if ENodeParents in node :
            hppCode += "\t\tif(maxDepth > 0) {\n"
            for p in node[ENodeParents] :
                typeName = "type_" + p.replace("::", "_")
                hppCode += "\t\t\tpycppgen<" + p + ">::for_each_parent(fn, maxDepth - 1);\n"
                hppCode += "\t\t\tstruct " + typeName + " { using type = " + p + "; const type* obj = nullptr; };\n"
                hppCode += f"\t\t\tfn({typeName}());\n"
            hppCode += "\t\t}\n"
        hppCode += "\t};\n\n"
        
        #variable's reflection
        hppCode += "\tstatic void for_each_var(std::function<void(const member_variable_info&)> fn, uint32_t maxDepth = UINT_MAX) {\n"
        if ENodeNamespace in node and node[ENodeNamespace] != "" :
            hppCode += f"\t\tusing namespace {node[ENodeNamespace]};\n"
        
        #parent variables
        if ENodeParents in node :
            hppCode += "\t\tif(maxDepth > 0) {\n"
            for p in node[ENodeParents] :
                hppCode += f"\t\t\tpycppgen<{p}>::for_each_var(fn, maxDepth - 1);\n"
            hppCode += "\t\t}\n"
            hppCode += "\n"

        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            for _, var in node[ENodeVariables].items() :
                #skip private variables
                if var[ENodeAccess] == str(AccessSpecifier.PRIVATE) :
                    continue
                
                #generate member_variable_info
                infoName = f"{var[ENodeName]}_info_" + str(hppCode.count('\n'))
                hppCode += GenerateMemberInfo(node, var, infoName)
                
                #call visitor
                hppCode += f"\t\tfn(" + infoName + ");\n\n"

        hppCode += "\t}\n\n"

        #variable's reflection
        hppCode += "\tstatic void for_each_var_typed(auto fn, uint32_t maxDepth = UINT_MAX) {\n"
        if ENodeNamespace in node and node[ENodeNamespace] != "" :
            hppCode += f"\t\tusing namespace {node[ENodeNamespace]};\n"
        
        #parent variables
        if ENodeParents in node :
            hppCode += "\t\tif(maxDepth > 0) {\n"
            for p in node[ENodeParents] :
                hppCode += f"\t\t\tpycppgen<{p}>::for_each_var_typed(fn, maxDepth - 1);\n"
            hppCode += "\t\t}\n"

        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            for _, var in node[ENodeVariables].items() :
                #skip private variables
                if var[ENodeAccess] == str(AccessSpecifier.PRIVATE) :
                    continue
                
                #generate member_variable_info
                infoName = f"{var[ENodeName]}_info_" + str(hppCode.count('\n'))
                hppCode += GenerateMemberInfo(node, var, infoName)
                
                #call visitor
                hppCode += f"\t\tfn({infoName}, access_helper().Get{var[ENodeName]}Ref());\n\n"

        hppCode += "\t}\n\n"

        hppCode += "\tstatic void for_each_var(" + node[ENodeType] + "* obj, auto visitor, uint32_t maxDepth = UINT_MAX) {\n"
        if ENodeNamespace in node and node[ENodeNamespace] != "" :
            hppCode += f"\t\tusing namespace {node[ENodeNamespace]};\n"
        #parent classes
        if ENodeParents in node :
            hppCode += "\t\tif(maxDepth > 0) {\n"
            for p in node[ENodeParents] :
                hppCode += f"\t\t\tpycppgen<{p}>::for_each_var(obj, visitor, maxDepth - 1);\n"
            hppCode += "\t\t}\n"

        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            for _, var in node[ENodeVariables].items() :
                #skip private variables
                if var[ENodeAccess] == str(AccessSpecifier.PRIVATE) :
                    continue
               
                #generate member_variable_info
                infoName = f"{var[ENodeName]}_info_" + str(hppCode.count('\n'))
                hppCode += GenerateMemberInfo(node, var, infoName)

                hppCode += f"\t\tvisitor({infoName}, ((access_helper*)obj)->Get{var[ENodeName]}Ref());\n"
        hppCode += "\t}\n\n"

        hppCode += "\tstatic void for_each_var(const " + node[ENodeType] + "* obj, auto visitor, uint32_t maxDepth = UINT_MAX) {\n"
        if ENodeNamespace in node and node[ENodeNamespace] != "" :
            hppCode += f"\t\tusing namespace {node[ENodeNamespace]};\n"
        #parent classes
        if ENodeParents in node :
            hppCode += "\t\tif(maxDepth > 0) {\n"
            for p in node[ENodeParents] :
                hppCode += f"\t\t\tpycppgen<{p}>::for_each_var(obj, visitor, maxDepth - 1);\n"
            hppCode += "\t\t}\n"

        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            for _, var in node[ENodeVariables].items() :
                #skip private variables
                if var[ENodeAccess] == str(AccessSpecifier.PRIVATE) :
                    continue
               
                #generate member_variable_info
                infoName = f"{var[ENodeName]}_info_" + str(hppCode.count('\n'))
                hppCode += GenerateMemberInfo(node, var, infoName)

                hppCode += f"\t\tvisitor({infoName}, ((access_helper*)obj)->Get{var[ENodeName]}Ref());\n"
        hppCode += "\t}\n\n"

        hppCode += "\tstatic std::map<std::string, std::string> get_var_attributes(std::string_view name) {\n"
        if ENodeNamespace in node and node[ENodeNamespace] != "" :
            hppCode += f"\t\tusing namespace {node[ENodeNamespace]};\n"
        
        hppCode += f"\t\tstd::map<std::string, std::string> result;\n"

        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            for _, var in node[ENodeVariables].items() :
                #skip private variables
                if var[ENodeAccess] == str(AccessSpecifier.PRIVATE) :
                    continue
                
                hppCode += f"\t\tif (name == \"{var[ENodeName]}\")\n"
                hppCode += f"\t\t\t result = {CodeGenOutputAttributes(var, 3)};\n"
            
        #parent classes
        if ENodeParents in node :
            hppCode += "\n"
            for p in node[ENodeParents] :
                hppCode += "\t\tif (result.empty())\n"
                hppCode += f"\t\t\tresult = pycppgen<{p}>::get_var_attributes(name);\n"
            hppCode += "\n"

        if ENodeMemberAttributesOverride in node and len(node[ENodeMemberAttributesOverride]) > 0:
            hppCode += f"\t\t//overrides\n"
            overrides = node[ENodeMemberAttributesOverride]
            for o in overrides :
                hppCode += f"\t\tif (name == \"{o}\")\n"
                hppCode += "\t\t{\n"
                for r in overrides[o]:
                    hppCode += f"\t\t\tresult[\"{r}\"] = \"{overrides[o][r]}\";\n"
                hppCode += "\t\t}\n"

        hppCode += "\t\treturn result;\n"
        hppCode += "\t}\n\n"

        #TODO do the same for static variables
        hppCode += "\tstatic void for_each_static_var(std::function<void(std::string_view name)> fn) {\n"
        if ENodeStaticVariables in node and len(node[ENodeStaticVariables]) > 0 :
            for _, var in node[ENodeStaticVariables].items() :
                hppCode += f"\t\tfn(\"{var[ENodeName]}\");\n"
        hppCode += "\t}\n\n"

        #serialization creates a dump (output) and parse (input) functions
        hppCode += "\ttemplate<typename T> static bool dump(T& result, const " + node[ENodeType] + "* object) {\n"
        if ENodeParents in node :
            for parent in node[ENodeParents] :
                hppCode += f"\t\tpycppgen<{parent}>::dump(result, object);\n"

        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            #serialize the values
            for _, var in node[ENodeVariables].items() :
                if "serialize" in var[ENodeAttributes] and (var[ENodeAccess] == str(AccessSpecifier.PUBLIC) or var[ENodeAccess] == str(AccessSpecifier.PROTECTED)) :
                    hppCode += f"\t\tresult[\"{var[ENodeName]}\"] = ((access_helper*)object)->Get{var[ENodeName]}();\n"
        hppCode += "\t\treturn true;\n"
        hppCode += "\t}\n\n"

        hppCode += "\ttemplate<typename T, typename R> static bool parse(const T& data, R* object) {\n"
        if ENodeParents in node :
            for parent in node[ENodeParents] :
                hppCode += f"\t\tpycppgen<{parent}>::parse(data, object);\n"
        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            for _, var in node[ENodeVariables].items() :
                if "serialize" in var[ENodeAttributes] and (var[ENodeAccess] == str(AccessSpecifier.PUBLIC) or var[ENodeAccess] == str(AccessSpecifier.PROTECTED)) :
                    hppCode += "\t\t((access_helper*)object)->Set" + var[ENodeName] + "(data[\"" + var[ENodeName]+ "\"]);\n"
        hppCode += "\t\treturn true;\n"
        hppCode += "\t}\n\n"

        #functions
        hppCode += "\tstatic void for_each_function(auto fn, uint32_t maxDepth = UINT_MAX) {\n"
        if ENodeNamespace in node and node[ENodeNamespace] != "" :
            hppCode += f"\t\tusing namespace {node[ENodeNamespace]};\n"

        if ENodeParents in node :
            hppCode += "\t\tif(maxDepth > 0) {\n"
            for p in node[ENodeParents] :
                hppCode += f"\t\t\tpycppgen<{p}>::for_each_function(fn, maxDepth - 1);\n"
            hppCode += "\t\t}\n"

        if ENodeFunctions in node and len(node[ENodeFunctions]) > 0 :
            for _, func in node[ENodeFunctions].items() :
                if func[ENodeAccess] == str(AccessSpecifier.PUBLIC) or func[ENodeAccess] == str(AccessSpecifier.PROTECTED) :
                    funcName = func[ENodeName]
                    infoName = f"{funcName}_info_" + str(hppCode.count('\n'))
                    hppCode += f"\t\tmember_function_info<decltype(&access_helper::{func[ENodeName]})> {infoName};\n"
                    hppCode += f"\t\t{infoName}.Name = \"{funcName}\";\n"
                    hppCode += f"\t\t{infoName}.Declaration = \"{func[ENodeType]}\";\n"
                    hppCode += f"\t\t{infoName}.Attributes = {CodeGenOutputAttributes(func, 3)};\n"
                    hppCode += f"\t\t{infoName}.ReturnType = \"{func[ENodeReturnType]}\";\n"
                    hppCode += f"\t\t{infoName}.Function = &access_helper::{func[ENodeName]};\n"
                    hppCode += "\t\t//parameters\n"
                    hppCode += "\t\t{\n"
                    for _, pv in func[ENodeParameters].items() :
                        paramInfoName = f"{pv[ENodeName]}_info_" + str(hppCode.count('\n'))
                        hppCode += f"\t\t\tfunction_parameter_info {paramInfoName};\n"
                        hppCode += f"\t\t\t{paramInfoName}.Name = \"{pv[ENodeName]}\";\n"
                        hppCode += f"\t\t\t{paramInfoName}.Type = \"{pv[ENodeType]}\";\n"
                        hppCode += f"\t\t\t{paramInfoName}.DefaultValue = \"{pv[ENodeDefaultValue]}\";\n"
                        hppCode += f"\t\t\t{paramInfoName}.Attributes = {CodeGenOutputAttributes(pv, 3)};\n"
                        hppCode += f"\t\t\t{infoName}.Parameters.push_back({paramInfoName});\n"
                    hppCode += "\t\t}\n"
                    hppCode += f"\t\tfn({infoName});\n"
        hppCode += "\t}\n\n"

        #functions
        hppCode += "\tstatic bool find_function_by_name(std::string_view name, auto fn, uint32_t maxDepth = UINT_MAX) {\n"
        hppCode += "\t\tbool result = false;\n"
        hppCode += "\t\tfor_each_function([&](const auto& info) {\n"
        hppCode += "\t\t\tif (info.Name == name) { result = true; fn(info); } \n"
        hppCode += "\t\t}, maxDepth);\n"
        hppCode += "\treturn result;\n"
        hppCode += "\t}\n\n"
        
        #has_function by name declaration
        hppCode += "\tstatic constexpr bool has_function(std::string_view name, uint32_t maxDepth = UINT_MAX) {\n"
        if ENodeNamespace in node and node[ENodeNamespace] != "" :
            hppCode += f"\t\tusing namespace {node[ENodeNamespace]};\n"

        if ENodeFunctions in node :
            for _, v in node[ENodeFunctions].items() :
                hppCode += f"\t\tif (name == std::string_view(\"{v[ENodeName]}\")) return true; \n"
        if ENodeStaticFunctions in node :
            for _, v in node[ENodeStaticFunctions].items() :
                hppCode += f"\t\tif (name == std::string_view(\"{v[ENodeName]}\")) return true; \n"
        if ENodeParents in node :
            hppCode += "\t\tif(maxDepth > 0) {\n"
            for p in node[ENodeParents] :
                hppCode += f"\t\t\tif (pycppgen<{p}>::has_function(name, maxDepth)) return true;\n"
            hppCode += "\t\t}\n"
        hppCode += "\t\treturn false;\n\t}\n\n"

        declarations = dict()

        #append functions
        if ENodeFunctions in node :
            for _, v in node[ENodeFunctions].items() :
                CodeGenOutputAddFunctionDeclaration(declarations, node, v, False)

        #append static functions
        if ENodeStaticFunctions in node and len(node[ENodeStaticFunctions]) > 0 :
            for _, v in node[ENodeStaticFunctions].items() :
                CodeGenOutputAddFunctionDeclaration(declarations, node, v, True)

        for _, v in declarations.items() :
            hppCode += v + "\t\treturn false;\n\t}\n\n"

        hppCode = CodeGenOutputMetaFooter(hppCode, node)

    elif node[ENodeKind] == EKindEnum :
        hppCode += CodeGenOutputMetaHeader(hppCode, node)

        #append enum attributes
        hppCode += "\tstd::map<std::string, std::string> Attributes = "
        hppCode += CodeGenOutputAttributes(node, 1) 
        hppCode += ";\n\n"

        if ENodeEnumValues in node :
            #for each enum
            hppCode += "\ttemplate<typename FN> static void for_each_enum_value(FN&& fn) {\n"
            for k, v in node[ENodeEnumValues].items() :
                hppCode += "\t\tfn( " + node[ENodeFullName] + "::" + k + " );\n"
            hppCode += "\t}\n"

            #enum to string
            hppCode += "\tstatic constexpr std::string_view enum_to_string(" + node[ENodeFullName] + " value) {\n"
            for k, v in node[ENodeEnumValues].items() :
                hppCode += "\t\tif (value == " + node[ENodeFullName] + "::" + k + " ) return \"" + k + "\";\n"
            hppCode += "\t\treturn \"\";\n"
            hppCode += "\t}\n"

            #string to enum
            hppCode += "\tstatic constexpr " + node[ENodeFullName] + " string_to_enum(std::string_view value) {\n"
            for k, v in node[ENodeEnumValues].items() :
                hppCode += "\t\tif (value == \"" + k + "\") return " + node[ENodeFullName] + "::" + k + ";\n"
            hppCode += "\t\treturn static_cast<" + node[ENodeFullName] + ">(-1);\n"
            hppCode += "\t}\n"

            #enum value attributes
            hppCode += "\tstatic std::map<std::string, std::string> enum_value_attributes(" + node[ENodeFullName] + " value) {\n"
            for k, v in node[ENodeEnumValues].items() :
                hppCode += "\t\tif (value == " + node[ENodeFullName] + "::" + k + ") {\n\t\t\treturn " + CodeGenOutputAttributes(v, 3) + ";\n\t\t}\n"
            hppCode += "\t\treturn {};\n"
            hppCode += "\t}\n"

        hppCode = CodeGenOutputMetaFooter(hppCode, node)

    return hppCode, cppCode

#codegen: output file
def CodeGen(filePath : str) :
    cppCode = ""
    hppCode = ""
    hppCode += "#pragma once\n\n"
    hppCode += "#include \"pycppgen.h\"\n"
    hppCode += "#include \"" + str(pathlib.Path(filePath).relative_to(pathlib.Path(filePath).parent)) + "\"\n\n"

    for key in TLS().NodeList :
        newHppCode, newCppCode = CodeGenOutputNode(TLS().NodeList[key])
        hppCode += newHppCode
        cppCode += newCppCode

    hppCode += "namespace pycppgen_globals {\n"
    
    for _, func in TLS().NodeList.items() :
        if func[ENodeKind] == EKindFreeFunction :
            hppCode += "//" + func[ENodeFullName] + "\n"

    for _, var in TLS().NodeList.items() :
        if var[ENodeKind] == EKindFreeVariable :
            hppCode += "//" + var[ENodeType] + " " + var[ENodeFullName] + "\n"

    hppCode += "}\n"

    with open(GetOutputFilePath(filePath, "h"), mode="wt") as output :
        output.write(hppCode)

    if len(cppCode) > 0 :
        with open(GetOutputFilePath(filePath, "cpp"), mode="wt") as output :
            output.write(f"#include \"{GetOutputFileName(filePath, 'h')}\"\n\n")
            output.write(cppCode)

#codegen: emit for each type call
def CodeGenGlobalAddForEachTypeCall(code, node) :
    if node[ENodeKind] == EKindClass or node[ENodeKind] == EKindStruct : #or node[ENodeKind] == EKindClassTemplate:
        typeName = "type_" + node[ENodeFullName].replace("::", "_")
        code += "\t\tstruct " + typeName + " { using type = " + node[ENodeFullName] + "; const type* obj = nullptr; };\n"
        code += f"\t\tfn({typeName}());\n"
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
#include <functional>
#include <type_traits>
#include <any>

struct member_variable_info {
	std::string Name;
	std::string FullName;
	std::string Type;
	size_t Offset = 0;
	size_t ElementSize = 0;
	size_t TotalSize = 0;
	size_t ArrayRank = 0;
	std::vector<size_t> ArrayExtents;
};

struct function_parameter_info {
	std::string Name;
	std::string Type;
	std::string DefaultValue;
	std::map<std::string, std::string> Attributes;
};

template<typename T>
struct member_function_info {
	std::string Name;
	std::string Declaration;
	std::string ReturnType;
    T Function = nullptr;
	std::vector<function_parameter_info> Parameters;
	std::map<std::string, std::string> Attributes;
};

template<>
struct member_function_info<void> {
	std::string Name;
	std::string Declaration;
	std::string ReturnType;
 	std::vector<function_parameter_info> Parameters;
	std::map<std::string, std::string> Attributes;

    member_function_info() 
    {
    }

    template<typename T> member_function_info(const member_function_info<T>& A)
    {
	    Name = A.Name;
	    Declaration = A.Declaration;
	    ReturnType = A.ReturnType;
 	    Parameters = A.Parameters;
	    Attributes = A.Attributes;
    }

    template<typename T> member_function_info& operator=(const member_function_info<T>& A)
    {
	    Name = A.Name;
	    Declaration = A.Declaration;
	    ReturnType = A.ReturnType;
 	    Parameters = A.Parameters;
	    Attributes = A.Attributes;

        return *this;
    }
};

template<typename T = void> struct pycppgen { static constexpr bool is_valid() { return false; } };
template<> struct pycppgen<void> 
{
    pycppgen(std::string_view name);
    pycppgen(const std::type_info& info) : HashCode(info.hash_code()) {}
    std::map<std::string, std::string> get_var_attributes(std::string_view name) const;
    void for_each_var(std::function<void(const member_variable_info&)> fn, uint32_t maxDepth = UINT_MAX) const;
    template<typename T> static void for_each_var(const T* obj, auto fn, uint32_t maxDepth = UINT_MAX);
    template<typename T> static void for_each_var(T* obj, auto fn, uint32_t maxDepth = UINT_MAX);   
    template<typename T, typename R> static bool dump(T& result, const R* object); 
    template<typename T, typename R> static bool parse(const T& data, R* object); 

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
	template <typename T>
	size_t get_rank(const T& arr) {
		return std::rank_v<T>;
	}

	template <typename T, std::size_t N>
	size_t get_rank(const std::array<T, N>& arr) {
	    return 1;
	}

	template <typename T>
	std::vector<size_t> get_extents(const T& arr) {
		return { 0 };
	}

	template <typename T, std::size_t N>
	std::vector<size_t> get_extents(const std::array<T, N>& arr) {
	    return { N };
	}

	template <typename T, std::size_t N>
	std::vector<size_t> get_extents(T (&)[N]) {
	    return { N };
	}
	
	template <typename T, std::size_t N, std::size_t M, typename... Dims>
	std::vector<std::size_t> get_extents(T (&)[N][M], Dims... dims) {
	    std::vector<size_t> extents = {N, M};
	    (extents.push_back(dims), ...);
	    return extents;
	}

	template <typename T, std::size_t N, std::size_t M, std::size_t B, typename... Dims>
	std::vector<std::size_t> get_extents(T (&)[N][M][B], Dims... dims) {
	    std::vector<size_t> extents = {N, M, B};
	    (extents.push_back(dims), ...);
	    return extents;
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
    for k in PerFileData :
        code += f"#include \"{str(pathlib.Path(GetOutputFilePath(k)).relative_to(ProjectPath)).replace("\\", "/")}\"\n"

    code += "\nnamespace pycppgen_globals\n{\n"

    code += "\tstatic void for_each_type_call(auto fn) {\n"
    for _, node in TLS().NodeList.items() :
        code = CodeGenGlobalAddForEachTypeCall(code, node)
    code += "\t}\n\n"

    code += "\tstatic void for_each_enum_call(auto fn)\n"
    code += "\t{\n"
    for _, node in TLS().NodeList.items() :
        if node[ENodeKind] == EKindEnum :
            code += f"\t\tfn({node[ENodeFullName]}());\n"
    code += "\t}\n\n"

    code += "}\n\n"

    code += "template<typename T> void pycppgen<void>::for_each_var(const T* obj, auto fn, uint32_t maxDepth)\n"
    code += "{\n"
    code += f"\tconst auto hashCode = obj ? typeid(*obj).hash_code() : 0;\n"
    code += "\tif (false) {}\n"
    for _, node in TLS().NodeList.items() :
        if node[ENodeKind] == EKindClass or node[ENodeKind] == EKindStruct :
            code += f"\telse if (hashCode == typeid({node[ENodeFullName]}).hash_code())\n"
            code += f"\t\tpycppgen<{node[ENodeFullName]}>::for_each_var((const {node[ENodeFullName]}*)obj, fn, maxDepth - 1);\n"
    code += "}\n\n"

    code += "template<typename T> void pycppgen<void>::for_each_var(T* obj, auto fn, uint32_t maxDepth)\n"
    code += "{\n"
    code += f"\tconst auto hashCode = obj ? typeid(*obj).hash_code() : 0;\n"
    code += "\tif (false) {}\n"
    for _, node in TLS().NodeList.items() :
        if node[ENodeKind] == EKindClass or node[ENodeKind] == EKindStruct :
            code += f"\telse if (hashCode == typeid({node[ENodeFullName]}).hash_code())\n"
            code += f"\t\tpycppgen<{node[ENodeFullName]}>::for_each_var(({node[ENodeFullName]}*)obj, fn, maxDepth - 1);\n"
    code += "}\n\n"

    code += "template<typename T, typename R> bool pycppgen<void>::dump(T& result, const R* obj)\n"
    code += "{\n"
    code += f"\tconst auto hashCode = obj ? typeid(*obj).hash_code() : 0;\n"
    code += "\tif (false) {}\n"
    for _, node in TLS().NodeList.items() :
        if (node[ENodeKind] == EKindClass or node[ENodeKind] == EKindStruct) and "serialize" in node[ENodeAttributes] :
            code += f"\telse if (hashCode == typeid({node[ENodeFullName]}).hash_code())\n"
            code += f"\t\treturn pycppgen<{node[ENodeFullName]}>::dump(result, (const {node[ENodeFullName]}*)obj);\n"
    code += "\treturn false;\n"
    code += "}\n\n"

    code += "template<typename T, typename R> bool pycppgen<void>::parse(const T& data, R* obj)\n"
    code += "{\n"
    code += f"\tconst auto hashCode = obj ? typeid(*obj).hash_code() : 0;\n"
    code += "\tif (false) {}\n"
    for _, node in TLS().NodeList.items() :
        if (node[ENodeKind] == EKindClass or node[ENodeKind] == EKindStruct) and "serialize" in node[ENodeAttributes] :
            code += f"\telse if (hashCode == typeid({node[ENodeFullName]}).hash_code())\n"
            code += f"\t\treturn pycppgen<{node[ENodeFullName]}>::parse(data, (const {node[ENodeFullName]}*)obj);\n"
    code += "\treturn false;\n"
    code += "}\n\n"

    if os.path.exists(path + "\\pycppgen.gen.h") :
        os.remove(path + "\\pycppgen.gen.h")

    with open(path + "\\pycppgen.gen.h", mode="wt") as file :
        file.write(code)

    #pycppgen.gen.cpp
    code = ""
    code += "#include \"pycppgen.h\"\n"
    code += "#include \"pycppgen.gen.h\"\n"
    code += "\n"

    code += "pycppgen<void>::pycppgen(std::string_view name)\n"
    code += "{\n"
    for _, node in TLS().NodeList.items() :
        if node[ENodeKind] == EKindClass or node[ENodeKind] == EKindStruct :
            if code.endswith("{\n") : code += "\t"
            else : code += f"\telse "
            code += f"if (name == \"{node[ENodeFullName]}\" || name == \"{node[ENodeName]}\")\n"
            code += f"\t\tHashCode = typeid({node[ENodeFullName]}).hash_code();\n"
    code += "}\n\n"

    #static function call by name
    code += "static void for_each_type_static_call_by_name(std::string_view funcName) {\n"
    for _, node in TLS().NodeList.items() :
        if (node[ENodeKind] == EKindClass or node[ENodeKind] == EKindStruct) and ENodeStaticFunctions in node:
            for _, func in node[ENodeStaticFunctions].items() :
                if (not ENodeParameters in func or len(func[ENodeParameters]) == 0) and (not ENodeReturnType in func or func[ENodeReturnType] == "void"):
                    code += f"\tpycppgen<{node[ENodeFullName]}>::call_function(funcName);\n"
    code += "}\n\n"
    
    code += "std::map<std::string, std::string> pycppgen<void>::get_var_attributes(std::string_view name) const\n"
    code += "{\n"
    code += "\tif (false) {}\n"
    for _, node in TLS().NodeList.items() :
        if node[ENodeKind] == EKindClass or node[ENodeKind] == EKindStruct :
            code += f"\telse if (HashCode == typeid({node[ENodeFullName]}).hash_code())\n"
            code += f"\t\treturn pycppgen<{node[ENodeFullName]}>::get_var_attributes(name);\n"
    code += "\treturn {};\n"
    code += "}\n\n"


    code += "void pycppgen<void>::for_each_var(std::function<void(const member_variable_info&)> fn, uint32_t maxDepth) const\n"
    code += "{\n"
    for _, node in TLS().NodeList.items() :
        if node[ENodeKind] == EKindClass or node[ENodeKind] == EKindStruct :
            code += f"\tif (HashCode == typeid({node[ENodeFullName]}).hash_code())\n"
            code += f"\t\tpycppgen<{node[ENodeFullName]}>::for_each_var(fn, maxDepth - 1);\n"
    code += "}\n\n"

    if os.path.exists(path + "\\pycppgen.gen.cpp") :
        os.remove(path + "\\pycppgen.gen.cpp")

    with open(path + "\\pycppgen.gen.cpp", mode="wt") as file :
        file.write(code)

def IsFileUpToDate(src : str, dst : str) :
    if not os.path.exists(dst) or not os.path.exists(src) :
        return False

    srcTime = os.path.getmtime(src)
    dstTime = os.path.getmtime(dst)

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
            if f.read().find("$[[pycppgen") != -1 :
                FilesWithPyCppGenTag[file] = True
                return True

    FilesWithPyCppGenTag[file] = False
    return False

def ProcessFile(file : str, compilerOptions) :
    global OutdatedFiles

    outdatedIncludedFile = False

    # if the input or output files are newer than the cache, force re-parsing
    if not IsFileUpToDate(file, CacheFile) or not IsFileUpToDate(GetOutputFilePath(file), CacheFile) :
        if not file in OutdatedFiles :
            print(f"outdated cache entry for {file}") 
        PerFileData[file] = ParseFile(file, compilerOptions)
    else : # check if any of the include files are dirty
        tu = CompileFile(file, compilerOptions)
        includeSet = set()
        for f in tu.get_includes():
            includeSet.add(f.include.name)

        for f in includeSet :
            if FileContainsPyCppGenTag(f) and not IsFileUpToDate(f, GetOutputFilePath(file)) :
                print(f"outdated include {f} in {file}") 
                outdatedIncludedFile = True
                break 

        if outdatedIncludedFile:
            PerFileData[file] = ParseTranslationUnit(tu)

    if outdatedIncludedFile == False and IsOutputUpToDate(file) :
        return    

    TLS().NodesToInclude = PerFileData[file]["NodesToInclude"]
    TLS().NodeList = PerFileData[file]["NodeList"]
    TLS().NodeTree = PerFileData[file]["NodeTree"]
    TLS().NodeStack = PerFileData[file]["NodeStack"]    
    
    print("generating code for: " + file)
    CodeGen(file)

def main(args : list) :
    global FilesToParse, PerFileData, ProjectPath, CacheFile, OutdatedFiles

    if len(args) < 1 :
        print("usage py main.py <directory> <options>")
        exit(-1)

    for arg in list(args) :
        if arg.startswith("--I") :
            args.remove(arg)
            arg = arg[3:]
            for i in arg.split(";") :
                args.append(f"-I{i}")

    OutdatedFiles = set()
    ProjectPath = str(pathlib.Path(args[0]).resolve())
    CacheFile = os.path.join(ProjectPath, "pycppgen.cache")

    print("parsing path: " + ProjectPath)

    FilesToParse = []
    OldGenFiles = []
    for root, _, files in os.walk(ProjectPath):
        for file in files:
            if file.endswith(".pycppgentmp") :
                os.remove(root + "\\" + file)
                continue
            if re.match(r".*\.h", file) and not re.match(r".*\.gen.h", file) :
                filePath = os.path.join(root, file)
                if FileContainsPyCppGenTag(filePath) :
                    FilesToParse.append(os.path.join(root, file))
            if file != "pycppgen.gen.h" and re.match(r".*\.gen.h", file) :
                OldGenFiles += [os.path.join(root, file)]
    
    compilerOptions = []
    if len(args) > 1 :
        compilerOptions = args[1:]

    GenFiles = list(map(lambda x : str(pathlib.Path(GetOutputFilePath(x)).resolve()), FilesToParse))
    OldGenFiles = list(map(lambda x : str(pathlib.Path(x).resolve()), OldGenFiles))

    #if the script is newer than the cache, remove all files as we need to rebuild everything
    if not IsFileUpToDate(inspect.getsourcefile(sys.modules[__name__]), CacheFile) :
        print("Outdated file cache")
        for file in OldGenFiles :
            if os.path.exists(file) :
                os.remove(file)
        OldGenFiles = []
        OutdatedFiles = set(FilesToParse)
    else :
        allFilesUpToDate = OldGenFiles == GenFiles and os.path.exists(os.path.join(ProjectPath, "pycppgen.gen.h"))
        for file in FilesToParse :
            if not IsOutputUpToDate(file) :
                print("Outdated file: " + file)
                OutdatedFiles.add(file)
                allFilesUpToDate = False

        if allFilesUpToDate :
            return
    
    FilesToRemove = list(set(OldGenFiles).difference(GenFiles))
    FilesToAdd = list(set(GenFiles).difference(OldGenFiles))
     
    #load cache
    PerFileData = {}
    if os.path.exists(CacheFile) :
        with open(CacheFile, "rt") as file :
            try :
                PerFileData = json.loads(file.read())
            except :
                PerFileData = {}

    if DebugMode :
        for file in FilesToParse :
            ProcessFile(file, compilerOptions)
    else :
        with ThreadPoolExecutor() as pool :
            for file in FilesToParse :
                pool.submit(ProcessFile, file, compilerOptions)

    #clear removed files from the cache
    for file in FilesToRemove :
        PerFileData[file] = {}

    #save cache
    with open(CacheFile, "wt") as file :
        file.write(json.dumps(PerFileData))

    #clear data
    TLS().NodesToInclude = []
    TLS().NodeList = {}
    TLS().NodeTree = {}
    TLS().NodeStack = [TLS().NodeTree]   

    for _, v in PerFileData.items() : 
        TLS().NodeList.update(v["NodeList"])

    print("global code gen step")
    FilesToParse.append(os.path.join(ProjectPath, "\\pycppgen.h"))
    CodeGenGlobal(ProjectPath)
    
    #remove old files
    for file in FilesToRemove :
        if os.path.exists(file) :
            os.remove(file)

if __name__ == "__main__":
    if len(sys.argv) < 2 :
        exit(-1)

    main(sys.argv[1:])

