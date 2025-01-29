#pragma once

#include "pycppgen.h"
#include "struct.h"

//<autogen__pycppgen_SStructTest>

#ifndef _pycppgen_SStructTest
#define _pycppgen_SStructTest

template<>
struct pycppgen<SStructTest> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string_view, std::string_view> Attributes = {
		{ "visible", "" }
		};

	struct access_helper : public SStructTest {
		using x_t = decltype(SStructTest::x);
		const size_t x_Offset = offsetof(access_helper, SStructTest::x);
		const size_t x_ElementSize = sizeof(std::remove_all_extents_t<x_t>);
		const size_t x_TotalSize = sizeof(x_t);
		const size_t x_ArrayRank = pycppgen_detail::get_rank(x);
		const std::vector<size_t> x_ArrayExtents = pycppgen_detail::get_extents(x);
		const std::string x_TypeName = typeid(decltype(SStructTest::x)).name();
		const void Setx(const decltype(SStructTest::x )& value) { SStructTest::x = value; }
		const auto& Getx() const { return SStructTest::x; }
		auto& GetxRef() { return SStructTest::x; }
		using y_t = decltype(SStructTest::y);
		const size_t y_Offset = offsetof(access_helper, SStructTest::y);
		const size_t y_ElementSize = sizeof(std::remove_all_extents_t<y_t>);
		const size_t y_TotalSize = sizeof(y_t);
		const size_t y_ArrayRank = pycppgen_detail::get_rank(y);
		const std::vector<size_t> y_ArrayExtents = pycppgen_detail::get_extents(y);
		const std::string y_TypeName = typeid(decltype(SStructTest::y)).name();
		const void Sety(const decltype(SStructTest::y )& value) { SStructTest::y = value; }
		const auto& Gety() const { return SStructTest::y; }
		auto& GetyRef() { return SStructTest::y; }
		using z_t = decltype(SStructTest::z);
		const size_t z_Offset = offsetof(access_helper, SStructTest::z);
		const size_t z_ElementSize = sizeof(std::remove_all_extents_t<z_t>);
		const size_t z_TotalSize = sizeof(z_t);
		const size_t z_ArrayRank = pycppgen_detail::get_rank(z);
		const std::vector<size_t> z_ArrayExtents = pycppgen_detail::get_extents(z);
		const std::string z_TypeName = typeid(decltype(SStructTest::z)).name();
		const void Setz(const decltype(SStructTest::z )& value) { SStructTest::z = value; }
		const auto& Getz() const { return SStructTest::z; }
		auto& GetzRef() { return SStructTest::z; }
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		member_variable_info x_info_51;
		x_info_51.Name = "x";
		x_info_51.FullName = "SStructTest::x";
		x_info_51.Type = access_helper().x_TypeName;
		x_info_51.Offset = access_helper().x_Offset;
		x_info_51.ElementSize = access_helper().x_ElementSize;
		x_info_51.TotalSize = access_helper().x_TotalSize;
		x_info_51.ArrayRank = access_helper().x_ArrayRank;
		x_info_51.ArrayExtents = access_helper().x_ArrayExtents;
		x_info_51.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(x_info_51);

		member_variable_info y_info_66;
		y_info_66.Name = "y";
		y_info_66.FullName = "SStructTest::y";
		y_info_66.Type = access_helper().y_TypeName;
		y_info_66.Offset = access_helper().y_Offset;
		y_info_66.ElementSize = access_helper().y_ElementSize;
		y_info_66.TotalSize = access_helper().y_TotalSize;
		y_info_66.ArrayRank = access_helper().y_ArrayRank;
		y_info_66.ArrayExtents = access_helper().y_ArrayExtents;
		y_info_66.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(y_info_66);

		member_variable_info z_info_81;
		z_info_81.Name = "z";
		z_info_81.FullName = "SStructTest::z";
		z_info_81.Type = access_helper().z_TypeName;
		z_info_81.Offset = access_helper().z_Offset;
		z_info_81.ElementSize = access_helper().z_ElementSize;
		z_info_81.TotalSize = access_helper().z_TotalSize;
		z_info_81.ArrayRank = access_helper().z_ArrayRank;
		z_info_81.ArrayExtents = access_helper().z_ArrayExtents;
		z_info_81.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(z_info_81);

	}

	static void for_each_var(SStructTest* obj, auto visitor) {
		member_variable_info x_info_99;
		x_info_99.Name = "x";
		x_info_99.FullName = "SStructTest::x";
		x_info_99.Type = access_helper().x_TypeName;
		x_info_99.Offset = access_helper().x_Offset;
		x_info_99.ElementSize = access_helper().x_ElementSize;
		x_info_99.TotalSize = access_helper().x_TotalSize;
		x_info_99.ArrayRank = access_helper().x_ArrayRank;
		x_info_99.ArrayExtents = access_helper().x_ArrayExtents;
		x_info_99.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(x_info_99, ((access_helper*)obj)->GetxRef());
		member_variable_info y_info_113;
		y_info_113.Name = "y";
		y_info_113.FullName = "SStructTest::y";
		y_info_113.Type = access_helper().y_TypeName;
		y_info_113.Offset = access_helper().y_Offset;
		y_info_113.ElementSize = access_helper().y_ElementSize;
		y_info_113.TotalSize = access_helper().y_TotalSize;
		y_info_113.ArrayRank = access_helper().y_ArrayRank;
		y_info_113.ArrayExtents = access_helper().y_ArrayExtents;
		y_info_113.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(y_info_113, ((access_helper*)obj)->GetyRef());
		member_variable_info z_info_127;
		z_info_127.Name = "z";
		z_info_127.FullName = "SStructTest::z";
		z_info_127.Type = access_helper().z_TypeName;
		z_info_127.Offset = access_helper().z_Offset;
		z_info_127.ElementSize = access_helper().z_ElementSize;
		z_info_127.TotalSize = access_helper().z_TotalSize;
		z_info_127.ArrayRank = access_helper().z_ArrayRank;
		z_info_127.ArrayExtents = access_helper().z_ArrayExtents;
		z_info_127.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(z_info_127, ((access_helper*)obj)->GetzRef());
	}

	static void for_each_var(const SStructTest* obj, auto visitor) {
		member_variable_info x_info_144;
		x_info_144.Name = "x";
		x_info_144.FullName = "SStructTest::x";
		x_info_144.Type = access_helper().x_TypeName;
		x_info_144.Offset = access_helper().x_Offset;
		x_info_144.ElementSize = access_helper().x_ElementSize;
		x_info_144.TotalSize = access_helper().x_TotalSize;
		x_info_144.ArrayRank = access_helper().x_ArrayRank;
		x_info_144.ArrayExtents = access_helper().x_ArrayExtents;
		x_info_144.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(x_info_144, ((access_helper*)obj)->GetxRef());
		member_variable_info y_info_158;
		y_info_158.Name = "y";
		y_info_158.FullName = "SStructTest::y";
		y_info_158.Type = access_helper().y_TypeName;
		y_info_158.Offset = access_helper().y_Offset;
		y_info_158.ElementSize = access_helper().y_ElementSize;
		y_info_158.TotalSize = access_helper().y_TotalSize;
		y_info_158.ArrayRank = access_helper().y_ArrayRank;
		y_info_158.ArrayExtents = access_helper().y_ArrayExtents;
		y_info_158.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(y_info_158, ((access_helper*)obj)->GetyRef());
		member_variable_info z_info_172;
		z_info_172.Name = "z";
		z_info_172.FullName = "SStructTest::z";
		z_info_172.Type = access_helper().z_TypeName;
		z_info_172.Offset = access_helper().z_Offset;
		z_info_172.ElementSize = access_helper().z_ElementSize;
		z_info_172.TotalSize = access_helper().z_TotalSize;
		z_info_172.ArrayRank = access_helper().z_ArrayRank;
		z_info_172.ArrayExtents = access_helper().z_ArrayExtents;
		z_info_172.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(z_info_172, ((access_helper*)obj)->GetzRef());
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

#endif //_pycppgen_SStructTest
//</autogen__pycppgen_SStructTest>

namespace pycppgen_globals {
//const int SStructTest::size
}
