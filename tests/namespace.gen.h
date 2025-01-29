#pragma once

#include "pycppgen.h"
#include "namespace.h"

//<autogen__pycppgen_TestNamespace_CNamespaceChild>

#ifndef _pycppgen_TestNamespace_CNamespaceChild
#define _pycppgen_TestNamespace_CNamespaceChild

template<>
struct pycppgen<TestNamespace::CNamespaceChild> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string_view, std::string_view> Attributes = {

		};

	static void for_each_parent(auto fn) {
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		using namespace TestNamespace;
	}

	static void for_each_var_typed(auto fn) {
		using namespace TestNamespace;
	}

	static void for_each_var(TestNamespace::CNamespaceChild* obj, auto visitor) {
		using namespace TestNamespace;
	}

	static void for_each_var(const TestNamespace::CNamespaceChild* obj, auto visitor) {
		using namespace TestNamespace;
	}

	static std::map<std::string, std::string> get_member_attributes(std::string_view name) {
		using namespace TestNamespace;
		return {};
	}

	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}

	template<typename T> static T dump(const TestNamespace::CNamespaceChild* object) {
		T result;
		return result;
	}

	template<typename T, typename R> static bool parse(const T& data, R* object) {
		return true;
	}

	static void for_each_function(std::function<void(const member_function_info&)> fn) {
		using namespace TestNamespace;
	}

	static constexpr bool has_function(std::string_view name) {
		using namespace TestNamespace;
		return false;
	}

};

#endif //_pycppgen_TestNamespace_CNamespaceChild
//</autogen__pycppgen_TestNamespace_CNamespaceChild>

namespace pycppgen_globals {
//TestNamespace::Func1()
//TestNamespace::Func2(int)
//TestNamespace::Func3()
}
