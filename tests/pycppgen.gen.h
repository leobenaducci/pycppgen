#pragma once

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
		fn(*(SVector*)0);
	}

	static void for_each_type_static_call_by_name(std::string_view funcName) {
		pycppgen<CObject>::call_function(funcName);
	}

}
