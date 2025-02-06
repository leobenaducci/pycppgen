
#include <cstdio>
#include <utility>

#include "chaiscript/chaiscript.hpp"
#include "pybind11/pybind11.h"
#include "pocketpy.h"

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
                    chai.add(chaiscript::fun(fn.Function), fn.Name);
                }, 0);

            pycppgen<T>::for_each_var([&](auto var)
                {
                    chai.add(chaiscript::fun(var.MemberVar), var.Name);
                }, 0);

            pycppgen<T>::for_each_static_var([&](auto var)
                {
                    std::string name = var.FullName;
                    std::ranges::replace(name, ':', '_');
                    chai.add_global(chaiscript::var(var.StaticMemberVar), name);
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

					auto& pyClass = py::class_<T, parent_t>(pyModule, pycppgen<T>::name())
						.def(py::init<>());

					pycppgen<T>::for_each_var([&](auto var)
						{
							if (var.is_const)
								pyClass.def_readonly(var.Name.data(), var.MemberVar);
							else
								pyClass.def_readwrite(var.Name.data(), var.MemberVar);
						}, 0);

					pycppgen<T>::for_each_function([&](auto fn)
						{
							pyClass.def((const char*)fn.Name.data(), fn.Function);
						}, 0);
				}, 1);

			if (!parentRegistered)
			{
				auto& pyClass = py::class_<T>(pyModule, pycppgen<T>::name())
					.def(py::init<>());

				pycppgen<T>::for_each_var([&](auto var)
					{
						if (var.is_const)
							pyClass.def_readonly(var.Name.data(), var.MemberVar);
						else
							pyClass.def_readwrite(var.Name.data(), var.MemberVar);
					}, 0);

				pycppgen<T>::for_each_function([&](auto fn)
					{
						pyClass.def((const char*)fn.Name.data(), fn.Function);
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
        CObject o2;

        printf("------------ PYTHON ---------------------\n");
        auto globals = py::dict();
        globals["testStruct"] = py::cast(testStruct);
        globals["o2"] = py::cast(o2);
        py::exec(
            "print('testStruct.z = ' + str(testStruct.z))\n"
            "print('o2.PublicShort = ' + str(o2.PublicShort))\n"
            "o2.PublicShort = 1\n"
            , globals);

        o2 = globals["o2"].cast<CObject>();
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

    return 0;
}


