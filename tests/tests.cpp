
#include <cstdio>
#include <string_view>
#include <functional>
#include <typeinfo>

#include "enum.gen.h"
#include "class.gen.h"
#include "template.gen.h"

int main()
{
	meta<EEnum>::for_each_enum(
          [](EEnum v)
          {
              printf("EEnum::%s = %d\n", meta<EEnum>::enum_to_string(v).data(), (uint32_t)v);
          }
      );
    
	meta<CObject>::for_each_var(
          [&](const member_variable_info& v)
          {
              printf("%s CObject::%s -> Offset: %llu Size: %llu\n", v.Type.data(), v.Name.data(), v.Offset, v.ElementSize);
          }
      );
    
    meta<FVector>::for_each_var(
          [&](const member_variable_info& v)
          {
              printf("%s FVector::%s -> Offset: %llu Size: %llu\n", v.Type.data(), v.Name.data(), v.Offset, v.ElementSize);
          }
      );

	CObject o;
    float rf;
    meta<CObject>::call_function("Add", &o, rf, 1.f, 2.f);

    const CObject co {};
    short rs;
    meta<CObject>::call_function("Get", &co, rs);

    return 0;
}
