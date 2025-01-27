#pragma once

#include "pycppgen.h"
#include "template.h"

//<autogen_pycppgen_Template_TVector_T_>

#ifndef pycppgen_Template_TVector_T_
#define pycppgen_Template_TVector_T_

template<typename T>
struct pycppgen<Template::TVector<T>> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string_view, std::string_view> Attributes = {

	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
	}
	static void for_each_var(* obj, auto visitor) {
	}
	static std::map<std::string, std::string> get_member_attributes(std::string_view name) {
		return {};
	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	template<typename T> static T dump(const * object) {
		T result;
		return result;
	}
	template<typename T, typename R> static bool parse(const T& data, R* object) {
		return true;
	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
	}
	static constexpr bool has_function(std::string_view name) {
		return false;
	}
};

#endif //pycppgen_Template_TVector_T_
//</autogen_pycppgen_Template_TVector_T_>

namespace pycppgen_globals {
}
