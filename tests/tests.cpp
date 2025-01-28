
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

int main()
{
    pycppgen_globals::for_each_type_call([](const auto& t)
        {
            pycppgen_of(t).for_each_var(
                [&](const member_variable_info& v)
                {
                    printf("%s CObject::%s -> Offset: %llu Size: %llu\n", v.Type.data(), v.Name.data(), v.Offset, v.ElementSize);
                });
        });
    
	pycppgen<EEnum>::for_each_enum(
          [](EEnum v)
          {
              printf("EEnum::%s = %d\n", pycppgen<EEnum>::enum_to_string(v).data(), (uint32_t)v);
    
              for (auto it : pycppgen<decltype(v)>::enum_value_attributes(v))
              {
                  if(it.second.length() > 0)
                      printf("\t%s = %s\n", it.first.c_str(), it.second.c_str());
                  else
                      printf("\t%s\n", it.first.c_str());
              }
          }
      );
    
	CObject* o = new CChild();

    float rf;
    pycppgen<CObject>::call_function("Add", o, rf, 1.f, 2.f);

    pycppgen_of(o).for_each_var([&](const member_variable_info& v)
        {
            printf("%s %s::%s -> Offset: %llu Size: %llu\n", v.Type.data(), typeid(*o).name(), v.Name.data(), v.Offset, v.ElementSize);
        }
    );

    const CObject co {};
    short rs;
    //pycppgen<CObject>::call_function("Get", &co, rs);
    
    return 0;
}
