#pragma once


#include "pycppgen.h"
#include "namespace.gen.h"
#include "function.gen.h"
#include "struct.gen.h"
#include "template.gen.h"
#include "enum.gen.h"
#include "class.gen.h"

namespace pycppgen_globals
{
	static void for_each_type_call(auto fn) {
		struct type_TestNamespace_CNamespaceChild { using type = TestNamespace::CNamespaceChild; const type* obj = nullptr; };
		fn(type_TestNamespace_CNamespaceChild());
		struct type_SStructTest { using type = SStructTest; const type* obj = nullptr; };
		fn(type_SStructTest());
		struct type_CObject_SSubObject { using type = CObject::SSubObject; const type* obj = nullptr; };
		fn(type_CObject_SSubObject());
		struct type_CObject { using type = CObject; const type* obj = nullptr; };
		fn(type_CObject());
		struct type_CChild { using type = CChild; const type* obj = nullptr; };
		fn(type_CChild());
	}

	static void for_each_enum_call(auto fn)
	{
		fn(EEnum());
		fn(EAnotherEnum());
	}

}

template<typename T> void pycppgen<void>::for_each_var(const T* obj, auto fn)
{
	const auto hashCode = obj ? typeid(*obj).hash_code() : 0;
	if (false) {}
	else if (hashCode == typeid(TestNamespace::CNamespaceChild).hash_code())
		pycppgen<TestNamespace::CNamespaceChild>::for_each_var((const TestNamespace::CNamespaceChild*)obj, fn);
	else if (hashCode == typeid(SStructTest).hash_code())
		pycppgen<SStructTest>::for_each_var((const SStructTest*)obj, fn);
	else if (hashCode == typeid(CObject::SSubObject).hash_code())
		pycppgen<CObject::SSubObject>::for_each_var((const CObject::SSubObject*)obj, fn);
	else if (hashCode == typeid(CObject).hash_code())
		pycppgen<CObject>::for_each_var((const CObject*)obj, fn);
	else if (hashCode == typeid(CChild).hash_code())
		pycppgen<CChild>::for_each_var((const CChild*)obj, fn);
}

template<typename T> void pycppgen<void>::for_each_var(T* obj, auto fn)
{
	const auto hashCode = obj ? typeid(*obj).hash_code() : 0;
	if (false) {}
	else if (hashCode == typeid(TestNamespace::CNamespaceChild).hash_code())
		pycppgen<TestNamespace::CNamespaceChild>::for_each_var((TestNamespace::CNamespaceChild*)obj, fn);
	else if (hashCode == typeid(SStructTest).hash_code())
		pycppgen<SStructTest>::for_each_var((SStructTest*)obj, fn);
	else if (hashCode == typeid(CObject::SSubObject).hash_code())
		pycppgen<CObject::SSubObject>::for_each_var((CObject::SSubObject*)obj, fn);
	else if (hashCode == typeid(CObject).hash_code())
		pycppgen<CObject>::for_each_var((CObject*)obj, fn);
	else if (hashCode == typeid(CChild).hash_code())
		pycppgen<CChild>::for_each_var((CChild*)obj, fn);
}

template<typename T, typename R> bool pycppgen<void>::dump(T& result, const R* obj)
{
	const auto hashCode = obj ? typeid(*obj).hash_code() : 0;
	if (false) {}
	else if (hashCode == typeid(CObject).hash_code())
		return pycppgen<CObject>::dump(result, (const CObject*)obj);
	else if (hashCode == typeid(CChild).hash_code())
		return pycppgen<CChild>::dump(result, (const CChild*)obj);
	return false;
}

template<typename T, typename R> bool pycppgen<void>::parse(const T& data, R* obj)
{
	const auto hashCode = obj ? typeid(*obj).hash_code() : 0;
	if (false) {}
	else if (hashCode == typeid(CObject).hash_code())
		return pycppgen<CObject>::parse(data, (const CObject*)obj);
	else if (hashCode == typeid(CChild).hash_code())
		return pycppgen<CChild>::parse(data, (const CChild*)obj);
	return false;
}

