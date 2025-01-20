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

template<typename T> struct meta {};

#endif //_PYCPPGEN_DECLARATIONS

template<>
struct meta<SVector>{
	std::map<std::string, std::string> Attributes = {
		{ "visible", "" }
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		struct access_helper : SVector {
			const size_t x_Offset = offsetof(access_helper, SVector::x);
			const size_t y_Offset = offsetof(access_helper, SVector::y);
			const size_t z_Offset = offsetof(access_helper, SVector::z);
		};
		member_variable_info x_info;
		x_info.Name = "x";
		x_info.Type = typeid(float).name();
		x_info.Offset = access_helper().x_Offset;
		x_info.ElementSize = sizeof(std::remove_all_extents_t<float>);
		x_info.TotalSize = sizeof(float);
		x_info.ArrayRank = std::rank_v<float>;
		x_info.Attributes = {
			{ "visible", "" }
		};

		fn(x_info);
		member_variable_info y_info;
		y_info.Name = "y";
		y_info.Type = typeid(float).name();
		y_info.Offset = access_helper().y_Offset;
		y_info.ElementSize = sizeof(std::remove_all_extents_t<float>);
		y_info.TotalSize = sizeof(float);
		y_info.ArrayRank = std::rank_v<float>;
		y_info.Attributes = {
			{ "visible", "" }
		};

		fn(y_info);
		member_variable_info z_info;
		z_info.Name = "z";
		z_info.Type = typeid(float).name();
		z_info.Offset = access_helper().z_Offset;
		z_info.ElementSize = sizeof(std::remove_all_extents_t<float>);
		z_info.TotalSize = sizeof(float);
		z_info.ArrayRank = std::rank_v<float>;
		z_info.Attributes = {
			{ "visible", "" }
		};

		fn(z_info);
	}
};

