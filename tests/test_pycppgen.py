#end to end tests: each one writes a few headers into a scratch project, runs pycppgen on it the way a build
#does, and checks what it generated. needs the libclang bindings; the HLSL tests also need dxc and
#spirv-cross (VULKAN_SDK, or PYCPPGEN_DXC and PYCPPGEN_SPIRV_CROSS) and are skipped without them.
#
#   python -m unittest discover -s tests -v
#
#PYCPPGEN_SRC points the tests at another copy of src/ (to compare against an older pycppgen, say).
import os
import shutil
import subprocess
import sys
import tempfile
import textwrap
import unittest

SRC = os.environ.get("PYCPPGEN_SRC", os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "src"))
SCRIPT = os.path.abspath(os.path.join(SRC, "pycppgen.py"))

sys.path.insert(0, os.path.abspath(SRC))
from pyhlslgen import FindShaderTool

HAVE_SHADER_TOOLS = FindShaderTool("PYCPPGEN_DXC", "dxc") is not None and FindShaderTool("PYCPPGEN_SPIRV_CROSS", "spirv-cross") is not None

class Project :
    #<root>/source/<name> is the project, so the .gen.hlsli land in <root>/shaders/Types as they do in a real tree
    def __init__(self, root : str, name : str = "proj") :
        self.root = root
        self.path = os.path.join(root, "source", name)
        os.makedirs(self.path, exist_ok=True)

    def write(self, relPath : str, text : str) :
        path = os.path.join(self.path, relPath)
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "w", encoding="utf-8", newline="\n") as f :
            f.write(textwrap.dedent(text))
        return path

    def remove(self, relPath : str) :
        os.remove(os.path.join(self.path, relPath))

    def read(self, relPath : str) -> str :
        with open(os.path.join(self.path, relPath), encoding="utf-8") as f :
            return f.read()

    def exists(self, relPath : str) -> bool :
        return os.path.exists(os.path.join(self.path, relPath))

    def hlsli(self, name : str) -> str :
        return os.path.join(self.root, "shaders", "Types", name)

    def run(self, *extra, check : bool = True) -> subprocess.CompletedProcess :
        #a separate process per run, as a build does: pycppgen keeps its state in module globals
        result = subprocess.run([sys.executable, SCRIPT, self.path, *extra], capture_output=True, text=True, cwd=self.root)
        if check and result.returncode != 0 :
            raise AssertionError(f"pycppgen failed ({result.returncode}):\n{result.stdout}\n{result.stderr}")
        return result

class TestCase(unittest.TestCase) :
    #assertIn would print the whole generated file on a failure
    def assertHas(self, needle : str, text : str) :
        if needle not in text : self.fail(f"missing: {needle!r}")

    def assertHasNot(self, needle : str, text : str) :
        if needle in text : self.fail(f"unexpected: {needle!r}")

    def setUp(self) :
        self.tmp = tempfile.mkdtemp(prefix="pycppgen_test_")
        self.project = Project(self.tmp)

    def tearDown(self) :
        shutil.rmtree(self.tmp, ignore_errors=True)

class TestExclude(TestCase) :
    def test_exclude_leaves_the_declaration_out(self) :
        self.project.write("a.h", """
            //$[[pycppgen]]
            struct SKept
            {
                //$[[pycppgen serialize]]
                int A;
                //$[[pycppgen serialize;exclude]]
                int B;
            };

            //$[[pycppgen exclude]]
            struct SDropped { int C; };

            //$[[pycppgen exclude=false]]
            struct SNotDropped { int D; };
            """)
        self.project.run()
        gen = self.project.read("a.gen.h")
        self.assertHas("struct pycppgen<SKept>", gen)
        self.assertHas("get_A_member_variable_info", gen)
        self.assertHasNot("get_B_member_variable_info", gen)
        self.assertHasNot("SDropped", gen)
        self.assertHas("struct pycppgen<SNotDropped>", gen)

if __name__ == "__main__" :
    unittest.main()
