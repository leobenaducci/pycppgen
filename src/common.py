import os
import re
import subprocess
import json
import pathlib
import subprocess
import sys
import re
import inspect
import json
import contextvars
import threading
from typing import Final, Any
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass

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
    Namespace: Final[str] = "namespace"
    Namespaces: Final[str] = "namespaces"
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
    HlslLayout: Final[str] = "hlsl_layout"

@dataclass(frozen=True, slots=True)
class _ParseCommentsType:
    BeforeDecl: Final[str] = "comments_before_decl"
    AfterDecl: Final[str] = "comments_after_decl"

# Add to global constants
@dataclass(frozen=True, slots=True)
class _Globals:
    kInvalid: Final[str] = "invalid"
    kInclude: Final[str] = "include"
    kSerialize: Final[str] = "serialize"
    kExclude: Final[str] = "exclude"
    kHlsliPath: Final[str] = "../../shaders/Types"
    kCacheVersion : Final[str] = "cache_version"
    kCurrentCacheVersion : Final[str] = "20260315a"

EKind = _Kinds()          # use K.Unknown, K.Class … everywhere
ENode = _NodeType()
EParseComments = _ParseCommentsType()
EGlobals = _Globals()

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

class TLS_Data:
    def __init__(self):
        self.NodesToInclude: list[str] = []
        self.NodeList: dict[str, Any] = {}
        self.NodeTree: dict[str, Any] = {}
        self.NodeStack: list[dict[str, Any]] = [self.NodeTree]
        self.pycppdefine: str = ""
    
PrintLock = threading.Lock()

def atomic_print(text : str) :
    with PrintLock :
        print(f"pycppgen: {text}")

def normalize_cr(text: str) -> str:
    return text.replace("\r\n", "\n").replace("\r", "\n")

def write_file_if_different(file : str, content : str | None) :
    inputContent : str = ""

    if content == None :
        if os.path.exists(file) :
            atomic_print(f"removing {file}")
            os.remove(file)
        return

    try:
        with open(file, mode="rt") as inputFile :
            inputContent = inputFile.read()
    except:
        inputContent = ""

    if normalize_cr(content) == normalize_cr(inputContent) :
        atomic_print(f"skipping {file} as it didn't change")
        os.utime(file, None)
        return

    if not os.path.exists(pathlib.Path(file).parent) :
        os.makedirs(pathlib.Path(file).parent)

    with open(file, mode="wt") as outputFile :
        atomic_print(f"writing {file}")
        outputFile.write(content)
