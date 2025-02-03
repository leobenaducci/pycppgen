import os
from pycppgen import main

path = os.getcwd()
if not path.endswith("tests") :
    os.chdir("tests")

path = os.getcwd()
if not path.endswith("tests") :
    exit(-1)

main(["../tests/lib"])
main(["../tests/app", "--P../lib", "--I../lib"])

os.makedirs("build", exist_ok=True)
os.chdir("build")
os.system("cmake .\\..\\")
