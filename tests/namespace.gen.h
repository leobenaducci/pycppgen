#pragma once

#include "namespace.h"

#ifndef _PYCPPGEN_DECLARATIONS
#define _PYCPPGEN_DECLARATIONS

struct member_variable_info {
	std::string_view Name;
	std::string_view Type;
	size_t Offset = 0;
	size_t ElementSize = 0;
	size_t TotalSize = 0;
	size_t ArrayRank = 0;
	std::vector<size_t> ArrayExtents;
	std::map<std::string, std::string> Attributes;
};

struct function_parameter_info {
	std::string_view Name;
	std::string_view Type;
	std::string_view DefaultValue;
	std::map<std::string, std::string> Attributes;
};

struct member_function_info {
	std::string_view Name;
	std::string_view Declaration;
	std::string_view ReturnType;
	std::vector<function_parameter_info> Parameters;
	std::map<std::string, std::string> Attributes;
};

template<typename T> struct pycppgen {};

template<typename T> auto pycppgen_typeof(T&& t) { return pycppgen<std::decay_t<decltype(t)>>(); }

#endif //_PYCPPGEN_DECLARATIONS

//<autogen_pycppgen_CObject_SSubObject>

#ifndef pycppgen_CObject_SSubObject
#define pycppgen_CObject_SSubObject

template<>
struct pycppgen<CObject::SSubObject>{
	std::map<std::string_view, std::string_view> Attributes = {

	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
	}
	static bool call_function(std::string_view name) {
		if (name == "OnRegister") {
			CObject::SSubObject::OnRegister();
			return true;
		}
		return false;
	}
};

#endif //pycppgen_CObject_SSubObject
//</autogen_pycppgen_CObject_SSubObject>

namespace pycppgen_globals {
//TestNameSpace::FuncA()
//TestNameSpace::FuncB(int)
//TestNameSpace::FuncC()
//int TestNameSpace::GlobalInt
}
