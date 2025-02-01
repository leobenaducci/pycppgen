#include "pycppgen.h"
#include "pycppgen.gen.h"

pycppgen<void>::pycppgen(std::string_view name)
{
	if (name == "TestNamespace::CNamespaceChild" || name == "CNamespaceChild")
		HashCode = typeid(TestNamespace::CNamespaceChild).hash_code();
	else if (name == "SStructTest" || name == "SStructTest")
		HashCode = typeid(SStructTest).hash_code();
	else if (name == "CObject::SSubObject" || name == "SSubObject")
		HashCode = typeid(CObject::SSubObject).hash_code();
	else if (name == "CObject" || name == "CObject")
		HashCode = typeid(CObject).hash_code();
	else if (name == "CChild" || name == "CChild")
		HashCode = typeid(CChild).hash_code();
}

static void for_each_type_static_call_by_name(std::string_view funcName) {
	pycppgen<CObject::SSubObject>::call_function(funcName);
	pycppgen<CObject>::call_function(funcName);
}

std::map<std::string, std::string> pycppgen<void>::get_var_attributes(std::string_view name) const
{
	if (false) {}
	else if (HashCode == typeid(TestNamespace::CNamespaceChild).hash_code())
		return pycppgen<TestNamespace::CNamespaceChild>::get_var_attributes(name);
	else if (HashCode == typeid(SStructTest).hash_code())
		return pycppgen<SStructTest>::get_var_attributes(name);
	else if (HashCode == typeid(CObject::SSubObject).hash_code())
		return pycppgen<CObject::SSubObject>::get_var_attributes(name);
	else if (HashCode == typeid(CObject).hash_code())
		return pycppgen<CObject>::get_var_attributes(name);
	else if (HashCode == typeid(CChild).hash_code())
		return pycppgen<CChild>::get_var_attributes(name);
	return {};
}

void pycppgen<void>::for_each_var(std::function<void(const member_variable_info&)> fn) const
{
	if (HashCode == typeid(TestNamespace::CNamespaceChild).hash_code())
		pycppgen<TestNamespace::CNamespaceChild>::for_each_var(fn);
	if (HashCode == typeid(SStructTest).hash_code())
		pycppgen<SStructTest>::for_each_var(fn);
	if (HashCode == typeid(CObject::SSubObject).hash_code())
		pycppgen<CObject::SSubObject>::for_each_var(fn);
	if (HashCode == typeid(CObject).hash_code())
		pycppgen<CObject>::for_each_var(fn);
	if (HashCode == typeid(CChild).hash_code())
		pycppgen<CChild>::for_each_var(fn);
}

