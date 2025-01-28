#pragma once


#include "pycppgen.h"
#include "class.gen.h"
#include "enum.gen.h"
#include "function.gen.h"
#include "namespace.gen.h"
#include "struct.gen.h"
#include "template.gen.h"

namespace pycppgen_globals
{
	static void for_each_type_call(auto fn) {
		fn(*(CObject::SSubObject*)0);
		fn(*(CObject*)0);
		fn(*(CChild*)0);
		fn(*(SStructTest*)0);
	}

	static void for_each_type_static_call_by_name(std::string_view funcName) {
		pycppgen<CObject::SSubObject>::call_function(funcName);
		pycppgen<CObject>::call_function(funcName);
	}
}

void pycppgen<void>::for_each_var(const void* obj, auto fn) const
{
	if (HashCode == typeid(CObject::SSubObject).hash_code())
		pycppgen<CObject::SSubObject>::for_each_var((const CObject::SSubObject*)obj, fn);
	if (HashCode == typeid(CObject).hash_code())
		pycppgen<CObject>::for_each_var((const CObject*)obj, fn);
	if (HashCode == typeid(CChild).hash_code())
		pycppgen<CChild>::for_each_var((const CChild*)obj, fn);
	if (HashCode == typeid(SStructTest).hash_code())
		pycppgen<SStructTest>::for_each_var((const SStructTest*)obj, fn);
}

void pycppgen<void>::for_each_var(void* obj, auto fn) const
{
	if (HashCode == typeid(CObject::SSubObject).hash_code())
		pycppgen<CObject::SSubObject>::for_each_var((CObject::SSubObject*)obj, fn);
	if (HashCode == typeid(CObject).hash_code())
		pycppgen<CObject>::for_each_var((CObject*)obj, fn);
	if (HashCode == typeid(CChild).hash_code())
		pycppgen<CChild>::for_each_var((CChild*)obj, fn);
	if (HashCode == typeid(SStructTest).hash_code())
		pycppgen<SStructTest>::for_each_var((SStructTest*)obj, fn);
}

template<typename T> static void pycppgen<void>::for_each_var(const T* obj, auto fn)
{
	if (obj == nullptr)
		return;

	const auto hashCode = typeid(*obj).hash_code();
	if (hashCode == typeid(CObject::SSubObject).hash_code())
		pycppgen<CObject::SSubObject>::for_each_var((const CObject::SSubObject*)obj, fn);
	if (hashCode == typeid(CObject).hash_code())
		pycppgen<CObject>::for_each_var((const CObject*)obj, fn);
	if (hashCode == typeid(CChild).hash_code())
		pycppgen<CChild>::for_each_var((const CChild*)obj, fn);
	if (hashCode == typeid(SStructTest).hash_code())
		pycppgen<SStructTest>::for_each_var((const SStructTest*)obj, fn);
}

template<typename T> static void pycppgen<void>::for_each_var(T* obj, auto fn)
{
	if (obj == nullptr)
		return;

	const auto hashCode = typeid(*obj).hash_code();
	if (hashCode == typeid(CObject::SSubObject).hash_code())
		pycppgen<CObject::SSubObject>::for_each_var((CObject::SSubObject*)obj, fn);
	if (hashCode == typeid(CObject).hash_code())
		pycppgen<CObject>::for_each_var((CObject*)obj, fn);
	if (hashCode == typeid(CChild).hash_code())
		pycppgen<CChild>::for_each_var((CChild*)obj, fn);
	if (hashCode == typeid(SStructTest).hash_code())
		pycppgen<SStructTest>::for_each_var((SStructTest*)obj, fn);
}

