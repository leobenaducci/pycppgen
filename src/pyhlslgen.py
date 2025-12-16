from common import *

kHlslTypes: Final[list]= ["int", "uint", "float", "bool", "double", "int64_t", "uint64_t", "float16_t", "int16_t", "uint16_t", "int8_t", "uint8_t"]
kPyHlslVectorTypes: Final[list]= ["int", "uint", "float", "bool", "double", "int64_t", "uint64_t", "int16_t", "uint16_t", "int8_t", "uint8_t"]
kPyHlslMatrixTypes: Final[list]= ["int", "uint", "float", "double", "int64_t", "uint64_t"]

def GenHlslDeclarations() :
    result = "\n"
    for t in kHlslTypes :
        for m in range(2, 5) :
            for n in range(2, 5) :
                result += f"using {t}{m}x{n} = float;\n"
            result += f"using {t}{m} = float;\n"
    result += "using float16_t = float;\n"
    result += "using uint = unsigned int;\n"
    result += "\n"

    return result

def GenVkToHlslMappings() :
    vkToHlsl = {}

    for t in kHlslTypes :
        vkToHlsl[t] = t

    for r in range(2, 5) :
        vkToHlsl[f"ivec{r}"] = f"int{r}"
        vkToHlsl[f"uvec{r}"] = f"uint{r}"
        vkToHlsl[f"vec{r}"] = f"float{r}"
        vkToHlsl[f"bvec{r}"] = f"bool{r}"
        vkToHlsl[f"dvec{r}"] = f"double{r}"
        vkToHlsl[f"u64vec{r}"] = f"uint64_t{r}"        
        vkToHlsl[f"i64vec{r}"] = f"int64_t{r}"        
        vkToHlsl[f"f16vec{r}"] = f"float16_t{r}"
        vkToHlsl[f"i16vec{r}"] = f"int16_t{r}"
        vkToHlsl[f"u16vec{r}"] = f"uint16_t{r}"
        vkToHlsl[f"i8vec{r}"] = f"int8_t{r}"
        vkToHlsl[f"u8vec{r}"] = f"uint8_t{r}"

        vkToHlsl[f"mat{r}"] = f"float{r}x{r}"
        vkToHlsl[f"imat{r}"] = f"int{r}x{r}"
        vkToHlsl[f"umat{r}"] = f"uint{r}x{r}"
        vkToHlsl[f"bmat{r}"] = f"bool{r}x{r}"
        vkToHlsl[f"dmat{r}"] = f"double{r}x{r}"
        vkToHlsl[f"u64mat{r}"] = f"uint64_t{r}x{r}"
        vkToHlsl[f"f16mat{r}"] = f"float16_t{r}x{r}"
        vkToHlsl[f"i16mat{r}"] = f"int16_t{r}x{r}"
        vkToHlsl[f"u16mat{r}"] = f"uint16_t{r}x{r}"
        vkToHlsl[f"i8mat{r}"] = f"int8_t{r}x{r}"
        vkToHlsl[f"u8mat{r}"] = f"uint8_t{r}x{r}"
        for c in range(2, 5) :
            vkToHlsl[f"mat{r}x{c}"] = f"float{r}x{c}"
            vkToHlsl[f"dmat{r}x{c}"] = f"double{r}x{c}"
            vkToHlsl[f"imat{r}x{c}"] = f"int{r}x{c}"
            vkToHlsl[f"umat{r}x{c}"] = f"uint{r}x{c}"
            vkToHlsl[f"bmat{r}x{c}"] = f"bool{r}x{c}"
            vkToHlsl[f"u64mat{r}x{c}"] = f"uint64_t{r}x{c}"
            vkToHlsl[f"f16mat{r}x{c}"] = f"float16_t{r}x{c}"
            vkToHlsl[f"i16mat{r}x{c}"] = f"int16_t{r}x{c}"
            vkToHlsl[f"u16mat{r}x{c}"] = f"uint16_t{r}x{c}"
            vkToHlsl[f"i8mat{r}x{c}"] = f"int8_t{r}x{c}"
            vkToHlsl[f"u8mat{r}x{c}"] = f"uint8_t{r}x{c}"

    return vkToHlsl

kHlslDeclarations : Final[str] = GenHlslDeclarations()
kVkToHlsl : Final[dict] = GenVkToHlslMappings()

kPyhlslgenHeader = """
template<typename T = void> struct pyhlslgen 
{
    using type_t = T; 
    static constexpr bool is_valid = false;
    static constexpr bool is_primitive = false;
    static constexpr bool uniform_alignment = false;
    static constexpr bool relaxed_alignment = false;
    static constexpr bool scalar_alignment = false;
    static constexpr char type_name[] = ""; 
    static constexpr char full_decl[] = ""; 
    static constexpr char struct_decl[] = ""; 
    static constexpr char cbuffer_decl[] = "";
};

#ifndef _HLSL_TYPES_DECLARED_
"""

for v in kPyHlslVectorTypes :
    kPyhlslgenHeader += f"""template<> struct pyhlslgen<{v}> {{ using type_t = {v}; static constexpr bool is_valid = true; static constexpr bool is_primitive = true; static constexpr bool scalar_alignment = true; static constexpr char type_name[] = "{v}";  }};\n"""
    for i in range(2, 5) :
        kPyhlslgenHeader += f"""template<> struct pyhlslgen<{v}{i}> {{ using type_t = {v}{i}; static constexpr bool is_valid = true; static constexpr bool is_primitive = true; static constexpr bool scalar_alignment = true; static constexpr char type_name[] = "{v}{i}";  }};\n"""

for v in kPyHlslMatrixTypes :
    for i in range(2, 5) :
        for e in range(2, 5) :
            kPyhlslgenHeader += f"""template<> struct pyhlslgen<{v}{i}x{e}> {{ using type_t = {v}{i}x{e}; static constexpr bool is_valid = true; static constexpr bool is_primitive = true; static constexpr bool scalar_alignment = true; static constexpr char type_name[] = "{v}{i}x{e}";  }};\n"""

kPyhlslgenHeader += "#endif // _HLSL_TYPES_DECLARED_\n"

def RemoveHlsl(var : str) :
    return var.replace("_pyhlslgen_uniform", "").replace("_pyhlslgen_relaxed", "").replace("_pyhlslgen_scalar", "").replace("_pyhlslgen", "")

def IsHlsl(var : str) :
    return var.endswith("_pyhlslgen_uniform") or var.endswith("_pyhlslgen_relaxed") or var.endswith("_pyhlslgen_scalar") or var.endswith("_pyhlslgen")

def GetHlslAlignment(var : str) :
    if var.endswith("_pyhlslgen_uniform") :
        return "uniform"
    if var.endswith("_pyhlslgen_scalar") :
        return "scalar"
    if var.endswith("_pyhlslgen_relaxed") or var.endswith("_pyhlslgen"):
        return "relaxed"
    
    return "NONE"

def PreParseHlsl(varType : str, layout : str) -> tuple[int, str, int, int, int]:

    #match type<n>x<m>[s] patterns
    match = re.fullmatch(rf'({"|".join(kHlslTypes)})(\d)?(?:x(\d))?(?:\[(\w+)\])?', varType)
    if match:
        baseType, rows, cols, arraySize = match.groups()

        if rows : rows = int(rows)
        else: rows = 1
        if cols : cols = int(cols)
        else: cols = 1
        if arraySize : arraySize = int(arraySize)
        else: arraySize = 1

        if baseType.startswith('uint64_t') | baseType.startswith('double'):
            size = 8
        elif baseType.find('16_t') != -1 :
            size = 2
        else :
            size = 4

        #strict ubo140?
        #if layout == "uniform" : #Rule 1a: Vector types are aligned according to their scalar component type.
        #    vrows = 1
        #    
        #    if arraySize > 1:
        #        if size == 8 :
        #            rows = ((rows + 1) / 2) * 2
        #        elif size == 2 :
        #            return 0, baseType, int(arraySize), int(rows), int(cols)
        #        else :
        #            rows = 4
        #    else :
        #        if size == 8 :
        #            vrows = ((rows + 1) / 2) * 2
        #        elif size == 2 :
        #            vrows = 8
        #        else :
        #            vrows = 4
        #        
        #    if rows > 1 and cols > 1 :
        #        rows = 4
        #        size *= rows * cols
        #    elif rows > 1:
        #        size *= rows
        #    size *= vrows
        #    size /= rows
        if layout == "uniform" :
            if arraySize > 1:
                if size == 8 :
                    rows = ((rows + 1) / 2) * 2
                elif size == 2 :
                    return 0, baseType, int(arraySize), int(rows), int(cols)
                else :
                    rows = 4
            if rows > 1 and cols > 1:
                size *= rows * cols
            elif rows > 1:
                size *= rows
        else :
            if rows > 1 and cols > 1:
                size *= rows * cols
            elif rows > 1:
                size *= rows

        if arraySize:
            size *= arraySize

        return int(size), baseType, int(arraySize), int(rows), int(cols)
    
    return 0, "", 1, 1, 1
    
#codegen: emit a hlsl node
def CodeGenHlslNode(hlslCode, node) -> str:
    
    vksdk = os.getenv("VULKAN_SDK")
    if vksdk == "":
        return ""

    hlslLayout = node[ENode.HlslLayout]
    hlslTemp = f"struct {node[ENode.Name]}\n{{\n"

    nameSizeMap = {}
    member = ""

    if ENode.Variables in node :
        for _, var in node[ENode.Variables].items() :
            
            size, baseType, arraySize, rows, cols = PreParseHlsl(var[ENode.Type], hlslLayout)
            
            nameSizeMap[var[ENode.Name]] = size

            newDecl = f"\t{baseType}"
            if rows > 1:
                newDecl += f"{rows}"
            if cols > 1:
                newDecl += f"x{cols}"
            else :
                newDecl += f"\t"

            newDecl += f"\t{var[ENode.Name]}"
            if arraySize and int(arraySize) > 1:
                newDecl += f"[{arraySize}]"

            if size == 0 :
                print(f"HLSL Error: Unsupported type {newDecl.replace("\t", " ")} in {node[ENode.Name]}")
                continue

            if member == "" :
                member = var[ENode.Name]
                if arraySize > 1 :
                    member += "[0]"

            hlslTemp += newDecl + ";\n"

    hlslTemp += "};\n"

    if hlslLayout == "uniform" :
        hlslTemp += f"ConstantBuffer<{node[ENode.Name]}> inBuffer;\n"
    elif hlslLayout == "scalar" :
        hlslTemp += f"RWStructuredBuffer<{node[ENode.Name]}> inBuffer;\n"
    elif hlslLayout == "relaxed" :
        hlslTemp += f"StructuredBuffer<{node[ENode.Name]}> inBuffer;\n"

    hlslTemp += f"RWStructuredBuffer<{node[ENode.Name]}> outBuffer;\n"
    hlslTemp += "\n"
    hlslTemp += "[numthreads(1,1,1)]\n"
    hlslTemp += "void main(uint d : SV_DispatchThreadId) {\n"
    hlslTemp += f"\toutBuffer[d].{member} = inBuffer"
    if hlslLayout != "uniform" :
        hlslTemp += "[0]"
    hlslTemp += f".{member};\n}}\n"
    
    fileName = os.path.abspath(f"tmp__{node[ENode.Name]}.tmp_hlsl")
    with open(fileName, "wt") as file:
        file.write(hlslTemp)

    if hlslLayout == "scalar" :
        vk_layout = "-fvk-use-scalar-layout"
    else :
        vk_layout = "-fvk-use-dx-layout"
    result = subprocess.run([f"{vksdk}\\bin\\dxc.exe", "-spirv", "-fspv-target-env=vulkan1.3", "-fspv-reflect", vk_layout, "-enable-16bit-types", "-T cs_6_2", "-E main", f"-Fo {fileName}.spv", fileName], capture_output=True)
    if os.path.exists(f"{fileName}"):
        os.remove(f"{fileName}")

    if result.stderr and len(result.stderr) > 0:
        atomic_print(result.stderr.decode())
        return hlslCode

    result = subprocess.run([f"{vksdk}\\bin\\spirv-cross", f"{fileName}.spv", "--reflect", "--hlsl", "--hlsl-enable-16bit-types"], capture_output=True)
    if os.path.exists(f"{fileName}.spv"):
        os.remove(f"{fileName}.spv")

    if result.stderr and len(result.stderr) > 0:
        atomic_print(result.stderr.decode())
        return hlslCode

    parsed = json.loads(result.stdout.decode())

    typePrefix = ""
    if hlslLayout == "uniform" :
        typePrefix = "ConstantBuffer."

    expectedType = None
    for t in parsed["types"] :
        if parsed["types"][t]["name"].find(f"{typePrefix}{node[ENode.Name]}") != -1 :
            expectedType = parsed["types"][t]
            break

    if expectedType == None :
        return hlslCode
    
    offset = 0
    padNum = 0
    size = 0

    cppNodeName : str = node[ENode.FullName][len(node[ENode.Namespace]):].lstrip('::').replace("::", "_")

    hlslResult = ""

    def applyPad(padSize : int) :
        nonlocal offset, padNum, hlslResult
        while padSize > 0 :
            pad = min(padSize, 16)
            if pad % 4 != 0 :
                newDecl = f"\tuint16_t{pad >> 1} _pad{padNum}_{node[ENode.Name]};"
            else :
                newDecl = f"\tuint{pad >> 2} _pad{padNum}_{node[ENode.Name]};"
            while (len(newDecl.replace("\t", "    ")) / 4) * 4 < 40 : newDecl += '\t'
            newDecl += f"// Offset: {offset} - Size: {pad}\n"
            padNum = padNum + 1
            offset = offset + int(pad)
            padSize -= pad
            hlslResult += newDecl

    for member in expectedType["members"]:

        if offset != member["offset"] and hlslLayout != "scalar":
            applyPad(abs(int(member["offset"]) - offset))

        newDecl = "\t"

        if member["type"] in kVkToHlsl :
            newDecl += kVkToHlsl[member["type"]]
        else :
            newDecl += member["type"]

        newDecl += f" {member["name"]}"

        if "array" in member:
            for a in member["array"]:
                newDecl += f"[{a}]"

        newDecl += ";"

        while (len(newDecl.replace("\t", "    ")) / 4) * 4 < 40 : newDecl += '\t'

        size = int(nameSizeMap[member["name"]])
        hlslResult += f"{newDecl}// Offset: {offset} - Size: {size}\n"
            
        offset += size

    uniform_alignment = True if hlslLayout == "uniform" else False
    scalar_alignment = True if hlslLayout == "scalar" else False

    if not uniform_alignment and not scalar_alignment :
        if offset % 16 != 0 :
            applyPad(16 - offset % 16)

    hlslResult = f"""
struct {cppNodeName}
{{
{hlslResult}}}; // Size: {offset}
"""
    
    hlslDecl = f"""
#ifndef __{cppNodeName.upper()}_DECL__
#define __{cppNodeName.upper()}_DECL__

{hlslResult}

#endif //__{cppNodeName.upper()}_DECL__
"""
    
    openNamespaces = ""
    closeNamespaces = ""
    if node[ENode.Namespace] != "" :
        for ns in node[ENode.Namespace].split('::') :
            openNamespaces += f"namespace {ns} {{\n"
            closeNamespaces += '}\n'
    result = f"""
#ifndef __{cppNodeName.upper()}_DECL__
#define __{cppNodeName.upper()}_DECL__

#ifdef __cplusplus
{openNamespaces}
{hlslResult}
template<> struct pyhlslgen<{cppNodeName}>
{{
    using type_t = {cppNodeName};
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool uniform_alignment = {"true" if uniform_alignment else "false"};
    static constexpr bool relaxed_alignment = {"true" if not uniform_alignment and not scalar_alignment else "false"};
    static constexpr bool scalar_alignment = {"true" if scalar_alignment else "false"};
    static constexpr char type_name[] = "{cppNodeName}"; 
    static constexpr char struct_decl[] = R"-({hlslDecl})-"; 
    static constexpr char uniform_decl[] = R"-({hlslResult.replace(f"struct {cppNodeName}", f"cbuffer {cppNodeName}_")})-";
}};
{closeNamespaces}
#else
{hlslResult}
#endif //__cplusplus
#endif //__{cppNodeName.upper()}_DECL__
"""

    return hlslCode + result