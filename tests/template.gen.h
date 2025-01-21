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

#endif //_PYCPPGEN_DECLARATIONS

#ifndef pycppgen_Template_TVector_T_
#define pycppgen_Template_TVector_T_

template<typename T, >
struct pycppgen<Template::TVector<T>>{
	static std::map<std::string_view, std::string_view> Attributes = {

	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		struct access_helper : Template::TVector<T> {
			const size_t x_Offset = offsetof(access_helper, Template::TVector<T>::x);
			const size_t y_Offset = offsetof(access_helper, Template::TVector<T>::y);
			const size_t z_Offset = offsetof(access_helper, Template::TVector<T>::z);
		};
		member_variable_info x_info_52;
		x_info_52.Name = "x";
		x_info_52.Type = typeid(T).name();
		x_info_52.Offset = access_helper().x_Offset;
		x_info_52.ElementSize = sizeof(std::remove_all_extents_t<T>);
		x_info_52.TotalSize = sizeof(T);
		x_info_52.ArrayRank = std::rank_v<T>;
		x_info_52.Attributes = {

		};
		fn(x_info_52);

		member_variable_info y_info_64;
		y_info_64.Name = "y";
		y_info_64.Type = typeid(T).name();
		y_info_64.Offset = access_helper().y_Offset;
		y_info_64.ElementSize = sizeof(std::remove_all_extents_t<T>);
		y_info_64.TotalSize = sizeof(T);
		y_info_64.ArrayRank = std::rank_v<T>;
		y_info_64.Attributes = {

		};
		fn(y_info_64);

		member_variable_info z_info_76;
		z_info_76.Name = "z";
		z_info_76.Type = typeid(T).name();
		z_info_76.Offset = access_helper().z_Offset;
		z_info_76.ElementSize = sizeof(std::remove_all_extents_t<T>);
		z_info_76.TotalSize = sizeof(T);
		z_info_76.ArrayRank = std::rank_v<T>;
		z_info_76.Attributes = {

		};
		fn(z_info_76);

	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
		member_function_info operator[]_info_90;
		operator[]_info_90.Name = "operator[]";
		operator[]_info_90.Declaration = "const T &(int) const";
		operator[]_info_90.Attributes = {};
		operator[]_info_90.ReturnType = "const T &";
		//parameters
		{
			function_parameter_info i_info_97;
			i_info_97.Name = "i";
			i_info_97.Type = "int";
			i_info_97.DefaultValue = "";
			i_info_97.Attributes = {};
			operator[]_info_90.Parameters.push_back(i_info_97);
		}
	}
	static void call_function(std::string_view name, const * object, const T && result, int _1) {
		if (name == "operator[]") {
			result = object->operator[]( _1);
			return;
		}
		__debugbreak();
	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	}
};

#endif //pycppgen_Template_TVector_T_
namespace pycppgen_globals {
}
