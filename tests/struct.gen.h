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

	static void for_each_parent(auto fn) {
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		member_variable_info x_info_49;
		x_info_49.Name = "x";
		x_info_49.FullName = "SStructTest::x";
		x_info_49.Type = access_helper().x_TypeName;
		x_info_49.Offset = access_helper().x_Offset;
		x_info_49.ElementSize = access_helper().x_ElementSize;
		x_info_49.TotalSize = access_helper().x_TotalSize;
		x_info_49.ArrayRank = access_helper().x_ArrayRank;
		x_info_49.ArrayExtents = access_helper().x_ArrayExtents;
		fn(x_info_49);

		member_variable_info y_info_60;
		y_info_60.Name = "y";
		y_info_60.FullName = "SStructTest::y";
		y_info_60.Type = access_helper().y_TypeName;
		y_info_60.Offset = access_helper().y_Offset;
		y_info_60.ElementSize = access_helper().y_ElementSize;
		y_info_60.TotalSize = access_helper().y_TotalSize;
		y_info_60.ArrayRank = access_helper().y_ArrayRank;
		y_info_60.ArrayExtents = access_helper().y_ArrayExtents;
		fn(y_info_60);

		member_variable_info z_info_71;
		z_info_71.Name = "z";
		z_info_71.FullName = "SStructTest::z";
		z_info_71.Type = access_helper().z_TypeName;
		z_info_71.Offset = access_helper().z_Offset;
		z_info_71.ElementSize = access_helper().z_ElementSize;
		z_info_71.TotalSize = access_helper().z_TotalSize;
		z_info_71.ArrayRank = access_helper().z_ArrayRank;
		z_info_71.ArrayExtents = access_helper().z_ArrayExtents;
		fn(z_info_71);

	}

	static void for_each_var_typed(auto fn) {
		member_variable_info x_info_85;
		x_info_85.Name = "x";
		x_info_85.FullName = "SStructTest::x";
		x_info_85.Type = access_helper().x_TypeName;
		x_info_85.Offset = access_helper().x_Offset;
		x_info_85.ElementSize = access_helper().x_ElementSize;
		x_info_85.TotalSize = access_helper().x_TotalSize;
		x_info_85.ArrayRank = access_helper().x_ArrayRank;
		x_info_85.ArrayExtents = access_helper().x_ArrayExtents;
		fn(x_info_85, access_helper().GetxRef());

		member_variable_info y_info_96;
		y_info_96.Name = "y";
		y_info_96.FullName = "SStructTest::y";
		y_info_96.Type = access_helper().y_TypeName;
		y_info_96.Offset = access_helper().y_Offset;
		y_info_96.ElementSize = access_helper().y_ElementSize;
		y_info_96.TotalSize = access_helper().y_TotalSize;
		y_info_96.ArrayRank = access_helper().y_ArrayRank;
		y_info_96.ArrayExtents = access_helper().y_ArrayExtents;
		fn(y_info_96, access_helper().GetyRef());

		member_variable_info z_info_107;
		z_info_107.Name = "z";
		z_info_107.FullName = "SStructTest::z";
		z_info_107.Type = access_helper().z_TypeName;
		z_info_107.Offset = access_helper().z_Offset;
		z_info_107.ElementSize = access_helper().z_ElementSize;
		z_info_107.TotalSize = access_helper().z_TotalSize;
		z_info_107.ArrayRank = access_helper().z_ArrayRank;
		z_info_107.ArrayExtents = access_helper().z_ArrayExtents;
		fn(z_info_107, access_helper().GetzRef());

	}

	static void for_each_var(SStructTest* obj, auto visitor) {
		member_variable_info x_info_121;
		x_info_121.Name = "x";
		x_info_121.FullName = "SStructTest::x";
		x_info_121.Type = access_helper().x_TypeName;
		x_info_121.Offset = access_helper().x_Offset;
		x_info_121.ElementSize = access_helper().x_ElementSize;
		x_info_121.TotalSize = access_helper().x_TotalSize;
		x_info_121.ArrayRank = access_helper().x_ArrayRank;
		x_info_121.ArrayExtents = access_helper().x_ArrayExtents;
		visitor(x_info_121, ((access_helper*)obj)->GetxRef());
		member_variable_info y_info_131;
		y_info_131.Name = "y";
		y_info_131.FullName = "SStructTest::y";
		y_info_131.Type = access_helper().y_TypeName;
		y_info_131.Offset = access_helper().y_Offset;
		y_info_131.ElementSize = access_helper().y_ElementSize;
		y_info_131.TotalSize = access_helper().y_TotalSize;
		y_info_131.ArrayRank = access_helper().y_ArrayRank;
		y_info_131.ArrayExtents = access_helper().y_ArrayExtents;
		visitor(y_info_131, ((access_helper*)obj)->GetyRef());
		member_variable_info z_info_141;
		z_info_141.Name = "z";
		z_info_141.FullName = "SStructTest::z";
		z_info_141.Type = access_helper().z_TypeName;
		z_info_141.Offset = access_helper().z_Offset;
		z_info_141.ElementSize = access_helper().z_ElementSize;
		z_info_141.TotalSize = access_helper().z_TotalSize;
		z_info_141.ArrayRank = access_helper().z_ArrayRank;
		z_info_141.ArrayExtents = access_helper().z_ArrayExtents;
		visitor(z_info_141, ((access_helper*)obj)->GetzRef());
	}

	static void for_each_var(const SStructTest* obj, auto visitor) {
		member_variable_info x_info_154;
		x_info_154.Name = "x";
		x_info_154.FullName = "SStructTest::x";
		x_info_154.Type = access_helper().x_TypeName;
		x_info_154.Offset = access_helper().x_Offset;
		x_info_154.ElementSize = access_helper().x_ElementSize;
		x_info_154.TotalSize = access_helper().x_TotalSize;
		x_info_154.ArrayRank = access_helper().x_ArrayRank;
		x_info_154.ArrayExtents = access_helper().x_ArrayExtents;
		visitor(x_info_154, ((access_helper*)obj)->GetxRef());
		member_variable_info y_info_164;
		y_info_164.Name = "y";
		y_info_164.FullName = "SStructTest::y";
		y_info_164.Type = access_helper().y_TypeName;
		y_info_164.Offset = access_helper().y_Offset;
		y_info_164.ElementSize = access_helper().y_ElementSize;
		y_info_164.TotalSize = access_helper().y_TotalSize;
		y_info_164.ArrayRank = access_helper().y_ArrayRank;
		y_info_164.ArrayExtents = access_helper().y_ArrayExtents;
		visitor(y_info_164, ((access_helper*)obj)->GetyRef());
		member_variable_info z_info_174;
		z_info_174.Name = "z";
		z_info_174.FullName = "SStructTest::z";
		z_info_174.Type = access_helper().z_TypeName;
		z_info_174.Offset = access_helper().z_Offset;
		z_info_174.ElementSize = access_helper().z_ElementSize;
		z_info_174.TotalSize = access_helper().z_TotalSize;
		z_info_174.ArrayRank = access_helper().z_ArrayRank;
		z_info_174.ArrayExtents = access_helper().z_ArrayExtents;
		visitor(z_info_174, ((access_helper*)obj)->GetzRef());
	}

	static std::map<std::string, std::string> get_var_attributes(std::string_view name) {
		std::map<std::string, std::string> result;
		if (name == "x")
			 result = {
				{ "visible", "" },
				{ "serialize", "" }
				};
		if (name == "y")
			 result = {
				{ "visible", "" },
				{ "serialize", "" }
				};
		if (name == "z")
			 result = {
				{ "visible", "" },
				{ "serialize", "" }
				};
		return result;
	}

	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
		fn("size");
	}

	template<typename T> static bool dump(T& result, const SStructTest* object) {
		result["x"] = ((access_helper*)object)->Getx();
		result["y"] = ((access_helper*)object)->Gety();
		result["z"] = ((access_helper*)object)->Getz();
		return true;
	}

	template<typename T, typename R> static bool parse(const T& data, R* object) {
		((access_helper*)object)->Setx(data["x"]);
		((access_helper*)object)->Sety(data["y"]);
		((access_helper*)object)->Setz(data["z"]);
		return true;
	}

	static void for_each_function(auto fn) {
	}

	static bool find_function_by_name(std::string_view name, auto fn) {
		bool result = false;
		for_each_function([&](const auto& info) {
			if (info.Name == name) { result = true; fn(info); } 
		});
	return result;
	}

	static constexpr bool has_function(std::string_view name) {
		return false;
	}

};

#endif //_pycppgen_SStructTest
//</autogen__pycppgen_SStructTest>

namespace pycppgen_globals {
}
