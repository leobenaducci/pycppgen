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
		member_variable_info x_info_52;
		x_info_52.Name = "x";
		x_info_52.Type = typeid(float).name();
		x_info_52.Offset = access_helper().x_Offset;
		x_info_52.ElementSize = sizeof(std::remove_all_extents_t<float>);
		x_info_52.TotalSize = sizeof(float);
		x_info_52.ArrayRank = std::rank_v<float>;
		x_info_52.Attributes = {
			{ "visible", "" }
		};
		fn(x_info_52);

		member_variable_info y_info_64;
		y_info_64.Name = "y";
		y_info_64.Type = typeid(float).name();
		y_info_64.Offset = access_helper().y_Offset;
		y_info_64.ElementSize = sizeof(std::remove_all_extents_t<float>);
		y_info_64.TotalSize = sizeof(float);
		y_info_64.ArrayRank = std::rank_v<float>;
		y_info_64.Attributes = {
			{ "visible", "" }
		};
		fn(y_info_64);

		member_variable_info z_info_76;
		z_info_76.Name = "z";
		z_info_76.Type = typeid(float).name();
		z_info_76.Offset = access_helper().z_Offset;
		z_info_76.ElementSize = sizeof(std::remove_all_extents_t<float>);
		z_info_76.TotalSize = sizeof(float);
		z_info_76.ArrayRank = std::rank_v<float>;
		z_info_76.Attributes = {
			{ "visible", "" }
		};
		fn(z_info_76);

	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
		fn("size");
	}
	}
};

#endif //pycppgen_SVector
namespace pycppgen_globals {
}
