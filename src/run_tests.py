import os
from pycppgen import main

path = os.getcwd()
if not path.endswith("tests") :
    os.chdir("tests")

path = os.getcwd()
if not path.endswith("tests") :
    exit(-1)

path = "C:/Leo/VkFramework/intermediate/../source/vkfw"

main([path, "-DVKFW=1", "-I..\\"])
#main(["../tests"])

os.makedirs("cpp", exist_ok=True)
os.chdir("cpp")
os.system("cmake .\\..\\")
