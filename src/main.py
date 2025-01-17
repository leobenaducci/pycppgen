import os;
import io;
import clang.cindex
from clang.cindex import CursorKind

nodeList = list()
nodeStack = []

def PushNode(cursor) :
    global nodeStack
    
    node = dict()
    node["full_name"] = node["name"] = str(cursor.spelling)
    node["type"] = str(cursor.type.spelling)
    node["access"] = str(cursor.access_specifier)

    node["scope"] = ""
    for i in nodeStack :
        node["scope"] = i["full_name"] + "::"
    if node["scope"].endswith("::") :
        node["scope"] = node["scope"][:-2]
    if node["scope"] != "" :
        node["full_name"] = node["scope"] + "::" + node["name"]

    nodeStack = nodeStack + [node]
    return nodeStack[-1]

def PopNode(node = None) :
    global nodeStack, nodeList
    if node != None :
        nodeList = nodeList + [nodeStack[-1] | node]
    nodeStack = nodeStack[:-1]

def ParseFunction(cursor) :
    node = PushNode(cursor)
    node["params"] = []
    
    # CursorKind.CONVERSION_FUNCTION = CursorKind(26)
    #CursorKind.PARM_DECL = CursorKind(10)
    for child in cursor.get_children() :
        if child.kind == CursorKind.PARM_DECL:
            param = PushNode(cursor)
            node["params"] = node["params"] + dict(param)
            PopNode(param)

    PopNode(node)
    nodeStack[-1]["functions"] = nodeStack[-1]["functions"] + [node]

    return

def ParseVar(cursor) :
    return

def ParseField(cursor) :
    node = PushNode(cursor)
    PopNode()

    nodeStack[-1]["variables"] = nodeStack[-1]["variables"] + [node]

    return

def ParseStruct(cursor) :
    #CursorKind.CXX_ACCESS_SPEC_DECL
    #CursorKind.FIELD_DECL = CursorKind(6)
    #CursorKind.CXX_METHOD = CursorKind(21)
    #CursorKind.CONSTRUCTOR = CursorKind(24)
    #CursorKind.DESTRUCTOR = CursorKind(25)``
    
    node = PushNode(cursor)

    node["type"] = "struct"
    node["variables"] = []
    node["functions"] = []
   
    for child in cursor.get_children() :
        ParseCursor(child)

    PopNode(node)

    return

def ParseEnum(cursor) :
    # An enumerator constant.
    #CursorKind.ENUM_CONSTANT_DECL = CursorKind(7)
    #for child in node.get_children() :
    #    ParseCursor(child)
    return

def ParseNamespace(cursor) :
    node = PushNode(cursor)
    for child in cursor.get_children() :
        ParseCursor(child)
    PopNode(node)

def ParseCursor(cursor) :
    print(str(cursor.kind) + " -> " + str(cursor.displayname))

    if cursor.kind.is_translation_unit() :
        for child in cursor.get_children() :
            ParseCursor(child)
        return

    if cursor.kind == CursorKind.STRUCT_DECL or cursor.kind == CursorKind.CLASS_DECL :
        ParseStruct(cursor)
        return

    if cursor.kind == CursorKind.FIELD_DECL :
        ParseField(cursor)
        return

    if cursor.kind == CursorKind.VAR_DECL :
        ParseVar(cursor)
        return

    if cursor.kind == CursorKind.ENUM_DECL :
        ParseEnum(cursor)
        return

    if cursor.kind == CursorKind.FUNCTION_DECL :
        return
    
    if cursor.kind == CursorKind.UNION_DECL :
        return
    
    if cursor.kind == CursorKind.NAMESPACE :
        return

    if cursor.kind == CursorKind.TYPEDEF_DECL :
        return
    
    if cursor.kind == CursorKind.TYPE_ALIAS_DECL :
        return


def ParseHeader(filePath : str) :
    with open(filePath) as file:
        args = ['-x', 'c++', '-std=c++17']
        idx = clang.cindex.Index.create()
        tu = idx.parse(os.path.join(os.getcwd(), filePath), args = args) #, options = clang.cindex.TranslationUnit.PARSE_INCOMPLETE | clang.cindex.TranslationUnit.PARSE_INCLUDE_BRIEF_COMMENTS_IN_CODE_COMPLETION | clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)

        ParseCursor(tu.cursor)

ParseHeader("tests\\enum.h")
ParseHeader("tests\\class.h")
ParseHeader("tests\\function.h")
ParseHeader("tests\\struct.h")

exit(0)