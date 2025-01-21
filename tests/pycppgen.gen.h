#pragma once

#include "C:\Leo\Python\pycppgen\tests\class.gen.h"
#include "C:\Leo\Python\pycppgen\tests\enum.gen.h"
#include "C:\Leo\Python\pycppgen\tests\function.gen.h"
#include "C:\Leo\Python\pycppgen\tests\namespace.gen.h"
#include "C:\Leo\Python\pycppgen\tests\struct.gen.h"
#include "C:\Leo\Python\pycppgen\tests\template.gen.h"

namespace pycppgen_globals {
	template<typename T> static void for_each_type_call(T fn) {
		fn<CObject::SSubObject>();
		fn<CObject>();
		fn<CChild>();
		fn<SVector>();
	}

	static void for_each_type_static_call_by_name(std::string_view funcName) {
		pycppgen<CObject::SSubObject>::call_function(funcName);
		pycppgen<CObject>::call_function(funcName);
		pycppgen<SVector>::call_function(funcName);
	}

}
