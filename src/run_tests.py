import os
from pycppgen import main

path = os.getcwd()
if not path.endswith("tests") :
    os.chdir("tests")

path = os.getcwd()
if not path.endswith("tests") :
    exit(-1)

includes = [r'--IC:\VulkanSDK\1.4.304.0/include;C:/Leo/VkFramework/intermediate/../intermediate/3rdparty/VulkanMemoryAllocator/include;C:/Leo/VkFramework/intermediate/3rdparty/glm-src;C:/Leo/VkFramework/intermediate/_deps/stb-src;C:/Leo/VkFramework/intermediate/3rdparty/imgui_markdown_src-src;C:/Leo/VkFramework/intermediate/3rdparty/iconfontcppheaders-src;C:/Leo/VkFramework/intermediate/../intermediate/dxc/inc};C:/Leo/VkFramework/intermediate/_deps/fidelityfx_fsr2-src/src/ffx-fsr2-api;C:/Leo/VkFramework/intermediate/_deps/gameworksnri-src/Include;C:/Leo/VkFramework/intermediate/_deps/gameworksdenoiser-src/Include;C:/Leo/VkFramework/intermediate/_deps/gameworksdenoiser-src/Integration;C:/Leo/VkFramework/intermediate/_deps/constexpr_md5-src/include;C:/Leo/VkFramework/intermediate/../source/vkfw/;C:/Leo/VkFramework/intermediate/../source/vkfw/']
main(["C:/Leo/VkFramework/Intermediate/../source/vkfw", "-DVKFW=1"] + includes)

#includes = []
#main(["../tests"] + includes)

os.makedirs("cpp", exist_ok=True)
os.chdir("cpp")
os.system("cmake .\\..\\")
