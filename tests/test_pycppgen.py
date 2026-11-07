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

#errors libclang finds in a C++ file: a compile check of generated code, with template instantiation, and
#no compiler needed beyond the libclang the generator already uses
def CompileErrors(path : str, includeDirs : list) -> list :
    import clang.cindex
    #-Wno-invalid-constexpr: the generated offset() is offsetof in a constexpr function, which Clang
    #refuses as a constant expression (MSVC and GCC, the compilers the engine is built with, accept it)
    args = ["-x", "c++", "-std=c++20", "-fsyntax-only", "-Wno-invalid-constexpr"] + [f"-I{d}" for d in includeDirs]
    tu = clang.cindex.Index.create().parse(path, args=args)
    #only errors in the scratch project count: a libclang older than the installed standard library
    #reports a few errors inside it (MSVC's STL asks for a newer Clang), which say nothing about our code
    root = os.path.dirname(os.path.dirname(includeDirs[0]))
    def ours(d) :
        return d.location.file is not None and os.path.abspath(d.location.file.name).startswith(os.path.abspath(root))
    return [str(d) for d in tu.diagnostics if d.severity >= clang.cindex.Diagnostic.Error and ours(d)]

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

    def test_a_using_declaration_overrides_attributes_without_the_include_flag(self) :
        self.project.write("a.h", """
            //$[[pycppgen]]
            struct SBase {
                //$[[pycppgen editable]]
                int Scale;
            };
            //$[[pycppgen]]
            struct SDerived : SBase {
                //$[[pycppgen visible=false]]
                using SBase::Scale;
            };
            """)
        self.project.run()
        gen = self.project.read("a.gen.h")
        self.assertHas('result["visible"] = "false";', gen)
        self.assertHasNot('result["include"]', gen)

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
            struct SBase { virtual ~SBase() = default; int A; };
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
            struct SBase { virtual ~SBase() = default; int A; };
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
            struct SBase { virtual ~SBase() = default; int A; };
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

class TestGlobalFiles(TestCase) :
    def test_pycppgen_h_is_not_rewritten_when_it_does_not_change(self) :
        self.project.write("A.h", """
            //$[[pycppgen]]
            struct SA { int A; };
            """)
        self.project.run()
        header = os.path.join(self.project.path, "pycppgen.h")
        os.utime(header, (1000, 1000))
        self.project.write("B.h", """
            //$[[pycppgen]]
            struct SB { int B; };
            """)
        self.project.run()
        self.assertHas("SB", self.project.read("pycppgen.gen.h"))
        self.assertEqual(os.path.getmtime(header), 1000)

    def test_a_deleted_global_file_comes_back(self) :
        self.project.write("A.h", """
            //$[[pycppgen]]
            struct SA { int A; };
            """)
        self.project.run()
        for name in ("pycppgen.gen.h", "pycppgen.h") :
            self.project.remove(name)
            self.project.run()
            self.assertTrue(self.project.exists(name), name)

class TestByName(TestCase) :
    def test_a_full_name_wins_over_an_earlier_short_name(self) :
        self.project.write("A.h", """
            namespace ns {
            //$[[pycppgen]]
            struct Foo { int A; };
            }
            """)
        self.project.write("B.h", """
            //$[[pycppgen]]
            struct Foo { int B; };
            """)
        self.project.run()
        gen = self.project.read("pycppgen.gen.h")
        ctor = gen[gen.index("pycppgen<void>::pycppgen(std::string_view name)") :]
        exact = ctor.index('if (name == "Foo")\n\t{\n\t\tHashCode = typeid(Foo)')
        short = ctor.index('if (name == "Foo")\n\t{\n\t\tHashCode = typeid(ns::Foo)')
        self.assertLess(exact, short)
        self.assertHas("HashCode = 0;", self.project.read("pycppgen.h"))

class TestStaticByName(TestCase) :
    def test_each_type_is_called_once(self) :
        self.project.write("A.h", """
            //$[[pycppgen]]
            struct SA {
                //$[[pycppgen]]
                static void Init() {}
                //$[[pycppgen]]
                static void Shutdown() {}
            };
            """)
        self.project.run()
        gen = self.project.read("pycppgen.gen.h")
        self.assertEqual(gen.count("pycppgen<SA>::call_function(funcName);"), 1)

class TestGeneratedCpp(TestCase) :
    def compile(self, source : str) :
        path = self.project.write("check.cpp", source)
        errors = CompileErrors(path, [self.project.path])
        if errors :
            self.fail("\n".join(errors[:10]))

    def test_the_by_type_dispatches_compile(self) :
        self.project.write("Types.h", """
            #pragma once
            namespace ns {
            //$[[pycppgen serialize]]
            struct SBase { virtual ~SBase() = default;
                //$[[pycppgen serialize]]
                int A = 1;
            };
            //$[[pycppgen serialize]]
            struct SDerived : SBase {
                //$[[pycppgen serialize]]
                float B = 2;
            };
            }
            """)
        self.project.run()
        self.compile("""
            #include "pycppgen.gen.h"

            struct SJson {
                bool contains(const char*) const { return true; }
                SJson operator[](const char*) const { return {}; }
                template<typename T> operator T() const { return T{}; }
                template<typename T> SJson& operator=(const T&) { return *this; }
            };

            void Check(ns::SBase* object, const ns::SBase* constObject) {
                SJson json;
                pycppgen<void>::parse(json, object);
                pycppgen<void>::dump(json, constObject);
                pycppgen<void>::for_each_var(object, []<typename V>(auto&) {});
                pycppgen<void>::for_each_var(constObject, []<typename V>(const auto&) {});
                pycppgen<void>("SDerived").for_each_var([]<typename V>() {});
            }
            """)

    def test_tagged_private_members_are_left_out(self) :
        self.project.write("Private.h", """
            #pragma once
            //$[[pycppgen]]
            class CPrivate
            {
            public:
                //$[[pycppgen]]
                int Public = 0;
                //$[[pycppgen]]
                void PublicFn() {}
            private:
                //$[[pycppgen]]
                int Hidden = 0;
                //$[[pycppgen]]
                void HiddenFn() {}
                //$[[pycppgen]]
                static void HiddenStatic() {}
            };
            """)
        self.project.run()
        gen = self.project.read("Private.gen.h")
        self.assertHasNot("Hidden", gen)
        self.assertHas("PublicFn", gen)
        self.compile("""
            #include "pycppgen.gen.h"
            bool Check(CPrivate* object) { return pycppgen<CPrivate>::call_function("PublicFn", object); }
            """)

if __name__ == "__main__" :
    unittest.main()
