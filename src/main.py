import os
import io
import pathlib
import sys
import clang.cindex
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
ENodeFunctions = "functions"
ENodeParents = "parents"
ENodeEnums = "enums"
ENodeStructs = "structs"
ENodeNamespaces = "namespaces"
ENodeParameters = "parameters"
ENodeEnumValues = "enum_values"
ENodeMetaTemplateDecl = "meta_template_decl"
ENodeReturnType = "return_type"

EKindNamespace = "kind_namespace"
EKindAlias = "kind_alias"
EKindEnum = "kind_enum"
EKindClassTemplate = "kind_class_template"
EKindClass = "kind_class"
EKindStruct = "kind_struct"
EKindFunction = "kind_function"
EKindParameter = "kind_parameter"
EKindVariable = "kind_variable"
EKindTemplateTypeParameter = "kind_template_type_parameter"
EKindTemplateNonTypeParameter = "kind_template_non_type_parameter"
EKindTemplateTemplateParameter = "kind_template_template_parameter"

EInvalid = "invalid"

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

def GetScope(cursor, accum : str = "") :
    if cursor.semantic_parent and not cursor.semantic_parent.kind.is_translation_unit() :
        if accum != "" :
            accum = "::" + accum
        accum = str(cursor.semantic_parent.canonical.spelling) + accum
        return GetScope(cursor.semantic_parent.canonical, accum)
    
    return accum

def GetFullName(cursor) :
    accum = str(cursor.displayname)
    return GetScope(cursor, accum)

def AppendToStackTop(node, node_type : str, appendToList : bool = False) :
    global NodeList, NodeTree, NodeStack

    if not node_type in NodeStack[-1]:
        NodeStack[-1][node_type] = dict()

    NodeStack[-1][node_type][node[ENodeFullName]] = node

    if appendToList :
        NodeList[node[ENodeFullName]] = node

def CopyNode(full_name) :
    global NodeList, NodeTree, NodeStack

    if full_name in NodeList :
        return dict(NodeList[full_name])
    return None

def PushNode(cursor, kind : str = EInvalid) :
    global NodeStack
    
    node = dict()
    node[ENodeName] = str(cursor.spelling)
    node[ENodeFullName] = GetFullName(cursor)
    node[ENodeKind] = kind
    node[ENodeType] = str(cursor.type.spelling)
    node[ENodeAccess] = str(cursor.access_specifier)
    node[ENodeScope] = GetScope(cursor)

    NodeStack.append(node)
    return NodeStack[-1]

def PopNode() :
    global NodeStack
    NodeStack = NodeStack[:-1]

def ParseFunction(cursor, isGlobal : bool = False) :
    global NodeList, NodeTree, NodeStack

    node = PushNode(cursor, EKindFunction)
    
    node[ENodeReturnType] = cursor.result_type.spelling
    node[ENodeParameters] = dict()

    for child in cursor.get_children() :
        if child.kind == CursorKind.PARM_DECL:
            param = PushNode(child, EKindParameter)
            PopNode()

            AppendToStackTop(param, ENodeParameters)

    PopNode()

    AppendToStackTop(node, ENodeFunctions, isGlobal)

    return node

def ParseVar(cursor) :
    global NodeList, NodeTree, NodeStack

    node = PushNode(cursor, EKindVariable)
    PopNode()

    AppendToStackTop(node, ENodeVariables)
    NodeList[node[ENodeFullName]] = node
    
    return node

def ParseStruct(cursor) :
    global NodeList, NodeTree, NodeStack

    kind = EInvalid
    if cursor.kind == CursorKind.CLASS_TEMPLATE :
        kind = EKindClassTemplate
    elif cursor.kind == CursorKind.CLASS_DECL :
        kind = EKindClass
    else :
        kind = EKindStruct

    node = PushNode(cursor, kind)
    node[ENodeMetaTemplateDecl] = ""

    for child in cursor.get_children() :
        if child.kind == CursorKind.CXX_BASE_SPECIFIER :
            AppendToStackTop({ENodeFullName: GetFullName(child)}, ENodeParents)
            continue

        if child.kind == CursorKind.CXX_METHOD:
            fn = ParseFunction(child)
            AppendToStackTop(fn, ENodeFunctions)
            continue

        if child.kind == CursorKind.FIELD_DECL :
            var = ParseVar(child)
            AppendToStackTop(var, ENodeVariables)

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

        if ENodeMetaTemplateDecl in node :
            if node[ENodeMetaTemplateDecl].endswith(", ") :
                node[ENodeMetaTemplateDecl] = node[ENodeMetaTemplateDecl][:-2]

        ParseCursor(child)

    PopNode()

    return node

def ParseEnum(cursor) :
    global NodeList, NodeTree, NodeStack

    node = PushNode(cursor, EKindEnum)

    node[ENodeUnderlyingType] = str(cursor.enum_type.spelling)
    node[ENodeEnumValues] = dict()

    for child in cursor.get_children() :
        if child.kind == CursorKind.ENUM_CONSTANT_DECL :
            node[ENodeEnumValues][child.spelling] = str(child.enum_value)

    PopNode()

    AppendToStackTop(node, ENodeEnums, True)

def ParseNamespace(cursor) :
    global NodeList, NodeTree, NodeStack

    node = PushNode(cursor, EKindNamespace)
    for child in cursor.get_children() :
        ParseCursor(child)
    PopNode()

    AppendToStackTop(node, ENodeNamespaces, True)

def ParseTypeAlias(cursor) :
    global NodeList, NodeTree, NodeStack

    node = PushNode(cursor, EKindAlias)
    node[ENodeUnderlyingType] = str(cursor.underlying_typedef_type.spelling)
    PopNode()

    AppendToStackTop(node, ENodeVariables, True)

def ParseCursor(cursor) :
    if cursor.kind.is_translation_unit() :
        for child in cursor.get_children() :
            ParseCursor(child)
        return

    if cursor.kind == CursorKind.NAMESPACE :
        ParseNamespace(cursor)
        return

    if cursor.kind == CursorKind.TYPE_REF or cursor.kind == CursorKind.TEMPLATE_REF or cursor.kind == CursorKind.NAMESPACE_REF:
        return

    if GetFullName(cursor) in NodeList :
        return

    if cursor.kind == CursorKind.STRUCT_DECL or cursor.kind == CursorKind.CLASS_DECL or cursor.kind == CursorKind.CLASS_TEMPLATE :
        if cursor.is_definition() :
            node = ParseStruct(cursor)   
            AppendToStackTop(node, ENodeStructs)
            NodeList[node[ENodeFullName]] = node
        return

    if cursor.kind == CursorKind.ENUM_DECL :
        if cursor.is_definition() :
            ParseEnum(cursor)
        return

    if cursor.kind == CursorKind.VAR_DECL :
        ParseVar(cursor)
        return

    if cursor.kind == CursorKind.FUNCTION_DECL :
        ParseFunction(cursor)
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

def ParseFile(filePath : str, sysArgs = []) :
    global NodeList, NodeTree, NodeStack

    NodeList = {}
    NodeTree = {}
    NodeStack = [NodeTree]

    with open(filePath) as file:
        args = ['-x', 'c++', '-std=c++17'] + sysArgs
        idx = clang.cindex.Index.create()
        tu = idx.parse(os.path.join(os.getcwd(), filePath), args = args, options = clang.cindex.TranslationUnit.PARSE_INCOMPLETE | clang.cindex.TranslationUnit.PARSE_INCLUDE_BRIEF_COMMENTS_IN_CODE_COMPLETION | clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)

        for cursor in tu.cursor.walk_preorder():
            ParseCursor(cursor)

        CodeGen(filePath)

def CodeGenOutputMetaHeader(code, node) :
    if ENodeMetaTemplateDecl in node :
        code += "template<"
        code += node[ENodeMetaTemplateDecl]
        code += ">\nstruct meta<"
    else :
        code += "template<> struct meta<"
    code += node[ENodeFullName]
    code += ">{\n"
    return code

def CodeGenOutputMetaFooter(code, node) :
    code += "};\n\n"
    return code

def CodeGenOutputNode(code, node) :
    
    if node[ENodeKind] == EKindClass or node[ENodeKind] == EKindClassTemplate or node[ENodeKind] == EKindStruct :
        code = CodeGenOutputMetaHeader(code, node)

        code += "\tstatic void for_each_var(std::function<void(const member_variable_info&)> fn) {\n"
        if ENodeVariables in node and len(node[ENodeVariables]) > 0 :
            code += "\t\tstruct access_helper : " + node[ENodeFullName] + " {\n"
            for _, var in node[ENodeVariables].items() :
                if var[ENodeAccess] == str(AccessSpecifier.PUBLIC) or var[ENodeAccess] == str(AccessSpecifier.PROTECTED) :
                    code += "\t\t\tconst size_t " + var[ENodeName] + "_Offset = offsetof(access_helper, " + node[ENodeFullName] + "::" + var[ENodeName] + ");\n"
            code += "\t\t};\n"
            for _, var in node[ENodeVariables].items() :
                if var[ENodeAccess] == str(AccessSpecifier.PUBLIC) or var[ENodeAccess] == str(AccessSpecifier.PROTECTED) :
                    varName = var[ENodeName]
                    varType = var[ENodeType]
                    infoName = f"{varName}_info"
                    code += f"\t\tmember_variable_info {infoName};\n"
                    code += f"\t\t{infoName}.Name = \"{varName}\";\n"
                    code += f"\t\t{infoName}.Type = typeid({varType}).name();\n"
                    code += f"\t\t{infoName}.Offset = access_helper().{varName}_Offset;\n"
                    code += f"\t\t{infoName}.ElementSize = sizeof(std::remove_all_extents_t<{varType}>);\n"
                    code += f"\t\t{infoName}.TotalSize = sizeof({varType});\n"
                    code += f"\t\t{infoName}.ArrayRank = std::rank_v<{varType}>;\n"
                    for i in range(0, varType.count("[")) :
                        code += f"\t\t{infoName}.ArrayExtents.push_back(std::extent_v<{varType}, {i}>);\n"
                    code += f"\t\tfn(" + infoName + ");\n"
        code += "\t}\n"

        if ENodeFunctions in node :
            declarations = dict()
            for k, v in node[ENodeFunctions].items() :
                if len(node[ENodeType]) == 0:
                    continue

                decl = v[ENodeType]
                numParams = len(v[ENodeParameters])
                isConst = decl.endswith("const")

                if not decl in declarations :
                    declarations[decl] = "\tstatic void call_function(std::string_view name, " 
                    if isConst :
                        declarations[decl] += "const " 
                    declarations[decl] += node[ENodeType] + "* object, "

                    if v[ENodeReturnType] != "void" :
                        declarations[decl] += v[ENodeReturnType] + "& result, "

                    paramNum = 1
                    for pk, pv in v[ENodeParameters].items() :
                        declarations[decl] += pv[ENodeType] + " _" + str(paramNum) + ", "
                        paramNum += 1
                    declarations[decl] = declarations[decl][:-2] + ") {\n"
                
                declarations[decl] += "\t\tif (name == \"" + v[ENodeName] + "\") {\n"
                declarations[decl] += "\t\t\t"
                if v[ENodeReturnType] != "void" :
                    declarations[decl] += "result = "
                declarations[decl] += "object->" + v[ENodeName] + "("

                if numParams > 0 :
                    paramNum = 1
                    for pk, pv in v[ENodeParameters].items() :
                        declarations[decl] += " _" + str(paramNum) + ", "
                        paramNum += 1
                    declarations[decl] = declarations[decl][:-2] + ");\n"
                else :
                    declarations[decl] += ");\n"
                declarations[decl] += "\t\t\treturn;\n\t\t}\n"

            for k, v in declarations.items() :
                code += declarations[k] + "\t\t__debugbreak();\n\t}\n"

        code = CodeGenOutputMetaFooter(code, node)

    elif node[ENodeKind] == EKindEnum :
        code = CodeGenOutputMetaHeader(code, node)

        if ENodeEnumValues in node :
            code += "\ttemplate<typename FN> static void for_each_enum(FN&& fn) {\n"
            for k, v in node[ENodeEnumValues].items() :
                code += "\t\tfn( " + node[ENodeFullName] + "::" + k + " );\n"
            code += "\t}\n"

            code += "\tstatic constexpr std::string_view enum_to_string(" + node[ENodeFullName] + " value) {\n"
            for k, v in node[ENodeEnumValues].items() :
                code += "\t\tif (value == " + node[ENodeFullName] + "::" + k + " ) return \"" + k + "\";\n"
            code += "\t\treturn \"\";\n"
            code += "\t}\n"

            code += "\tstatic constexpr " + node[ENodeFullName] + " string_to_enum(std::string_view value) {\n"
            for k, v in node[ENodeEnumValues].items() :
                code += "\t\tif (value == \"" + k + "\") return " + node[ENodeFullName] + "::" + k + ";\n"
            code += "\t\treturn static_cast<" + node[ENodeFullName] + ">(-1);\n"
            code += "\t}\n"

        code = CodeGenOutputMetaFooter(code, node)


    return code

def CodeGen(filePath : str) :
    global NodeList, NodeTree, NodeStack

    fileName = str(pathlib.Path(filePath).relative_to(pathlib.Path(filePath).parent))
    extStart = filePath.rfind(".")
    ext = filePath[extStart:]
    outputPath = filePath[:extStart]
    outputPath += ".gen.h"

    code = "#include \"" + fileName + "\"\n\n"

    code += "#ifndef _PYCPPGEN_DECLARATIONS\n"
    code += "#define _PYCPPGEN_DECLARATIONS\n\n"
    code += "struct member_variable_info {\n"
    code += "\tstd::string_view Name;\n"
    code += "\tstd::string_view Type;\n"
    code += "\tsize_t Offset = 0;\n"
    code += "\tsize_t ElementSize = 0;\n"
    code += "\tsize_t ArrayRank = 0;\n"
    code += "\tstd::vector<size_t> ArrayExtents;\n"
    code += "};\n\n"
    code += "template<typename T> struct meta {};\n\n"
    code += "#endif //_PYCPPGEN_DECLARATIONS\n\n"

    for key in NodeList :
        code = CodeGenOutputNode(code, NodeList[key])

    with open(outputPath, mode="wt") as output :
        output.write(code)

if __name__ == "__main__":
    if len(sys.argv) < 2 :
        print("usage py main.py <filename> <clang_args>")
        exit(-1)

    sysArgs = []
    if len(sys.argv) > 2 :
        sysArgs = sys.argv[2:]
    ParseFile(sys.argv[1], sysArgs)

    exit(0)
