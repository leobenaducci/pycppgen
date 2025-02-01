#pragma once

#include "pycppgen.h"
#include "template.h"

//<autogen__pycppgen_Template_TVector_T_>

#ifndef _pycppgen_Template_TVector_T_
#define _pycppgen_Template_TVector_T_

template<typename T>
struct pycppgen<Template::TVector<T>> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string_view, std::string_view> Attributes = {

		};

	static void for_each_parent(auto fn) {
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		using namespace Template;
	}

	static void for_each_var_typed(auto fn) {
		using namespace Template;
	}

	static void for_each_var(Template::TVector<T>* obj, auto visitor) {
		using namespace Template;
	}

	static void for_each_var(const Template::TVector<T>* obj, auto visitor) {
		using namespace Template;
	}

	static std::map<std::string, std::string> get_member_attributes(std::string_view name) {
		using namespace Template;
		return {};
	}

	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}

	template<typename T> static bool dump(T& result, const Template::TVector<T>* object) {
		return true;
	}

	template<typename T, typename R> static bool parse(const T& data, R* object) {
		return true;
	}

	static void for_each_function(auto fn) {
		using namespace Template;
	}

	static auto get_function_by_name(std::string_view name) {
		member_function_info<void> result = {};
		for_each_function([&](const auto& fn) {
			if (fn.Name == name) result = fn; 
		});
		return result;
	}

	static constexpr bool has_function(std::string_view name) {
		using namespace Template;
		return false;
	}

};

#endif //_pycppgen_Template_TVector_T_
//</autogen__pycppgen_Template_TVector_T_>

namespace pycppgen_globals {
}
