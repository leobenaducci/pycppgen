
#include <cstdio>
#include <string_view>
#include <functional>
#include <typeinfo>
#include <map>
#include <string>

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

int main()
{
    //printf("%s\n", typeid(EEnum).name());
    //pycppgen<EEnum>::for_each_enum(
    //    [](EEnum v)
    //    {
    //        printf("\tEEnum::%s = %d\n", pycppgen<EEnum>::enum_to_string(v).data(), (uint32_t)v);
    //
    //        for (auto it : pycppgen<decltype(v)>::enum_value_attributes(v))
    //        {
    //            if(it.second.length() > 0)
    //                printf("\t\t%s = %s\n", it.first.c_str(), it.second.c_str());
    //            else
    //                printf("\t\t%s\n", it.first.c_str());
    //        }
    //    }
    //);
    //printf("---\n");
    //
    //pycppgen_globals::for_each_type_call([](const auto& t)
    //    {
    //        printf("%s ->\n", typeid(decltype(t)).name());
    //
    //        pycppgen_of(t).for_each_var(
    //            [&](const member_variable_info& v)
    //            {
    //                printf("\t%s %s -> Offset: %llu Size: %llu\n", v.Type.data(), v.FullName.data(), v.Offset, v.ElementSize);
    //            });
    //        printf("---\n");
    //    });
    //
    //

	CObject* o = new CChild();
    pycppgen<>::for_each_var(o, [&](const member_variable_info& v, auto&& t)
        {
            printf("%s = %s\n", v.FullName.data(), std::to_string(t).c_str());
        }
    );

    printf("---\n");

    float rf;
    pycppgen<CObject>::call_function("Add", o, rf, 1.f, 2.f);
    printf("Add(1.f, 2.f) = %.2f\n", rf);

    const CObject co;
    short rs;
    pycppgen<CObject>::call_function("Get", &co, rs);
    printf("Get() = %d\n", rs);

    pycppgen<>("SStructTest").for_each_var([&](const member_variable_info& v)
        {
            printf("%s\n", v.FullName.data());
        });


    return 0;
}
