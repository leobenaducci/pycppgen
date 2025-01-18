import os;
import io;
import clang.cindex
from clang.cindex import CursorKind

EName = "name"
EFullName = "full_name"
EType = "type"
EUnderlyingType = "underlying_type"
EAccess = "access"
EScope = "scope"
EVariables = "variables"
EFunctions = "functions"
EParents = "parents"
EEnums = "enums"
EStructs = "structs"
ENamespaces = "namespaces"
EParameters = "parameters"
EValueMap = "value_map"
EAlias = "alias"
EEnum = "enum"
EClassTemplate = "class_template"
EClass = "class"
EStruct = "struct"

TypeAliases = dict(
    {
        "int": "int32_t",
        "unsigned int": "uint32_t",
        "short": "int16_t",
        "unsigned short": "uint16_t",
        "unsigned char": "uint8_t"
    }
)

NodeList = dict()
NodeTree = {
        EName : "",
        EFullName: "",
        EType: "",
        EAccess: "",
        EScope: "",
    }

NodeStack = [NodeTree]

def GetScope(cursor, accum : str = "") :
    if not cursor.semantic_parent.kind.is_translation_unit() :
        if accum != "" :
            accum = "::" + accum
        accum = str(cursor.semantic_parent.canonical.spelling) + accum
        return GetScope(cursor.semantic_parent.canonical, accum)
    
    return accum

def GetFullName(cursor) :
    accum = str(cursor.spelling)
    return GetScope(cursor, accum)

def AppendToStackTop(node, node_type : str) :
    if not node_type in NodeStack[-1]:
        NodeStack[-1][node_type] = dict()

    NodeStack[-1][node_type][node[EFullName]] = node

def CopyNode(full_name) :
    if full_name in NodeList :
        return dict(NodeList[full_name])
    return None

def PushNode(cursor) :
    global NodeStack
    
    node = dict()
    node[EName] = str(cursor.spelling)
    node[EFullName] = GetFullName(cursor)
    node[EType] = str(cursor.type.spelling)
    node[EAccess] = str(cursor.access_specifier)
    node[EScope] = GetScope(cursor)

    NodeStack.append(node)
    return NodeStack[-1]

def PopNode() :
    global NodeStack
    NodeStack = NodeStack[:-1]

def ParseFunction(cursor) :
    node = PushNode(cursor)
    
    for child in cursor.get_children() :
        if child.kind == CursorKind.PARM_DECL:
            param = PushNode(child)
            PopNode()
            AppendToStackTop(param, EParameters)

    PopNode()

    AppendToStackTop(node, EFunctions)
    NodeList[node[EFullName]] = node

    return node

def ParseVar(cursor) :
    node = PushNode(cursor)
    PopNode()

    AppendToStackTop(node, EVariables)
    NodeList[node[EFullName]] = node
    
    return node

def ParseStruct(cursor) :
    node = PushNode(cursor)

    if cursor.kind == CursorKind.CLASS_TEMPLATE :
        node[EType] = EClassTemplate
    elif cursor.kind == CursorKind.CLASS_DECL :
        node[EType] = EClass
    else :
        node[EType] = EStruct

    for child in cursor.get_children() :
        if child.kind == CursorKind.CXX_BASE_SPECIFIER :
            AppendToStackTop({EFullName: GetFullName(child)}, EParents)
            continue

        if child.kind == CursorKind.CXX_METHOD:
            fn = ParseFunction(child)
            AppendToStackTop(fn, EFunctions)
            continue

        if child.kind == CursorKind.FIELD_DECL :
            var = ParseVar(child)
            AppendToStackTop(var, EVariables)

        if child.kind == CursorKind.TEMPLATE_TYPE_PARAMETER or child.kind == CursorKind.TEMPLATE_NON_TYPE_PARAMETER or child.kind == CursorKind.TEMPLATE_TEMPLATE_PARAMETER:
            param = PushNode(child)
            PopNode()

            if child.kind == CursorKind.TEMPLATE_TYPE_PARAMETER :
                param[EType] = "template_type_parameter"
            elif child.kind == CursorKind.TEMPLATE_NON_TYPE_PARAMETER :
                param[EType] = "template_non_type_parameter"
            elif child.kind == CursorKind.TEMPLATE_PARAMETER :
                param[EType] = "template_template_parameter"

            AppendToStackTop(param, EParameters)

            continue

        ParseCursor(child)

    PopNode()

    return node

def ParseEnum(cursor) :
    node = PushNode(cursor)

    node[EType] = EEnum
    node[EUnderlyingType] = str(cursor.enum_type.spelling)
    node[EValueMap] = dict()

    for child in cursor.get_children() :
        if child.kind == CursorKind.ENUM_CONSTANT_DECL :
            node[EValueMap][child.spelling] = str(child.enum_value)

    PopNode()

    AppendToStackTop(node, EEnums)
    NodeList[node[EFullName]] = node

def ParseNamespace(cursor) :
    node = PushNode(cursor)
    for child in cursor.get_children() :
        ParseCursor(child)
    PopNode()

    AppendToStackTop(node, ENamespaces)

def ParseTypeAlias(cursor) :
    typeName = "::".join(map(lambda x: x.spelling, cursor.get_children()))
    node = CopyNode(typeName)
    if node == None : 
        return
    
    nodeType = node[EType]
    node[EName] = str(cursor.spelling)
    node[EFullName] = GetFullName(cursor)
    node[EType] = EAlias
    node[EAccess] = str(cursor.access_specifier)
    node[EScope] = GetScope(cursor)
    node[EUnderlyingType] = str(cursor.underlying_typedef_type.spelling)

    if nodeType == EStruct or nodeType == EClass or nodeType == EClassTemplate :
        AppendToStackTop(node, EStructs)        

def ParseCursor(cursor) :
    if cursor.kind.is_translation_unit() :
        for child in cursor.get_children() :
            ParseCursor(child)
        return

    if cursor.kind == CursorKind.NAMESPACE :
        ParseNamespace(cursor)
        return

    if GetFullName(cursor) in NodeList :
        return

    if cursor.kind == CursorKind.STRUCT_DECL or cursor.kind == CursorKind.CLASS_DECL or cursor.kind == CursorKind.CLASS_TEMPLATE :
        if cursor.is_definition() :
            node = ParseStruct(cursor)   
            AppendToStackTop(node, EStructs)
            NodeList[node[EFullName]] = node
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

def ParseHeader(filePath : str) :
    with open(filePath) as file:
        args = ['-x', 'c++', '-std=c++17']
        idx = clang.cindex.Index.create()
        tu = idx.parse(os.path.join(os.getcwd(), filePath), args = args, options = clang.cindex.TranslationUnit.PARSE_INCOMPLETE | clang.cindex.TranslationUnit.PARSE_INCLUDE_BRIEF_COMMENTS_IN_CODE_COMPLETION | clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)

        for cursor in tu.cursor.walk_preorder():
            ParseCursor(cursor)

def CodeGen() :
    code = ""

    for node in NodeList :
        meta_decl = ""
        meta_decl.append("struct SMeta {\n")
        meta_decl.append()
        meta_decl.append("}meta;\n")
        code = code + "template<> constexpr auto meta<{node[EFullName]}>() { " + meta_decl + "return meta;}"

ParseHeader("tests\\template.h")
#ParseHeader("tests\\enum.h")
#ParseHeader("tests\\class.h")
#ParseHeader("tests\\function.h")
#ParseHeader("tests\\struct.h")
#ParseHeader("tests\\namespace.h")

exit(0)