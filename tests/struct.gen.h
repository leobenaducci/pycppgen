#pragma once

#include "pycppgen.h"
#include "struct.h"

//<autogen_pycppgen_SStructTest>

#ifndef pycppgen_SStructTest
#define pycppgen_SStructTest

template<>
struct pycppgen<SStructTest> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string_view, std::string_view> Attributes = {
		{ "visible", "" }
		};

	struct access_helper : SStructTest {
		const size_t x_Offset = offsetof(access_helper, SStructTest::x);
		const void Setx(const decltype(SStructTest::x )& value) { SStructTest::x = value; }
		const auto& Getx() const { return SStructTest::x; }
		auto& GetxRef() { return SStructTest::x; }
		const size_t y_Offset = offsetof(access_helper, SStructTest::y);
		const void Sety(const decltype(SStructTest::y )& value) { SStructTest::y = value; }
		const auto& Gety() const { return SStructTest::y; }
		auto& GetyRef() { return SStructTest::y; }
		const size_t z_Offset = offsetof(access_helper, SStructTest::z);
		const void Setz(const decltype(SStructTest::z )& value) { SStructTest::z = value; }
		const auto& Getz() const { return SStructTest::z; }
		auto& GetzRef() { return SStructTest::z; }
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		member_variable_info x_info_33;
		x_info_33.Name = "x";
		x_info_33.FullName = "SStructTest::x";
		x_info_33.Type = typeid(float).name();
		x_info_33.Offset = offsetof(SStructTest, x);
		x_info_33.ElementSize = sizeof(std::remove_all_extents_t<float>);
		x_info_33.TotalSize = sizeof(float);
		x_info_33.ArrayRank = std::rank_v<float>;
		x_info_33.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(x_info_33);

		member_variable_info y_info_47;
		y_info_47.Name = "y";
		y_info_47.FullName = "SStructTest::y";
		y_info_47.Type = typeid(float).name();
		y_info_47.Offset = offsetof(SStructTest, y);
		y_info_47.ElementSize = sizeof(std::remove_all_extents_t<float>);
		y_info_47.TotalSize = sizeof(float);
		y_info_47.ArrayRank = std::rank_v<float>;
		y_info_47.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(y_info_47);

		member_variable_info z_info_61;
		z_info_61.Name = "z";
		z_info_61.FullName = "SStructTest::z";
		z_info_61.Type = typeid(float).name();
		z_info_61.Offset = offsetof(SStructTest, z);
		z_info_61.ElementSize = sizeof(std::remove_all_extents_t<float>);
		z_info_61.TotalSize = sizeof(float);
		z_info_61.ArrayRank = std::rank_v<float>;
		z_info_61.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(z_info_61);

	}

	static void for_each_var(SStructTest* obj, auto visitor) {
		member_variable_info x_info_78;
		x_info_78.Name = "x";
		x_info_78.FullName = "SStructTest::x";
		x_info_78.Type = typeid(float).name();
		x_info_78.Offset = offsetof(SStructTest, x);
		x_info_78.ElementSize = sizeof(std::remove_all_extents_t<float>);
		x_info_78.TotalSize = sizeof(float);
		x_info_78.ArrayRank = std::rank_v<float>;
		x_info_78.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(x_info_78, ((access_helper*)obj)->GetxRef());
		member_variable_info y_info_91;
		y_info_91.Name = "y";
		y_info_91.FullName = "SStructTest::y";
		y_info_91.Type = typeid(float).name();
		y_info_91.Offset = offsetof(SStructTest, y);
		y_info_91.ElementSize = sizeof(std::remove_all_extents_t<float>);
		y_info_91.TotalSize = sizeof(float);
		y_info_91.ArrayRank = std::rank_v<float>;
		y_info_91.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(y_info_91, ((access_helper*)obj)->GetyRef());
		member_variable_info z_info_104;
		z_info_104.Name = "z";
		z_info_104.FullName = "SStructTest::z";
		z_info_104.Type = typeid(float).name();
		z_info_104.Offset = offsetof(SStructTest, z);
		z_info_104.ElementSize = sizeof(std::remove_all_extents_t<float>);
		z_info_104.TotalSize = sizeof(float);
		z_info_104.ArrayRank = std::rank_v<float>;
		z_info_104.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(z_info_104, ((access_helper*)obj)->GetzRef());
	}

	static void for_each_var(const SStructTest* obj, auto visitor) {
		member_variable_info x_info_120;
		x_info_120.Name = "x";
		x_info_120.FullName = "SStructTest::x";
		x_info_120.Type = typeid(float).name();
		x_info_120.Offset = offsetof(SStructTest, x);
		x_info_120.ElementSize = sizeof(std::remove_all_extents_t<float>);
		x_info_120.TotalSize = sizeof(float);
		x_info_120.ArrayRank = std::rank_v<float>;
		x_info_120.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(x_info_120, ((access_helper*)obj)->GetxRef());
		member_variable_info y_info_133;
		y_info_133.Name = "y";
		y_info_133.FullName = "SStructTest::y";
		y_info_133.Type = typeid(float).name();
		y_info_133.Offset = offsetof(SStructTest, y);
		y_info_133.ElementSize = sizeof(std::remove_all_extents_t<float>);
		y_info_133.TotalSize = sizeof(float);
		y_info_133.ArrayRank = std::rank_v<float>;
		y_info_133.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(y_info_133, ((access_helper*)obj)->GetyRef());
		member_variable_info z_info_146;
		z_info_146.Name = "z";
		z_info_146.FullName = "SStructTest::z";
		z_info_146.Type = typeid(float).name();
		z_info_146.Offset = offsetof(SStructTest, z);
		z_info_146.ElementSize = sizeof(std::remove_all_extents_t<float>);
		z_info_146.TotalSize = sizeof(float);
		z_info_146.ArrayRank = std::rank_v<float>;
		z_info_146.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(z_info_146, ((access_helper*)obj)->GetzRef());
	}

	static std::map<std::string, std::string> get_member_attributes(std::string_view name) {
		if (name == "x")
		{
			return {
				{ "visible", "" },
				{ "serialize", "" }
				};
		}
		if (name == "y")
		{
			return {
				{ "visible", "" },
				{ "serialize", "" }
				};
		}
		if (name == "z")
		{
			return {
				{ "visible", "" },
				{ "serialize", "" }
				};
		}
		return {};
	}

	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
		fn("size");
	}

	template<typename T> static T dump(const SStructTest* object) {
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

#endif //pycppgen_SStructTest
//</autogen_pycppgen_SStructTest>

namespace pycppgen_globals {
//const int SStructTest::size
}
