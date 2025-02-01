import os
from pycppgen import main

path = os.getcwd()
if not path.endswith("tests") :
    os.chdir("tests")

path = os.getcwd()
if not path.endswith("tests") :
    exit(-1)

includes = []
includes.append(r'-IC:/Leo/VkFramework/intermediate/../source/vkfw')  
main(["C:/Leo/VkFramework/Intermediate/../source/vkfw", "-DVKFW=1"] + includes)
#main(["../tests"])

os.makedirs("cpp", exist_ok=True)
os.chdir("cpp")
os.system("cmake .\\..\\")
