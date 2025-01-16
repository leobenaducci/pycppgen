import os;
import io;
import clang.cindex
from clang.cindex import CursorKind

typeList = list()

currentType = dict()
currentScope = []

def PushScope(scope) :
    global currentScope
    currentScope = currentScope + [scope]

def PopScope() :
    global currentScope
    currentScope = currentScope[:-1]

def ParseFunction(node) :
    # CursorKind.CONVERSION_FUNCTION = CursorKind(26)
    #CursorKind.PARM_DECL = CursorKind(10)
    print(str(cursor.kind) + " -> " + str(cursor.displayname))
    for child in cursor.get_children() :
        ParseCursor(child)
    return

def ParseVar(node) :
    return

def ParseField(node) :
    global currentType

    newVariable = dict()
    newVariable["full_name"] = newVariable["name"] = node.spelling
    newVariable["scope"] = ""

    if len(currentScope) > 0 :
        newVariable["scope"] = "::".join(currentScope)
        newVariable["full_name"] = newVariable["scope"] + "::" + newVariable["name"]

    newVariable["type"] = str(node.type.spelling)
    currentType["variables"] = currentType["variables"] + [newVariable]

    return

def ParseStruct(node) :
    #CursorKind.CXX_ACCESS_SPEC_DECL
    #CursorKind.FIELD_DECL = CursorKind(6)
    #CursorKind.CXX_METHOD = CursorKind(21)
    #CursorKind.CONSTRUCTOR = CursorKind(24)
    #CursorKind.DESTRUCTOR = CursorKind(25)``
    
    print(str(node.kind) + " -> " + str(node.spelling))

    currentType["full_name"] = currentType["name"] = str(node.spelling)
    currentType["scope"] = ""

    if len(currentScope) > 0 :
        currentType["scope"] = "::".join(currentScope)
        currentType["full_name"] = currentType["scope"] + "::" + currentType["name"]

    currentType["type"] = "struct"
    currentType["variables"] = []
    currentType["functions"] = []
    
    PushScope(node.spelling)
    
    for child in node.get_children() :
        ParseCursor(child)
        
    PopScope()

    return

def ParseEnum(node) :
    # An enumerator constant.
    #CursorKind.ENUM_CONSTANT_DECL = CursorKind(7)
    for child in node.get_children() :
        ParseCursor(child)
    return

def ParseNamespace(node) :

    PushScope(node.spelling)
    currentScope = currentScope + [node.spelling]
    for child in node.get_children() :
        ParseCursor(child)
    PopScope()

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

