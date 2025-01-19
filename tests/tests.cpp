
#include <cstdio>
#include <string_view>
#include <functional>
#include <typeinfo>

#include "enum.gen.h"
#include "class.gen.h"
#include "template.gen.h"

void main()
{
    meta<EEnum>::for_each_enum(
        [](EEnum v)
        {
            printf("EEnum::%s = %d\n", meta<EEnum>::enum_to_string(v).data(), (uint32_t)v);
        }
    );

    CObject o;

    meta<CObject>::for_each_var(
        [&](const member_variable_info& v)
        {
            printf("%s CObject::%s -> Offset: %llu Size: %llu\n", v.Type.data(), v.Name.data(), v.Offset, v.Size);
        }
    );

    meta<FVector>::for_each_var(
        [&](const member_variable_info& v)
        {
            printf("%s FVector::%s -> Offset: %llu Size: %llu\n", v.Type.data(), v.Name.data(), v.Offset, v.Size);
        }
    );
}