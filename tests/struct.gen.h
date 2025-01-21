#pragma once

#include "struct.h"

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

//<autogen_pycppgen_SVector>

#ifndef pycppgen_SVector
#define pycppgen_SVector

template<>
struct pycppgen<SVector>{
	static std::map<std::string_view, std::string_view> Attributes = {
		{ "visible", "" }
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		struct access_helper : SVector {
			const size_t x_Offset = offsetof(access_helper, SVector::x);
			const size_t y_Offset = offsetof(access_helper, SVector::y);
			const size_t z_Offset = offsetof(access_helper, SVector::z);
		};
		member_variable_info x_info_54;
		x_info_54.Name = "x";
		x_info_54.Type = typeid(float).name();
		x_info_54.Offset = access_helper().x_Offset;
		x_info_54.ElementSize = sizeof(std::remove_all_extents_t<float>);
		x_info_54.TotalSize = sizeof(float);
		x_info_54.ArrayRank = std::rank_v<float>;
		x_info_54.Attributes = {
			{ "visible", "" }
		};
		fn(x_info_54);

		member_variable_info y_info_66;
		y_info_66.Name = "y";
		y_info_66.Type = typeid(float).name();
		y_info_66.Offset = access_helper().y_Offset;
		y_info_66.ElementSize = sizeof(std::remove_all_extents_t<float>);
		y_info_66.TotalSize = sizeof(float);
		y_info_66.ArrayRank = std::rank_v<float>;
		y_info_66.Attributes = {
			{ "visible", "" }
		};
		fn(y_info_66);

		member_variable_info z_info_78;
		z_info_78.Name = "z";
		z_info_78.Type = typeid(float).name();
		z_info_78.Offset = access_helper().z_Offset;
		z_info_78.ElementSize = sizeof(std::remove_all_extents_t<float>);
		z_info_78.TotalSize = sizeof(float);
		z_info_78.ArrayRank = std::rank_v<float>;
		z_info_78.Attributes = {
			{ "visible", "" }
		};
		fn(z_info_78);

	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
		fn("size");
	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
	}
	static bool call_function(std::string_view name) {
		if (name == "OnRegister") {
			SVector::OnRegister();
			return true;
		}
		return false;
	}
};

#endif //pycppgen_SVector
//</autogen_pycppgen_SVector>

namespace pycppgen_globals {
}
