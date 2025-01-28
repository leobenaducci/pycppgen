#include "pycppgen.h"
#include "pycppgen.gen.h"

void pycppgen<void>::for_each_var(std::function<void(const member_variable_info&)> fn) const
{
	if (HashCode == typeid(CObject::SSubObject).hash_code())
		pycppgen<CObject::SSubObject>::for_each_var(fn);
	if (HashCode == typeid(CObject).hash_code())
		pycppgen<CObject>::for_each_var(fn);
	if (HashCode == typeid(CChild).hash_code())
		pycppgen<CChild>::for_each_var(fn);
	if (HashCode == typeid(SVector).hash_code())
		pycppgen<SVector>::for_each_var(fn);
}
