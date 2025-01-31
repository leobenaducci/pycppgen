#include "pycppgen.h"
#include "pycppgen.gen.h"

void pycppgen<void>::for_each_var(std::function<void(const member_variable_info&)> fn) const
{
	if (HashCode == typeid(CObject::SSubObject).hash_code())
		pycppgen<CObject::SSubObject>::for_each_var(fn);
	if (HashCode == typeid(CObject).hash_code())
		pycppgen<CObject>::for_each_var(fn);
	if (HashCode == typeid(TestNamespace::CNamespaceChild).hash_code())
		pycppgen<TestNamespace::CNamespaceChild>::for_each_var(fn);
	if (HashCode == typeid(SStructTest).hash_code())
		pycppgen<SStructTest>::for_each_var(fn);
}

pycppgen<void>::pycppgen(std::string_view name)
{
	if (name == "CObject::SSubObject" || name == "SSubObject")
		HashCode = typeid(CObject::SSubObject).hash_code();
	else if (name == "CObject" || name == "CObject")
		HashCode = typeid(CObject).hash_code();
	else if (name == "TestNamespace::CNamespaceChild" || name == "CNamespaceChild")
		HashCode = typeid(TestNamespace::CNamespaceChild).hash_code();
	else if (name == "SStructTest" || name == "SStructTest")
		HashCode = typeid(SStructTest).hash_code();
}

