
#include <cstdio>

#include "chaiscript/chaiscript.hpp"

#include "class.gen.h"
#include "enum.gen.h"
#include "pycppgen.gen.h"

static void RegisterChaiScriptTypes(chaiscript::ChaiScript& chai)
{
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
                    chai.add(chaiscript::exception::global_non_const(var.StaticMemberVar), var.FullName);
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

int main()
{
    //member_function_info<decltype(&pycppgen<SStructTest>::access_helper::size)> info;
    //info.Function;

    decltype(&SStructTest::size) A;

    chaiscript::ChaiScript chai;
    RegisterChaiScriptTypes(chai);

    
    SStructTest testStruct;
    testStruct.x = 0;
    testStruct.y = 0;
    testStruct.z = 100;

    try
    {
        chai.add(chaiscript::var(testStruct), "testStruct");
        auto o2 = chai.eval<CObject>(R"_(
		    print("testStruct::size = " + to_string(testStruct::size));
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

    return 0;
}
