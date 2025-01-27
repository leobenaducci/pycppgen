#pragma once

#include "pycppgen.h"
#include "struct.h"

//<autogen_pycppgen_SVector>

#ifndef pycppgen_SVector
#define pycppgen_SVector

template<>
struct pycppgen<SVector> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string_view, std::string_view> Attributes = {
		{ "visible", "" }
	};

	struct access_helper : SVector {
		const size_t x_Offset = offsetof(access_helper, SVector::x);
		const void Setx(const decltype(SVector::x )& value) { SVector::x = value; }
		const auto& Getx() const { return SVector::x; }
		auto& GetxRef() { return SVector::x; }
		const size_t y_Offset = offsetof(access_helper, SVector::y);
		const void Sety(const decltype(SVector::y )& value) { SVector::y = value; }
		const auto& Gety() const { return SVector::y; }
		auto& GetyRef() { return SVector::y; }
		const size_t z_Offset = offsetof(access_helper, SVector::z);
		const void Setz(const decltype(SVector::z )& value) { SVector::z = value; }
		const auto& Getz() const { return SVector::z; }
		auto& GetzRef() { return SVector::z; }
	};
	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		member_variable_info x_info_32;
		x_info_32.Name = "x";
		x_info_32.Type = typeid(float).name();
		x_info_32.Offset = offsetof(SVector, x);
		x_info_32.ElementSize = sizeof(std::remove_all_extents_t<float>);
		x_info_32.TotalSize = sizeof(float);
		x_info_32.ArrayRank = std::rank_v<float>;
		x_info_32.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
		};
		fn(x_info_32);

		member_variable_info y_info_45;
		y_info_45.Name = "y";
		y_info_45.Type = typeid(float).name();
		y_info_45.Offset = offsetof(SVector, y);
		y_info_45.ElementSize = sizeof(std::remove_all_extents_t<float>);
		y_info_45.TotalSize = sizeof(float);
		y_info_45.ArrayRank = std::rank_v<float>;
		y_info_45.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
		};
		fn(y_info_45);

		member_variable_info z_info_58;
		z_info_58.Name = "z";
		z_info_58.Type = typeid(float).name();
		z_info_58.Offset = offsetof(SVector, z);
		z_info_58.ElementSize = sizeof(std::remove_all_extents_t<float>);
		z_info_58.TotalSize = sizeof(float);
		z_info_58.ArrayRank = std::rank_v<float>;
		z_info_58.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
		};
		fn(z_info_58);

	}
	static void for_each_var(SVector* obj, auto visitor) {
		visitor("x", ((access_helper*)obj)->GetxRef());
		visitor("y", ((access_helper*)obj)->GetyRef());
		visitor("z", ((access_helper*)obj)->GetzRef());
	}
	static std::map<std::string, std::string> get_member_attributes(std::string_view name) {
		if (name == "x") return {
			{ "visible", "" },
			{ "serialize", "" }
		};
		if (name == "y") return {
			{ "visible", "" },
			{ "serialize", "" }
		};
		if (name == "z") return {
			{ "visible", "" },
			{ "serialize", "" }
		};
		return {};
	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
		fn("size");
	}
	template<typename T> static T dump(const SVector* object) {
		T result;
		result["x"] = ((access_helper*)object)->Getx();
		result["y"] = ((access_helper*)object)->Gety();
		result["z"] = ((access_helper*)object)->Getz();
		return result;
	}
	template<typename T, typename R> static bool parse(const T& data, R* object) {
		((access_helper*)object)->Setx(data["x"]);
		((access_helper*)object)->Sety(data["y"]);
		((access_helper*)object)->Setz(data["z"]);
		return true;
	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
	}
	static constexpr bool has_function(std::string_view name) {
		return false;
	}
};

#endif //pycppgen_SVector
//</autogen_pycppgen_SVector>

namespace pycppgen_globals {
//const int SVector::size
}
