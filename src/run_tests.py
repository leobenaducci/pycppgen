import os
from pycppgen import main

path = os.getcwd()
if not path.endswith("tests") :
    os.chdir("tests")

path = os.getcwd()
if not path.endswith("tests") :
    exit(-1)

includes = [r'-IC:/Leo/VkFramework/intermediate/../source/vkfw']
main(["C:/Leo/VkFramework/Intermediate/../source/vkfw", "-DVKFW=1"] + includes)

includes = [r"--IC:\Hola;c:\hola con espacio;c:\test"]
#main(["..`/tests"] + includes)

os.makedirs("cpp", exist_ok=True)
os.chdir("cpp")
os.system("cmake .\\..\\")
