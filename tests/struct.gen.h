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
		x_info_49.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(x_info_49);

		member_variable_info y_info_64;
		y_info_64.Name = "y";
		y_info_64.FullName = "SStructTest::y";
		y_info_64.Type = access_helper().y_TypeName;
		y_info_64.Offset = access_helper().y_Offset;
		y_info_64.ElementSize = access_helper().y_ElementSize;
		y_info_64.TotalSize = access_helper().y_TotalSize;
		y_info_64.ArrayRank = access_helper().y_ArrayRank;
		y_info_64.ArrayExtents = access_helper().y_ArrayExtents;
		y_info_64.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(y_info_64);

		member_variable_info z_info_79;
		z_info_79.Name = "z";
		z_info_79.FullName = "SStructTest::z";
		z_info_79.Type = access_helper().z_TypeName;
		z_info_79.Offset = access_helper().z_Offset;
		z_info_79.ElementSize = access_helper().z_ElementSize;
		z_info_79.TotalSize = access_helper().z_TotalSize;
		z_info_79.ArrayRank = access_helper().z_ArrayRank;
		z_info_79.ArrayExtents = access_helper().z_ArrayExtents;
		z_info_79.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(z_info_79);

	}

	static void for_each_var_typed(auto fn) {
		member_variable_info x_info_97;
		x_info_97.Name = "x";
		x_info_97.FullName = "SStructTest::x";
		x_info_97.Type = access_helper().x_TypeName;
		x_info_97.Offset = access_helper().x_Offset;
		x_info_97.ElementSize = access_helper().x_ElementSize;
		x_info_97.TotalSize = access_helper().x_TotalSize;
		x_info_97.ArrayRank = access_helper().x_ArrayRank;
		x_info_97.ArrayExtents = access_helper().x_ArrayExtents;
		x_info_97.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(x_info_97, access_helper().GetxRef());

		member_variable_info y_info_112;
		y_info_112.Name = "y";
		y_info_112.FullName = "SStructTest::y";
		y_info_112.Type = access_helper().y_TypeName;
		y_info_112.Offset = access_helper().y_Offset;
		y_info_112.ElementSize = access_helper().y_ElementSize;
		y_info_112.TotalSize = access_helper().y_TotalSize;
		y_info_112.ArrayRank = access_helper().y_ArrayRank;
		y_info_112.ArrayExtents = access_helper().y_ArrayExtents;
		y_info_112.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(y_info_112, access_helper().GetyRef());

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
		fn(z_info_127, access_helper().GetzRef());

	}

	static void for_each_var(SStructTest* obj, auto visitor) {
		member_variable_info x_info_145;
		x_info_145.Name = "x";
		x_info_145.FullName = "SStructTest::x";
		x_info_145.Type = access_helper().x_TypeName;
		x_info_145.Offset = access_helper().x_Offset;
		x_info_145.ElementSize = access_helper().x_ElementSize;
		x_info_145.TotalSize = access_helper().x_TotalSize;
		x_info_145.ArrayRank = access_helper().x_ArrayRank;
		x_info_145.ArrayExtents = access_helper().x_ArrayExtents;
		x_info_145.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(x_info_145, ((access_helper*)obj)->GetxRef());
		member_variable_info y_info_159;
		y_info_159.Name = "y";
		y_info_159.FullName = "SStructTest::y";
		y_info_159.Type = access_helper().y_TypeName;
		y_info_159.Offset = access_helper().y_Offset;
		y_info_159.ElementSize = access_helper().y_ElementSize;
		y_info_159.TotalSize = access_helper().y_TotalSize;
		y_info_159.ArrayRank = access_helper().y_ArrayRank;
		y_info_159.ArrayExtents = access_helper().y_ArrayExtents;
		y_info_159.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(y_info_159, ((access_helper*)obj)->GetyRef());
		member_variable_info z_info_173;
		z_info_173.Name = "z";
		z_info_173.FullName = "SStructTest::z";
		z_info_173.Type = access_helper().z_TypeName;
		z_info_173.Offset = access_helper().z_Offset;
		z_info_173.ElementSize = access_helper().z_ElementSize;
		z_info_173.TotalSize = access_helper().z_TotalSize;
		z_info_173.ArrayRank = access_helper().z_ArrayRank;
		z_info_173.ArrayExtents = access_helper().z_ArrayExtents;
		z_info_173.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(z_info_173, ((access_helper*)obj)->GetzRef());
	}

	static void for_each_var(const SStructTest* obj, auto visitor) {
		member_variable_info x_info_190;
		x_info_190.Name = "x";
		x_info_190.FullName = "SStructTest::x";
		x_info_190.Type = access_helper().x_TypeName;
		x_info_190.Offset = access_helper().x_Offset;
		x_info_190.ElementSize = access_helper().x_ElementSize;
		x_info_190.TotalSize = access_helper().x_TotalSize;
		x_info_190.ArrayRank = access_helper().x_ArrayRank;
		x_info_190.ArrayExtents = access_helper().x_ArrayExtents;
		x_info_190.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(x_info_190, ((access_helper*)obj)->GetxRef());
		member_variable_info y_info_204;
		y_info_204.Name = "y";
		y_info_204.FullName = "SStructTest::y";
		y_info_204.Type = access_helper().y_TypeName;
		y_info_204.Offset = access_helper().y_Offset;
		y_info_204.ElementSize = access_helper().y_ElementSize;
		y_info_204.TotalSize = access_helper().y_TotalSize;
		y_info_204.ArrayRank = access_helper().y_ArrayRank;
		y_info_204.ArrayExtents = access_helper().y_ArrayExtents;
		y_info_204.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(y_info_204, ((access_helper*)obj)->GetyRef());
		member_variable_info z_info_218;
		z_info_218.Name = "z";
		z_info_218.FullName = "SStructTest::z";
		z_info_218.Type = access_helper().z_TypeName;
		z_info_218.Offset = access_helper().z_Offset;
		z_info_218.ElementSize = access_helper().z_ElementSize;
		z_info_218.TotalSize = access_helper().z_TotalSize;
		z_info_218.ArrayRank = access_helper().z_ArrayRank;
		z_info_218.ArrayExtents = access_helper().z_ArrayExtents;
		z_info_218.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(z_info_218, ((access_helper*)obj)->GetzRef());
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

	static void for_each_function(std::function<void(const member_function_info&)> fn) {
	}

	static constexpr bool has_function(std::string_view name) {
		return false;
	}

};

#endif //_pycppgen_SStructTest
//</autogen__pycppgen_SStructTest>

namespace pycppgen_globals {
}
