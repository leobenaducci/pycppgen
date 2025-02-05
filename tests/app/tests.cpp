
#include <cstdio>
#include <string_view>
#include <functional>
#include <typeinfo>
#include <map>
#include <string>

#include "chaiscript/chaiscript.hpp"

#include "class.gen.h"
#include "enum.gen.h"
#include "pycppgen.gen.h"

void CChild::DoSomething() {}

namespace std
{
    template<typename T, size_t N>
    std::string to_string(const std::array<T, N>& arr)
    {
        std::string str;
        str.reserve(N * 3 + 3);

        str += '[';
        
        for (const auto& it : arr)
            str += std::to_string(it) + ", ";

        if (arr.size() > 0)
            str.resize(str.length() - 2);

        str += ']';

        return str;
    }
}

//sample serializer
struct serializer_value_t
{
    std::string value;

    template<typename T>
    serializer_value_t& operator=(const T& a) { value = std::to_string(a); return *this; }

    template<std::integral T> operator T () const { return std::atoi(value.c_str()); }
    template<std::floating_point T> operator T () const { return std::atof(value.c_str()); }
    operator std::string () const { return value; }
    template<typename T, size_t N> operator std::array<T, N> () const { return std::array<T, N>(); }
};

struct serializer_t
{
    serializer_value_t operator[](std::string key) const 
    {
        auto it = data.find(key); 
        return it != data.end() ? it->second : serializer_value_t{}; 
    }

    serializer_value_t& operator[](std::string key)
    {
        return data[key];
    }

    std::map<std::string, serializer_value_t> data;
};

static void RegisterChaiScriptTypes(chaiscript::ChaiScript& chai)
{
    pycppgen_globals::for_each_type_call([&](auto param)
        {
            using T = decltype(param)::type;

            chai.add(chaiscript::user_type<T>(), pycppgen<T>::name());
            chai.add(chaiscript::constructor<T()>(), pycppgen<T>::name());

            pycppgen<T>::for_each_parent([&](auto parent)
                {
                    using parent_t = decltype(param)::type;
                    chai.add(chaiscript::base_class<parent_t, T>());
                });

            pycppgen<T>::for_each_var([&](auto var)
                {
                    chai.add(chaiscript::fun(var.MemberVar), var.Name);
                }, 0);
        });
}

int main()
{
    chaiscript::ChaiScript chai;
    RegisterChaiScriptTypes(chai);

    SStructTest testStruct;
    testStruct.x = 0;
    testStruct.y = 0;
    testStruct.z = 100;

    chai.add(chaiscript::var(testStruct), "testStruct");
    auto o2 = chai.eval<CObject>(R"_(
		print("testStruct.z = " + to_string(testStruct.z));
		var o2 = CObject();
		print("o2.PublicShort = " + to_string(o2.PublicShort));
        o2.PublicShort = 1;
        return o2;
	)_");

    printf("o2.PublicShort = %d\n", o2.PublicShort);

    printf("-> pycppgen_globals::for_each_enum_call([](auto&& e)\n");
    pycppgen_globals::for_each_enum_call([](auto e)
        {
            printf("\t%s:\n", typeid(e).name());
            pycppgen_of(e).for_each_enum_value([e](auto v)
                {
                    printf("\t\t*%s = %d\n", pycppgen_of(e).enum_to_string(v).data(), (uint32_t)v);
                });
        });

    printf("---\n");
    
    printf("-> pycppgen_globals::for_each_type_call([](auto&& e)\n");
    pycppgen_globals::for_each_type_call([](auto param)
        {
            printf("\t*%s\n", typeid(decltype(param)::type).name());
            
            pycppgen<decltype(param)::type>::for_each_var(
                [&](const auto& v)
                {
                    printf("\t\t%s %s -> Offset: %llu Size: %llu", v.Type.data(), v.FullName.data(), v.Offset, v.TotalSize);
                    if (v.ArrayRank > 0)
                    {
                        printf(" Array decl: ");
                        for (auto i : v.ArrayExtents)
                        {
                            printf("[%llu]", i);
                        }
                    }
                    printf("\n");
                });
        });
    
	CObject* o = new CChild();

    printf("-> CObject* o = new CChild(); pycppgen<>::for_each_var(o, [](const member_variable_info& v, auto&& t)\n");
    pycppgen<>::for_each_var(o, [o](const auto& v, auto&& t)
        {
            auto attribs = pycppgen_of(o).get_var_attributes(v.Name);
            printf("\t%s = %s\n", v.FullName.data(), std::to_string(t).c_str());
        }
    );

    printf("---\n");

    float rf;
    printf("-> pycppgen<CObject>::call_function(\"Add\", o, rf, 1.f, 2.f)\n");
    pycppgen<CObject>::call_function("Add", o, rf, 1.f, 2.f);
    printf("\tAdd(1.f, 2.f) = %.2f\n", rf);

    const CObject co;
    short rs;
    printf("-> const CObject co; pycppgen<CObject>::call_function(\"Get\", &co, rs)\n");
    pycppgen<CObject>::call_function("Get", &co, rs);
    printf("\tGet() = %d\n", rs);

    printf("---\n");

    printf("-> pycppgen<>(\"SStructTest\").for_each_var([](const member_variable_info& v)\n");
    pycppgen<>("SStructTest").for_each_var([](const auto& v)
        {
            printf("\t%s\n", v.FullName.data());
        });

    printf("---\n");

    //dump/parse
    serializer_t data{};
    pycppgen<>::dump(data, o);

    {
        CChild dst;
        dst.PublicShort = 0;
        ((pycppgen<CObject>::access_helper*) & dst)->SetProtectedUint(0);

        pycppgen<>::parse(data, &dst);
    }

    pycppgen<CObject>::find_function_by_name("Get", [](auto fn)
        {
            printf("CObject::Get -> %s\n", typeid(fn.Function).name());
        });

    pycppgen<CChild>::find_function_by_name("Add", [](auto fn)
        {
            printf("CChild::Add -> %s\n", typeid(fn.Function).name());
        });

    return 0;
}
