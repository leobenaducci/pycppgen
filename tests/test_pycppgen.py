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

    def run(self, *extra, check : bool = True, script : str = SCRIPT) -> subprocess.CompletedProcess :
        #a separate process per run, as a build does: pycppgen keeps its state in module globals
        result = subprocess.run([sys.executable, script, self.path, *extra], capture_output=True, text=True, cwd=self.root)
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

class TestAttributeGrammar(unittest.TestCase) :
    def split(self, text) :
        from pycppgen import SplitAttributes
        return SplitAttributes(text)

    def test_unquoted_values_parse_as_before(self) :
        self.assertEqual(self.split("serialize;editable;category=Transform;step=0.1f"),
                         [("serialize", ""), ("editable", ""), ("category", "Transform"), ("step", "0.1f")])
        self.assertEqual(self.split(" a = b c ; d ;"), [("a", "b c"), ("d", "")])
        self.assertEqual(self.split("requires=Other:Value;options=a|b|c"), [("requires", "Other:Value"), ("options", "a|b|c")])

    def test_quoted_value_keeps_semicolons_and_equals(self) :
        self.assertEqual(self.split('tooltip="0 is off; 1 is on, a=b";label=X'), [("tooltip", "0 is off; 1 is on, a=b"), ("label", "X")])
        self.assertEqual(self.split('tooltip = "say \\"hi\\" \\\\ bye" ;x'), [("tooltip", 'say "hi" \\ bye'), ("x", "")])

    def test_second_equals_is_part_of_the_value(self) :
        self.assertEqual(self.split("expr=a=b"), [("expr", "a=b")])

    def test_empty_attributes_are_skipped(self) :
        self.assertEqual(self.split(";;a;; ;"), [("a", "")])

class TestAttributes(TestCase) :
    def test_quoted_tooltip_reaches_the_generated_code_whole(self) :
        self.project.write("a.h", """
            //$[[pycppgen]]
            struct SConfig
            {
                //$[[pycppgen tooltip="0 is off; higher is \\"more\\"";clamp_min=0]]
                int Level;
            };
            """)
        self.project.run()
        gen = self.project.read("a.gen.h")
        self.assertHas('{ "tooltip", "0 is off; higher is \\"more\\"" }', gen)
        self.assertHas('{ "clamp_min", "0" }', gen)

class TestHlslEnum(TestCase) :
    def test_flags_and_bitmask_set_is_bitmask(self) :
        self.project.write("Enums.h", """
            //$[[pycppgen hlsl;flags]]
            enum class EFlags : unsigned int { A = 1, B = 2 };
            //$[[pycppgen hlsl;bitmask]]
            enum class EBitmask : unsigned int { A = 1, B = 2 };
            //$[[pycppgen hlsl]]
            enum class EPlain : unsigned int { A = 0, B = 1 };
            //$[[pycppgen hlsl]]
            enum class ESigned : int { Neg = -1, Zero = 0 };
            //$[[pycppgen hlsl]]
            enum class EShort : short { Neg = -2 };
            //$[[pycppgen hlsl]]
            enum class EUnsignedShort : unsigned short { A = 2 };
            """)
        self.project.run()
        with open(self.project.hlsli("Enums.gen.hlsli"), encoding="utf-8") as f :
            hlsl = f.read()
        def block(name) :
            return hlsl[hlsl.index(f"struct pyhlslgen<{name}>") :][:400]
        self.assertHas("is_bitmask   = true", block("EFlags"))
        self.assertHas("is_bitmask   = true", block("EBitmask"))
        self.assertHas("is_bitmask   = false", block("EPlain"))
        self.assertHas("static const int ESigned_Neg = -1;", hlsl)
        self.assertHas("static const int EShort_Neg = -2;", hlsl)
        self.assertHas("static const uint EUnsignedShort_A = 2;", hlsl)

class TestCache(TestCase) :
    def test_a_change_to_any_script_regenerates_everything(self) :
        self.project.write("a.h", """
            //$[[pycppgen]]
            struct SA { int A; };
            """)
        scripts = os.path.join(self.tmp, "src")
        shutil.copytree(SRC, scripts, ignore=shutil.ignore_patterns("__pycache__"))
        script = os.path.join(scripts, "pycppgen.py")
        self.project.run(script=script)
        self.assertNotIn("Outdated file cache", self.project.run(script=script).stdout)
        for name in ("pyhlslgen.py", "common.py") :
            future = os.path.getmtime(self.project.path + "/pycppgen.cache") + 10
            os.utime(os.path.join(scripts, name), (future, future))
            self.assertIn("Outdated file cache", self.project.run(script=script).stdout, name)
            os.utime(os.path.join(scripts, name), (0, 0))

class TestParents(TestCase) :
    def test_a_reflected_global_base_from_another_header_is_a_parent(self) :
        self.project.write("Base.h", """
            #pragma once
            //$[[pycppgen]]
            struct SBase { int A; };
            struct SUnreflected { int C; };
            """)
        self.project.write("Derived.h", """
            #pragma once
            #include "Base.h"
            //$[[pycppgen]]
            struct SDerived : SBase, SUnreflected { int B; };
            """)
        self.project.run()
        gen = self.project.read("Derived.gen.h")
        self.assertHas("struct pycppgen<SDerived> : SDerived, virtual pycppgen<SBase>{", gen)

class TestIncremental(TestCase) :
    def touch_after_cache(self, relPath : str) :
        future = os.path.getmtime(os.path.join(self.project.path, "pycppgen.cache")) + 10
        os.utime(os.path.join(self.project.path, relPath), (future, future))

    def test_a_changed_include_reparses_the_header(self) :
        self.project.write("Base.h", """
            #pragma once
            namespace ns {
            //$[[pycppgen]]
            struct SBase { int A; };
            }
            """)
        self.project.write("Derived.h", """
            #pragma once
            #include "Base.h"
            namespace ns {
            //$[[pycppgen]]
            struct SDerived : SBase { int B; };
            }
            """)
        self.project.run()
        gen = self.project.read("Derived.gen.h")
        self.assertHas("virtual pycppgen<ns::SBase>", gen)

        #the base loses its tag; Derived.h itself does not change
        self.project.write("Base.h", """
            #pragma once
            namespace ns {
            //$[[pycppgen-include SOther]]
            struct SBase { int A; };
            }
            """)
        self.touch_after_cache("Base.h")
        self.project.run()
        self.assertHasNot("pycppgen<ns::SBase>", self.project.read("Derived.gen.h"))
        self.assertHasNot("ns::SBase", self.project.read("pycppgen.gen.h"))

class TestHlslOutputs(TestCase) :
    #an `hlsl` enum is enough to give a header a .gen.hlsli, and needs no shader compiler
    HLSL_ENUM = """
        #pragma once
        //$[[pycppgen hlsl]]
        enum class E{0} : unsigned int {{ A = 0 }};
        """

    def test_a_fresh_tree_with_many_hlsl_headers(self) :
        #the workers used to race to create shaders/Types, and the losers failed
        for i in range(16) :
            self.project.write(f"H{i}.h", self.HLSL_ENUM.format(f"H{i}"))
        self.project.run()
        for i in range(16) :
            self.assertTrue(os.path.exists(self.project.hlsli(f"H{i}.gen.hlsli")))

    def test_a_renamed_header_takes_its_hlsli_along(self) :
        self.project.write("Old.h", self.HLSL_ENUM.format("Old"))
        self.project.run()
        self.assertTrue(os.path.exists(self.project.hlsli("Old.gen.hlsli")))

        self.project.remove("Old.h")
        self.project.write("New.h", self.HLSL_ENUM.format("New"))
        self.project.run()
        self.assertFalse(os.path.exists(self.project.hlsli("Old.gen.hlsli")))
        self.assertTrue(os.path.exists(self.project.hlsli("New.gen.hlsli")))

    def test_a_header_that_loses_its_hlsl_loses_its_hlsli(self) :
        self.project.write("A.h", self.HLSL_ENUM.format("A"))
        self.project.run()
        self.project.write("A.h", """
            //$[[pycppgen]]
            enum class EA : unsigned int { A = 0 };
            """)
        self.project.run()
        self.assertFalse(os.path.exists(self.project.hlsli("A.gen.hlsli")))

    def test_two_headers_writing_the_same_hlsli_fail_the_run(self) :
        self.project.write("a/Same.h", self.HLSL_ENUM.format("One"))
        self.project.write("b/Same.h", self.HLSL_ENUM.format("Two"))
        result = self.project.run(check=False)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("Same.gen.hlsli", result.stdout)

    def test_a_namesake_without_hlsl_leaves_the_hlsli_alone(self) :
        self.project.write("a/Same.h", self.HLSL_ENUM.format("One"))
        self.project.write("b/Same.h", """
            //uses a _pyhlslgen struct from elsewhere
            //$[[pycppgen]]
            struct SUser { int A; };
            """)
        for _ in range(2) :
            self.project.run()
            self.assertTrue(os.path.exists(self.project.hlsli("Same.gen.hlsli")))

    def test_a_dependency_writing_the_same_hlsli_fails_the_run(self) :
        lib = Project(self.tmp, "lib")
        lib.write("Same.h", self.HLSL_ENUM.format("One"))
        lib.run()
        self.project.write("Same.h", self.HLSL_ENUM.format("Two"))
        result = self.project.run("--P../lib", check=False)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("Same.gen.hlsli", result.stdout)

if __name__ == "__main__" :
    unittest.main()
