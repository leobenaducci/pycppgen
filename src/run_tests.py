import os
from main import ParseFile

path = os.getcwd()
if not path.endswith("tests") :
    os.chdir("tests")

path = os.getcwd()
if not path.endswith("tests") :
    exit(-1)

ParseFile(path + "\\enum.h")
ParseFile(path + "\\class.h")
ParseFile(path + "\\function.h")
ParseFile(path + "\\namespace.h")
ParseFile(path + "\\struct.h")
ParseFile(path + "\\template.h")

os.makedirs("cpp", exist_ok=True)
os.chdir("cpp")
os.system("cmake .\\..\\")
