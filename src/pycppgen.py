import os
import pathlib
import sys
import clang.cindex
import re
import inspect
from clang.cindex import CursorKind
from clang.cindex import AccessSpecifier

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
ENodeParameters = "parameters"
ENodeEnumValues = "enum_values"
ENodeMetaTemplateDecl = "meta_template_decl"
ENodeReturnType = "return_type"
ENodeAttributes = "attributes"
ENodeDefaultValue = "default_value"
ENodeCursor = "clang_cursor"

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

#unused
TypeAliases = dict(
    {
        "int": "int32_t",
        "unsigned int": "uint32_t",
        "short": "int16_t",
        "unsigned short": "uint16_t",
        "unsigned char": "uint8_t"
    }
)

NodeList = {}
NodeTree = {}
NodeStack = [NodeTree]

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
            if len(kv) > 0 : key = kv[0].casefold()
            if len(kv) > 1 : value = kv[1].casefold()

            if key == "exclude" : result["include"] = str(bool(value != None and value == True))
            else : result[key] = value

    if oneMatch and not "include" in result :
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
    global NodeList, NodeTree, NodeStack

    if not node_type in NodeStack[-1]:
        NodeStack[-1][node_type] = dict()

    NodeStack[-1][node_type][node[ENodeFullName]] = node

    if appendToList :
        NodeList[node[ENodeFullName]] = node

#common node push code
def PushNode(cursor, kind : str = EInvalid) :
    global NodeStack
    
    node = dict()
    node[ENodeName] = str(cursor.spelling)
    node[ENodeFullName] = GetFullName(cursor)
    node[ENodeKind] = kind
    node[ENodeType] = str(cursor.type.spelling)
    node[ENodeAccess] = str(cursor.access_specifier)
    node[ENodeScope] = GetScope(cursor)
    node[ENodeAttributes] = ParseComments(cursor, kind)
    node[ENodeCursor] = cursor

    NodeStack.append(node)
    return NodeStack[-1]

#common node pop code
def PopNode() :
    global NodeStack
    NodeStack = NodeStack[:-1]

#parse a function cursor
def ParseFunction(cursor, isFreeFunction : bool = False) :

    #TODO: support operators and functions with special characters
    if re.fullmatch("[a-zA-Z0-9_-_]+", cursor.spelling) == None:
        return

    #push this function to it's parent
    node = PushNode(cursor, EKindFunction)
    
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

    for child in cursor.get_children() :
        
        #inheritance
        if child.kind == CursorKind.CXX_BASE_SPECIFIER :
            AppendToStackTop({ENodeFullName: GetFullName(child)}, ENodeParents)
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
        if cursor.kind == CursorKind.ENUM_DECL :
            if cursor.is_definition() :
                ParseEnum(cursor, False)
            continue

        #generic parse (shouldn't do anything)
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
    global NodeList, NodeTree, NodeStack

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
    if cursor.kind.is_translation_unit() :
        for child in cursor.get_children() :
            ParseCursor(child)
        return

    if cursor.kind == CursorKind.NAMESPACE :
        ParseNamespace(cursor)
        return

    fullName = GetFullName(cursor)

    #ignore already added
    if fullName in NodeList :
        return
    
    #check if it should be parsed
    if not forceInclude :
        flags = ParseComments(cursor, EKindUnknown)
        if "include" in flags : 
            if str(flags["include"]) == "False" :
                return
        elif not fullName in NodesToInclude :
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
            NodeList[node[ENodeFullName]] = node
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

    if cursor.kind == CursorKind.UNION_DECL :
        #TODO
        return

    if cursor.kind == CursorKind.TYPEDEF_DECL :
        #TODO
        return
    
    if cursor.kind == CursorKind.TYPE_ALIAS_DECL :
        ParseTypeAlias(cursor)
        return

def GetOutputFilePath(filePath : str) :
    extStart = filePath.rfind(".")
    outputPath = filePath[:extStart]
    outputPath += ".gen.h"
    return outputPath

#parse a header file
def ParseFile(filePath : str, options : list) :
    global NodesToInclude

    with open(filePath) as file:
        for line in file.readlines() :
            m = re.match(r"\s*\/\/\s*\$\[\[pycppgen-include\s+((?>\w|\W)*)\]\]", line, flags=re.MULTILINE|re.IGNORECASE)
            if not m : continue
            for g in m.groups() :
                NodesToInclude += g.replace(" ", ";").replace(",", ";").split(";")

    with open(os.path.join(os.getcwd(), filePath)) as src :
        with open("tmp.h", "wt") as dst:
            outlines = []
            for line in src.readlines() :
                if re.match(r".*\#\s*include", line) != None:
                    continue
                outlines += [line]
            dst.writelines(["#define PYCPPGEN_STRUCT void _PYCPPGEN_STRUCT() {}\n"])
            dst.writelines(outlines)

    args = ['-x', 'c++', '-std=c++17'] + options
    idx = clang.cindex.Index.create()
    tu = idx.parse("tmp.h", args = args, options = clang.cindex.TranslationUnit.PARSE_INCOMPLETE | clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)

    for cursor in tu.cursor.walk_preorder():
        ParseCursor(cursor)

#codegen: common type header 
def CodeGenOutputMetaHeader(code, node) :
    global pycppdefine

    #make a unique name
    pycppdefine = "pycppgen_" + node[ENodeFullName].replace("::", "_").replace("<","_").replace(">","_")

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

    cursor = node[ENodeCursor]
    if cursor.kind == CursorKind.STRUCT_DECL or cursor.kind == CursorKind.CLASS_DECL or cursor.kind == CursorKind.CLASS_TEMPLATE or cursor.kind == CursorKind.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION :
        for c in cursor.get_children() :
            if c.spelling == "_PYCPPGEN_STRUCT" :
                code += "void " + node[ENodeFullName] + "::for_each_var(std::function<void(const member_variable_info&)> fn) const { return pycppgen<std::decay_t<decltype(*this)>>::for_each_var(fn); }\n"
                code += "void " + node[ENodeFullName] + "::for_each_var(std::function<void(const member_variable_info&)> fn) { return pycppgen<std::decay_t<decltype(*this)>>::for_each_var(fn); }\n"

    code += f"#endif //{pycppdefine}\n"

    #tag the end of autogen code
    code += f"//</autogen_{pycppdefine}>\n\n"

    pycppdefine = None

    return code

#codegen: emit attributes as array of pairs
def CodeGenOutputAttributes(node, depth = 0) :
    if ENodeAttributes in node and len(node[ENodeAttributes]) > 0 :
        depth += 1
        result = "{\n"

        for k, v in node[ENodeAttributes].items() :
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
        result += "\t" * depth + "}"
    else :
        result = "{}"

    return result

#codegen: emit call_function definitions
def CodeGenOutputAddFunctionDeclaration(declarations, node, funcNode, isStatic : bool) :
    decl = f"static_{isStatic}__{funcNode[ENodeType]}"
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
            declarations[decl] += funcNode[ENodeReturnType] + "& result, "

        paramNum = 1
        for _, pv in funcNode[ENodeParameters].items() :
            #code '_<param_num, '
            declarations[decl] += pv[ENodeType] + " _" + str(paramNum) + ", "
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
        declarations[decl] += f"object->{funcNode[ENodeName]}("

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

#codegen: emit a node
def CodeGenOutputNode(code, node) :
    #class or structs
    if node[ENodeKind] == EKindClass or node[ENodeKind] == EKindClassTemplate or node[ENodeKind] == EKindStruct :
        code = CodeGenOutputMetaHeader(code, node)

        #declare the attribute map
        code += "\tstd::map<std::string_view, std::string_view> Attributes = "
        code += CodeGenOutputAttributes(node, 1) 
        code += ";\n\n"

        #create the access helper
        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            #create an access_helper to read protected variables
            code += "\tstruct access_helper : " + node[ENodeFullName] + " {\n"
            for _, var in node[ENodeVariables].items() :
                if var[ENodeAccess] == str(AccessSpecifier.PROTECTED) or var[ENodeAccess] == str(AccessSpecifier.PUBLIC) :
                    code += "\t\tconst size_t " + var[ENodeName] + "_Offset = offsetof(access_helper, " + node[ENodeFullName] + "::" + var[ENodeName] + ");\n"
                    code += "\t\tconst void Set" + var[ENodeName] + "(const decltype(" + node[ENodeFullName] + "::" + var[ENodeName] +" )& value) { " +  node[ENodeFullName] + "::" + var[ENodeName] + " = value; }\n"
                    code += "\t\tconst auto& Get" + var[ENodeName] + "() const { return " + node[ENodeFullName] + "::" + var[ENodeName] + "; }\n"
                    code += "\t\tauto& Get" + var[ENodeName] + "Ref() { return " + node[ENodeFullName] + "::" + var[ENodeName] + "; }\n"
            code += "\t};\n"

        #variable's reflection
        code += "\tstatic void for_each_var(std::function<void(const member_variable_info&)> fn) {\n"
        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            for _, var in node[ENodeVariables].items() :
                #skip private variables
                if var[ENodeAccess] == str(AccessSpecifier.PRIVATE) :
                    continue
                
                #frequently used variables
                varName = var[ENodeName]
                varType = var[ENodeType]
                infoName = f"{varName}_info_" + str(code.count('\n'))

                code += f"\t\tmember_variable_info {infoName};\n"
                #variable name
                code += f"\t\t{infoName}.Name = \"{varName}\";\n"
                #typeid name
                code += f"\t\t{infoName}.Type = typeid({varType}).name();\n"
                #get the protected variable offset using the access_helper
                if var[ENodeAccess] == str(AccessSpecifier.PROTECTED) :
                    code += f"\t\t{infoName}.Offset = access_helper().{varName}_Offset;\n"
                else :
                    code += f"\t\t{infoName}.Offset = offsetof({node[ENodeFullName]}, {varName});\n"
                #single element size
                code += f"\t\t{infoName}.ElementSize = sizeof(std::remove_all_extents_t<{varType}>);\n"
                #total size
                code += f"\t\t{infoName}.TotalSize = sizeof({varType});\n"
                #array dimensions
                code += f"\t\t{infoName}.ArrayRank = std::rank_v<{varType}>;\n"
                for i in range(0, varType.count("[")) :
                    code += f"\t\t{infoName}.ArrayExtents.push_back(std::extent_v<{varType}, {i}>);\n"
                #variable attributes
                code += f"\t\t{infoName}.Attributes = {CodeGenOutputAttributes(var, 2)};\n"
                #call visitor
                code += f"\t\tfn(" + infoName + ");\n\n"
        code += "\t}\n"

        code += "\tstatic void for_each_var(" + node[ENodeType] + "* obj, auto visitor) {\n"
        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            for _, var in node[ENodeVariables].items() :
                #skip private variables
                if var[ENodeAccess] == str(AccessSpecifier.PRIVATE) :
                    continue
               
                code += f"\t\tvisitor(\"{var[ENodeName]}\", ((access_helper*)obj)->Get{var[ENodeName]}Ref());\n"
        code += "\t}\n"

        code += "\tstatic std::map<std::string, std::string> get_member_attributes(std::string_view name) {\n"
        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            for _, var in node[ENodeVariables].items() :
                #skip private variables
                if var[ENodeAccess] == str(AccessSpecifier.PRIVATE) :
                    continue
                
                code += f"\t\tif (name == \"{var[ENodeName]}\") return {CodeGenOutputAttributes(var, 2)};\n"
        code += "\t\treturn {};\n"
        code += "\t}\n"

        #TODO do the same for static variables
        code += "\tstatic void for_each_static_var(std::function<void(std::string_view name)> fn) {\n"
        if ENodeStaticVariables in node and len(node[ENodeStaticVariables]) > 0 :
            for _, var in node[ENodeStaticVariables].items() :
                code += f"\t\tfn(\"{var[ENodeName]}\");\n"
        code += "\t}\n"

        #serialization creates a dump (output) and parse (input) functions
        code += "\ttemplate<typename T> static T dump(const " + node[ENodeType] + "* object) {\n"
        code += "\t\tT result;\n"

        if "for_each_var" in node[ENodeFunctions] :
            code += "\t\tfor_each_var([this](const std::string& name, const auto& value) {\n"
            code += "\t\t\tresult[name] = value;\n"
            code += "\t\t});\n"
        elif ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            #serialize the values
            for _, var in node[ENodeVariables].items() :
                if "serialize" in var[ENodeAttributes] and (var[ENodeAccess] == str(AccessSpecifier.PUBLIC) or var[ENodeAccess] == str(AccessSpecifier.PROTECTED)) :
                    code += f"\t\tresult[\"{var[ENodeName]}\"] = ((access_helper*)object)->Get{var[ENodeName]}();\n"

        code += "\t\treturn result;\n"
        code += "\t}\n"

        code += "\ttemplate<typename T, typename R> static bool parse(const T& data, R* object) {\n"
        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            for _, var in node[ENodeVariables].items() :
                if "serialize" in var[ENodeAttributes] and (var[ENodeAccess] == str(AccessSpecifier.PUBLIC) or var[ENodeAccess] == str(AccessSpecifier.PROTECTED)) :
                    code += "\t\t((access_helper*)object)->Set" + var[ENodeName] + "(data[\"" + var[ENodeName]+ "\"]);\n"
        code += "\t\treturn true;\n"
        code += "\t}\n"

        #functions
        code += "\tstatic void for_each_function(std::function<void(const member_function_info&)> fn) {\n"
        if ENodeFunctions in node and len(node[ENodeFunctions]) > 0 :
            for _, func in node[ENodeFunctions].items() :
                if func[ENodeAccess] == str(AccessSpecifier.PUBLIC) or func[ENodeAccess] == str(AccessSpecifier.PROTECTED) :
                    funcName = func[ENodeName]
                    infoName = f"{funcName}_info_" + str(code.count('\n'))
                    code += f"\t\tmember_function_info {infoName};\n"
                    code += f"\t\t{infoName}.Name = \"{funcName}\";\n"
                    code += f"\t\t{infoName}.Declaration = \"{func[ENodeType]}\";\n"
                    code += f"\t\t{infoName}.Attributes = {CodeGenOutputAttributes(func, 3)};\n"
                    code += f"\t\t{infoName}.ReturnType = \"{func[ENodeReturnType]}\";\n"
                    code += "\t\t//parameters\n"
                    code += "\t\t{\n"
                    for _, pv in func[ENodeParameters].items() :
                        paramInfoName = f"{pv[ENodeName]}_info_" + str(code.count('\n'))
                        code += f"\t\t\tfunction_parameter_info {paramInfoName};\n"
                        code += f"\t\t\t{paramInfoName}.Name = \"{pv[ENodeName]}\";\n"
                        code += f"\t\t\t{paramInfoName}.Type = \"{pv[ENodeType]}\";\n"
                        code += f"\t\t\t{paramInfoName}.DefaultValue = \"{pv[ENodeDefaultValue]}\";\n"
                        code += f"\t\t\t{paramInfoName}.Attributes = {CodeGenOutputAttributes(pv, 3)};\n"
                        code += f"\t\t\t{infoName}.Parameters.push_back({paramInfoName});\n"
                    code += "\t\t}\n"
        code += "\t}\n"

        #has_function by name declaration
        code += "\tstatic constexpr bool has_function(std::string_view name) {\n"
        if ENodeFunctions in node :
            for _, v in node[ENodeFunctions].items() :
                code += f"\t\tif (name == std::string_view(\"{v[ENodeName]}\")) return true; \n"
        if ENodeStaticFunctions in node :
            for _, v in node[ENodeStaticFunctions].items() :
                code += f"\t\tif (name == std::string_view(\"{v[ENodeName]}\")) return true; \n"
        code += "\t\treturn false;\n\t}\n"

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
            code += v + "\t\treturn false;\n\t}\n"

        code = CodeGenOutputMetaFooter(code, node)

    elif node[ENodeKind] == EKindEnum :
        code = CodeGenOutputMetaHeader(code, node)

        #append enum attributes
        code += "\tstd::map<std::string, std::string> Attributes = "
        code += CodeGenOutputAttributes(node, 1) 
        code += ";\n\n"

        if ENodeEnumValues in node :
            #for each enum
            code += "\ttemplate<typename FN> static void for_each_enum(FN&& fn) {\n"
            for k, v in node[ENodeEnumValues].items() :
                code += "\t\tfn( " + node[ENodeFullName] + "::" + k + " );\n"
            code += "\t}\n"

            #enum to string
            code += "\tstatic constexpr std::string_view enum_to_string(" + node[ENodeFullName] + " value) {\n"
            for k, v in node[ENodeEnumValues].items() :
                code += "\t\tif (value == " + node[ENodeFullName] + "::" + k + " ) return \"" + k + "\";\n"
            code += "\t\treturn \"\";\n"
            code += "\t}\n"

            #string to enum
            code += "\tstatic constexpr " + node[ENodeFullName] + " string_to_enum(std::string_view value) {\n"
            for k, v in node[ENodeEnumValues].items() :
                code += "\t\tif (value == \"" + k + "\") return " + node[ENodeFullName] + "::" + k + ";\n"
            code += "\t\treturn static_cast<" + node[ENodeFullName] + ">(-1);\n"
            code += "\t}\n"

            #enum value attributes
            code += "\tstatic std::map<std::string, std::string> enum_value_attributes(" + node[ENodeFullName] + " value) {\n"
            for k, v in node[ENodeEnumValues].items() :
                code += "\t\tif (value == " + node[ENodeFullName] + "::" + k + ") {\n\t\t\treturn " + CodeGenOutputAttributes(v, 3) + ";\n\t\t}\n"
            code += "\t\treturn {};\n"
            code += "\t}\n"

        code = CodeGenOutputMetaFooter(code, node)

    return code

#codegen: output file
def CodeGen(filePath : str) :
    outputPath = GetOutputFilePath(filePath)

    code = ""
    code += "#pragma once\n\n"
    code += "#include \"pycppgen.h\"\n"
    code += "#include \"" + str(pathlib.Path(filePath).relative_to(pathlib.Path(filePath).parent)) + "\"\n\n"

    for key in NodeList :
        code = CodeGenOutputNode(code, NodeList[key])

    code += "namespace pycppgen_globals {\n"
    
    for _, func in NodeList.items() :
        if func[ENodeKind] == EKindFreeFunction :
            code += "//" + func[ENodeFullName] + "\n"

    for _, var in NodeList.items() :
        if var[ENodeKind] == EKindFreeVariable :
            code += "//" + var[ENodeType] + " " + var[ENodeFullName] + "\n"

    code += "}\n"

    with open(outputPath, mode="wt") as output :
        output.write(code)

#codegen: emit for each type call
def CodeGenGlobalAddForEachTypeCall(code, node) :
    if node[ENodeKind] == EKindClass or node[ENodeKind] == EKindStruct : #or node[ENodeKind] == EKindClassTemplate:
        code += f"\t\tfn(*({node[ENodeFullName]}*)0);\n"
    return code

#codegen: output global file
def CodeGenGlobalHeader(path : str) :
    
    code = ""
    code += "#pragma once\n\n"
    code += "#ifndef _PYCPPGEN_HEADER_\n"
    code += "#define _PYCPPGEN_HEADER_\n\n"
    code += "struct member_variable_info {\n"
    code += "\tstd::string_view Name;\n"
    code += "\tstd::string_view Type;\n"
    code += "\tsize_t Offset = 0;\n"
    code += "\tsize_t ElementSize = 0;\n"
    code += "\tsize_t TotalSize = 0;\n"
    code += "\tsize_t ArrayRank = 0;\n"
    code += "\tstd::vector<size_t> ArrayExtents;\n"
    code += "\tstd::map<std::string, std::string> Attributes;\n"
    code += "};\n\n"
    
    code += "struct function_parameter_info {\n"
    code += "\tstd::string_view Name;\n"
    code += "\tstd::string_view Type;\n"
    code += "\tstd::string_view DefaultValue;\n"
    code += "\tstd::map<std::string, std::string> Attributes;\n"
    code += "};\n\n"

    code += "struct member_function_info {\n"
    code += "\tstd::string_view Name;\n"
    code += "\tstd::string_view Declaration;\n"
    code += "\tstd::string_view ReturnType;\n"
    code += "\tstd::vector<function_parameter_info> Parameters;\n"
    code += "\tstd::map<std::string, std::string> Attributes;\n"
    code += "};\n\n"

    code += "template<typename T> struct pycppgen { static constexpr bool is_valid() { return false; } };\n\n"
    code += "template<typename T> auto pycppgen_typeof(T&& t) { return pycppgen<std::decay_t<decltype(t)>>(); }\n\n"
    
    code += "#define PYCPPGEN_STRUCT \\\n"
    code += "\tvirtual void for_each_var(std::function<void(const member_variable_info&)> fn) const; \\\n"
    code += "\tvirtual void for_each_var(std::function<void(const member_variable_info&)> fn); \n"

    code += "#endif //_PYCPPGEN_HEADER_\n\n"

    with open(path + "/pycppgen.h", mode="wt") as output :
        output.write(code)

def CodeGenGlobal(path : str) :
    global PerFileData
    
    CodeGenGlobalHeader(path)

    code = ""
    code += "#pragma once\n\n"
    code += ""
    for k in PerFileData :
        code += f"#include \"{pathlib.Path(GetOutputFilePath(k)).relative_to(path)}\"\n"

    code += "\nnamespace pycppgen_globals\n{\n"

    code += "\tstatic void for_each_type_call(auto fn) {\n"
    for _, node in NodeList.items() :
        code = CodeGenGlobalAddForEachTypeCall(code, node)
    code += "\t}\n\n"

    #static function call by name
    code += "\tstatic void for_each_type_static_call_by_name(std::string_view funcName) {\n"
    for _, node in NodeList.items() :
        if (node[ENodeKind] == EKindClass or node[ENodeKind] == EKindStruct) and ENodeStaticFunctions in node:
            for _, func in node[ENodeStaticFunctions].items() :
                if (not ENodeParameters in func or len(func[ENodeParameters]) == 0) and (not ENodeReturnType in func or func[ENodeReturnType] == "void"):
                    code += f"\t\tpycppgen<{node[ENodeFullName]}>::call_function(funcName);\n"
    code += "\t}\n\n"

    code += ""
    code += "}\n"

    if os.path.exists(path + "\\pycppgen.gen.h") :
        os.remove(path + "\\pycppgen.gen.h")

    with open(path + "\\pycppgen.gen.h", mode="wt") as file :
        file.write(code)

def IsFileUpToDate(src : str, dst : str) :
    if not os.path.exists(dst) or not os.path.exists(src) :
        return False

    srcTime = os.path.getmtime(src)
    dstTime = os.path.getmtime(dst)

    return srcTime < dstTime  

def IsOutputUpToDate(file : str) :
    outputFile = GetOutputFilePath(file)

    IsFileUpToDate(file, outputFile)

def main(args : list) :
    global FilesToParse, NodesToInclude, NodeList, NodeTree, NodeStack, PerFileData

    if len(args) < 1 :
        print("usage py main.py <directory> <options>")
        exit(-1)

    FilesToParse = []
    OldGenFiles = []
    for root, _, files in os.walk(args[0]):
        for file in files:
            if re.match(r".*\.h", file) and not re.match(r".*\.gen.h", file) :
                filePath = os.path.join(root, file)
                with open(filePath) as f :
                    if f.read().find("$[[pycppgen") != -1:
                        FilesToParse.append(os.path.join(root, file))
            if file != "pycppgen.gen.h" and re.match(r".*\.gen.h", file) :
                OldGenFiles += [os.path.join(root, file)]
    
    compilerOptions = []
    if len(args) > 1 :
        compilerOptions = args[1:]

    GenFiles = list(map(lambda x : str(pathlib.Path(GetOutputFilePath(x)).resolve()), FilesToParse))
    OldGenFiles = list(map(lambda x : str(pathlib.Path(x).resolve()), OldGenFiles))

    if not IsFileUpToDate(inspect.getsourcefile(sys.modules[__name__]), args[0] + "\\pycppgen.ver") :
        for file in OldGenFiles :
            if os.path.exists(file) :
                os.remove(file)
        OldGenFiles = []
        with open(args[0] + "\\pycppgen.ver", "wt") as f :
            f.write("")

    FilesToRemove = list(set(OldGenFiles).difference(GenFiles))
    FilesToAdd = list(set(GenFiles).difference(OldGenFiles))

    allFilesUpToDate = len(FilesToRemove) == 0 and len(FilesToAdd) == 0 and os.path.exists(args[0] + "\\pycppgen.gen.h")
    for file in FilesToParse :
        if not IsOutputUpToDate(file) :
            print("Outdated file detected: " + file)
            allFilesUpToDate = False
            break

    if allFilesUpToDate :
        return
    
    print("parsing path: " + args[0])

    PerFileData = {}
    for file in FilesToParse :
        #initialize data
        NodesToInclude = []
        NodeList = {}
        NodeTree = {}
        NodeStack = [NodeTree]        

        ParseFile(file, compilerOptions)
        
        PerFileData[file] = {
            "NodeList": NodeList,
            "NodesToInclude": NodesToInclude,
            "NodeTree": NodeTree,
            "NodeStack": NodeStack
            }
        
    for file in FilesToParse :
        if IsOutputUpToDate(file) :
            continue

        NodesToInclude = PerFileData[file]["NodesToInclude"]
        NodeList = PerFileData[file]["NodeList"]
        NodeTree = PerFileData[file]["NodeTree"]
        NodeStack = PerFileData[file]["NodeStack"]

        print("generating code for: " + file)
        CodeGen(file)

    #clear data
    NodesToInclude = []
    NodeList = {}
    NodeTree = {}
    NodeStack = [NodeTree]   

    for _, v in PerFileData.items() : 
        NodeList.update(v["NodeList"])

    print("global code gen step")
    FilesToParse.append(args[0] + "\\pycppgen.h")
    CodeGenGlobal(args[0])
    
    #remove old files
    for file in FilesToRemove :
        if os.path.exists(file) :
            os.remove(file)

if __name__ == "__main__":
    if len(sys.argv) < 2 :
        exit(-1)

    main(sys.argv[1:])

