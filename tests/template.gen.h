#pragma once

#include "template.h"

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

//<autogen_pycppgen_Template_TVector_T_>

#ifndef pycppgen_Template_TVector_T_
#define pycppgen_Template_TVector_T_

template<typename T>
struct pycppgen<Template::TVector<T>>{
	std::map<std::string_view, std::string_view> Attributes = {

	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		struct access_helper : Template::TVector<T> {
			const size_t x_Offset = offsetof(access_helper, Template::TVector<T>::x);
			const size_t y_Offset = offsetof(access_helper, Template::TVector<T>::y);
			const size_t z_Offset = offsetof(access_helper, Template::TVector<T>::z);
		};
		member_variable_info x_info_56;
		x_info_56.Name = "x";
		x_info_56.Type = typeid(T).name();
		x_info_56.Offset = access_helper().x_Offset;
		x_info_56.ElementSize = sizeof(std::remove_all_extents_t<T>);
		x_info_56.TotalSize = sizeof(T);
		x_info_56.ArrayRank = std::rank_v<T>;
		x_info_56.Attributes = {

		};
		fn(x_info_56);

		member_variable_info y_info_68;
		y_info_68.Name = "y";
		y_info_68.Type = typeid(T).name();
		y_info_68.Offset = access_helper().y_Offset;
		y_info_68.ElementSize = sizeof(std::remove_all_extents_t<T>);
		y_info_68.TotalSize = sizeof(T);
		y_info_68.ArrayRank = std::rank_v<T>;
		y_info_68.Attributes = {

		};
		fn(y_info_68);

		member_variable_info z_info_80;
		z_info_80.Name = "z";
		z_info_80.Type = typeid(T).name();
		z_info_80.Offset = access_helper().z_Offset;
		z_info_80.ElementSize = sizeof(std::remove_all_extents_t<T>);
		z_info_80.TotalSize = sizeof(T);
		z_info_80.ArrayRank = std::rank_v<T>;
		z_info_80.Attributes = {

		};
		fn(z_info_80);

	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
	}
};

#endif //pycppgen_Template_TVector_T_
//</autogen_pycppgen_Template_TVector_T_>

namespace pycppgen_globals {
}
