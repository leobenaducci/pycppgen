
#include <cstdio>
#include <utility>

#include "chaiscript/chaiscript.hpp"
#include "chaiscript/utility/utility.hpp"

#include "class.gen.h"
#include "enum.gen.h"
#include "pycppgen.gen.h"

static void RegisterScriptingBindings(chaiscript::ChaiScript& chai)
{
    //chaiscript
    pycppgen_globals::for_each_type([&]<typename T>()
        {
            chai.add(chaiscript::user_type<T>(), pycppgen<T>::name());
            chai.add(chaiscript::constructor<T()>(), pycppgen<T>::name());
        });

    pycppgen_globals::for_each_enum([&]<typename T>()
        {
            const auto enumName = std::string(pycppgen<T>::name());

            auto m = std::make_shared<chaiscript::Module>();
    		chaiscript::utility::add_class(*m, enumName, std::vector<std::pair<T, std::string>>{});

            pycppgen<T>::for_each_enum_value(
                [&](auto v)
                {
                   m->add_global_const(chaiscript::const_var(T(v)), enumName + "__" + std::string(pycppgen<T>::enum_to_string(v)));
                });

            chai.add(chaiscript::type_conversion<T, std::underlying_type_t<T>>([](const T& v) { return static_cast<std::underlying_type_t<T>>(v); }));
            chai.add(chaiscript::type_conversion<T, int>([](const T& v) { return static_cast<int>(v); }));
            chai.add(chaiscript::type_conversion<T, std::string>([](const T& v) { return std::string(pycppgen<T>::enum_to_string(v)); }));

            chai.add(m);
        });

    pycppgen_globals::for_each_type([&]<typename T>()
        {
            pycppgen<T>::for_each_function([&]<typename R>()
                {
                    chai.add(chaiscript::fun(R::function_ptr()), R::name());
                }, 0);

            pycppgen<T>::for_each_var([&]<typename R>()
                {
                    chai.add(chaiscript::fun(R::variable_ptr()), R::name());
                }, 0);

            pycppgen<T>::for_each_static_var([&]<typename R>()
                {
                    std::string name = R::full_name();
                    std::ranges::replace(name, ':', '_');
                    chai.add_global(chaiscript::var(R::variable_ptr()), name);
                });
        });

    pycppgen_globals::for_each_type([&]<typename T>()
        {
            pycppgen<T>::for_each_parent([&]<typename R>()
                {
                    chai.add(chaiscript::base_class<R, T>());
                });
        });
}

int main()
{
    chaiscript::ChaiScript chai;

    SStructTest testStruct;
    testStruct.x = 75;
    testStruct.y = 0;
    testStruct.z = 100;

    RegisterScriptingBindings(chai);

    try
    {
        printf("------------ CHAISCRIPT ---------------------\n");

        chai.add(chaiscript::var(testStruct), "testStruct");
        auto o2 = chai.eval<CObject>(R"_chai_(
		    print("SStructBase__size = " + to_string(SStructBase__size));
		    print("testStruct.z = " + to_string(testStruct.z));
		    print("testStruct.components = " + to_string(testStruct.components));
		    var o2 = CObject();
		    print("o2.PublicShort = " + to_string(o2.PublicShort));
		    print("set o2.PublicShort to 1");
            o2.PublicShort = 1;
			print("EEnum__Test = " + to_string(EEnum__Test));
            return o2;
	    )_chai_");

        printf("o2.PublicShort = %d\n", o2.PublicShort);
    }
    catch (const std::exception& e)
    {
        printf("%s\n", e.what());
    }

    auto v = pycppgen<EEnum>::string_to_bitfield("Test| Value");
    v = (EEnum) ((std::underlying_type_t<EEnum>)v | (std::underlying_type_t<EEnum>)EEnum::Something);
    auto s = pycppgen<EEnum>::bitfield_to_string(v);

    printf("---------------------------------\n");

    pycppgen_globals::for_each_type([&]<typename T>()
        {
            pycppgen<T>::for_each_var([&]<typename R>()
                {
                    printf("%s\n", R::name());
                }, 0);

            pycppgen<T>::for_each_function([&]<typename R>()
                {
                    printf("%s\n", R::declaration());
                }, 0);
        });

    return 0;
}


