
#include <cstdio>
#include <utility>

#include "chaiscript/chaiscript.hpp"
#include "pybind11/pybind11.h"

#include "class.gen.h"
#include "enum.gen.h"
#include "pycppgen.gen.h"

namespace py = pybind11;

static void RegisterScriptingBindings(chaiscript::ChaiScript& chai, auto pyModule)
{
    //chaiscript
    pycppgen_globals::for_each_type([&](auto param)
        {
            using T = decltype(param)::type;

            chai.add(chaiscript::user_type<T>(), pycppgen<T>::name());
            chai.add(chaiscript::constructor<T()>(), pycppgen<T>::name());
        });

    pycppgen_globals::for_each_type([&](auto param)
        {
            using T = decltype(param)::type;

            pycppgen<T>::for_each_function([&](auto fn)
                {
                    chai.add(chaiscript::fun(fn.FunctionPtr), fn.name());
                }, 0);

            pycppgen<T>::for_each_var([&](auto var)
                {
                    chai.add(chaiscript::fun(var.VariablePtr), var.name());
                }, 0);

            pycppgen<T>::for_each_static_var([&](auto var)
                {
                    std::string name = var.full_name();
                    std::ranges::replace(name, ':', '_');
                    chai.add_global(chaiscript::var(var.VariablePtr), name);
                });
        });

    pycppgen_globals::for_each_type([&](auto param)
        {
            using T = decltype(param)::type;

            pycppgen<T>::for_each_parent([&](auto parent)
                {
                    using parent_t = decltype(parent)::type;
                    chai.add(chaiscript::base_class<parent_t, T>());
                });
        });
}

PYBIND11_EMBEDDED_MODULE(tests, m)
{
    //pocketpy
	pycppgen_globals::for_each_type([&](auto param)
		{
			using T = decltype(param)::type;

			bool parentRegistered = false;
			pycppgen<T>::for_each_parent([&](auto parent)
				{
					if (parentRegistered)
						return;

					parentRegistered = true;

					using parent_t = decltype(parent)::type;

					auto& pyClass = py::class_<T, parent_t>(m, pycppgen<T>::name())
						.def(py::init<>())
                        .def(py::init<const T&>());

					pycppgen<T>::for_each_var([&](auto var)
						{
							if (var.is_const())
								pyClass.def_readonly(var.name(), var.VariablePtr);
							else
								pyClass.def_readwrite(var.name(), var.VariablePtr);
						}, 0);

					pycppgen<T>::for_each_function([&](auto fn)
						{
							pyClass.def(fn.name(), fn.FunctionPtr);
						}, 0);
				}, 1);

			if (!parentRegistered)
			{
				auto& pyClass = py::class_<T>(m, pycppgen<T>::name())
					.def(py::init<>());

				pycppgen<T>::for_each_var([&](auto var)
					{
						if (var.is_const())
							pyClass.def_readonly(var.name(), var.VariablePtr);
						else
							pyClass.def_readwrite(var.name(), var.VariablePtr);
					}, 0);

				pycppgen<T>::for_each_function([&](auto fn)
					{
						pyClass.def(fn.name(), fn.FunctionPtr);
					}, 0);
			}
		});
}

int main()
{
    chaiscript::ChaiScript chai;
    py::scoped_interpreter guard{};

    SStructTest testStruct;
    testStruct.x = 75;
    testStruct.y = 0;
    testStruct.z = 100;

    RegisterScriptingBindings(chai, py::module_::__main__());

	{
		printf("------------ PYTHON ---------------------\n");
		auto globals = py::dict();

		auto tests = py::module::import("tests");
		globals["testStruct"] = py::cast(&testStruct);
		py::exec(
			"import tests\n"
			"testStruct.z = 23\n"
			"print('testStruct.z = ' + str(testStruct.z))\n"
			"o2 = tests.CObject()\n"
			"print('o2.PublicShort = ' + str(o2.PublicShort))\n"
			"print('set o2.PublicShort to 2')\n"
			"o2.PublicShort = 2\n"
			, globals);

		auto o2 = py::eval("o2", globals).cast<CObject>();
		printf("o2.PublicShort = %d\n", o2.PublicShort);

		printf("---------------------------------\n");
	}

    try
    {
        printf("------------ CHAISCRIPT ---------------------\n");

        chai.add(chaiscript::var(testStruct), "testStruct");
        auto o2 = chai.eval<CObject>(R"_(
		    print("SStructBase__size = " + to_string(SStructBase__size));
		    print("testStruct.z = " + to_string(testStruct.z));
		    print("testStruct.components = " + to_string(testStruct.components));
		    var o2 = CObject();
		    print("o2.PublicShort = " + to_string(o2.PublicShort));
		    print("set o2.PublicShort to 1");
            o2.PublicShort = 1;
            return o2;
	    )_");

        printf("o2.PublicShort = %d\n", o2.PublicShort);
    }
    catch (std::exception e)
    {
        printf(e.what());
    }

    printf("---------------------------------\n");

    pycppgen_globals::for_each_type([&](auto param)
        {
            using T = decltype(param)::type;

            pycppgen<T>::for_each_var([&](auto var)
                {
                    printf("%s\n", decltype(var)::name());
                }, 0);

            pycppgen<T>::for_each_function([&](auto fun)
                {
                    printf("%s\n", decltype(fun)::declaration());
                }, 0);
        });

    return 0;
}


