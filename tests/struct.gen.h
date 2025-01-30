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
		member_variable_info x_info_54;
		x_info_54.Name = "x";
		x_info_54.FullName = "SStructTest::x";
		x_info_54.Type = access_helper().x_TypeName;
		x_info_54.Offset = access_helper().x_Offset;
		x_info_54.ElementSize = access_helper().x_ElementSize;
		x_info_54.TotalSize = access_helper().x_TotalSize;
		x_info_54.ArrayRank = access_helper().x_ArrayRank;
		x_info_54.ArrayExtents = access_helper().x_ArrayExtents;
		x_info_54.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(x_info_54);

		member_variable_info y_info_69;
		y_info_69.Name = "y";
		y_info_69.FullName = "SStructTest::y";
		y_info_69.Type = access_helper().y_TypeName;
		y_info_69.Offset = access_helper().y_Offset;
		y_info_69.ElementSize = access_helper().y_ElementSize;
		y_info_69.TotalSize = access_helper().y_TotalSize;
		y_info_69.ArrayRank = access_helper().y_ArrayRank;
		y_info_69.ArrayExtents = access_helper().y_ArrayExtents;
		y_info_69.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(y_info_69);

		member_variable_info z_info_84;
		z_info_84.Name = "z";
		z_info_84.FullName = "SStructTest::z";
		z_info_84.Type = access_helper().z_TypeName;
		z_info_84.Offset = access_helper().z_Offset;
		z_info_84.ElementSize = access_helper().z_ElementSize;
		z_info_84.TotalSize = access_helper().z_TotalSize;
		z_info_84.ArrayRank = access_helper().z_ArrayRank;
		z_info_84.ArrayExtents = access_helper().z_ArrayExtents;
		z_info_84.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(z_info_84);

	}

	static void for_each_var_typed(auto fn) {
		member_variable_info x_info_102;
		x_info_102.Name = "x";
		x_info_102.FullName = "SStructTest::x";
		x_info_102.Type = access_helper().x_TypeName;
		x_info_102.Offset = access_helper().x_Offset;
		x_info_102.ElementSize = access_helper().x_ElementSize;
		x_info_102.TotalSize = access_helper().x_TotalSize;
		x_info_102.ArrayRank = access_helper().x_ArrayRank;
		x_info_102.ArrayExtents = access_helper().x_ArrayExtents;
		x_info_102.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(x_info_102, access_helper().GetxRef());

		member_variable_info y_info_117;
		y_info_117.Name = "y";
		y_info_117.FullName = "SStructTest::y";
		y_info_117.Type = access_helper().y_TypeName;
		y_info_117.Offset = access_helper().y_Offset;
		y_info_117.ElementSize = access_helper().y_ElementSize;
		y_info_117.TotalSize = access_helper().y_TotalSize;
		y_info_117.ArrayRank = access_helper().y_ArrayRank;
		y_info_117.ArrayExtents = access_helper().y_ArrayExtents;
		y_info_117.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(y_info_117, access_helper().GetyRef());

		member_variable_info z_info_132;
		z_info_132.Name = "z";
		z_info_132.FullName = "SStructTest::z";
		z_info_132.Type = access_helper().z_TypeName;
		z_info_132.Offset = access_helper().z_Offset;
		z_info_132.ElementSize = access_helper().z_ElementSize;
		z_info_132.TotalSize = access_helper().z_TotalSize;
		z_info_132.ArrayRank = access_helper().z_ArrayRank;
		z_info_132.ArrayExtents = access_helper().z_ArrayExtents;
		z_info_132.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		fn(z_info_132, access_helper().GetzRef());

	}

	static void for_each_var(SStructTest* obj, auto visitor) {
		member_variable_info x_info_150;
		x_info_150.Name = "x";
		x_info_150.FullName = "SStructTest::x";
		x_info_150.Type = access_helper().x_TypeName;
		x_info_150.Offset = access_helper().x_Offset;
		x_info_150.ElementSize = access_helper().x_ElementSize;
		x_info_150.TotalSize = access_helper().x_TotalSize;
		x_info_150.ArrayRank = access_helper().x_ArrayRank;
		x_info_150.ArrayExtents = access_helper().x_ArrayExtents;
		x_info_150.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(x_info_150, ((access_helper*)obj)->GetxRef());
		member_variable_info y_info_164;
		y_info_164.Name = "y";
		y_info_164.FullName = "SStructTest::y";
		y_info_164.Type = access_helper().y_TypeName;
		y_info_164.Offset = access_helper().y_Offset;
		y_info_164.ElementSize = access_helper().y_ElementSize;
		y_info_164.TotalSize = access_helper().y_TotalSize;
		y_info_164.ArrayRank = access_helper().y_ArrayRank;
		y_info_164.ArrayExtents = access_helper().y_ArrayExtents;
		y_info_164.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(y_info_164, ((access_helper*)obj)->GetyRef());
		member_variable_info z_info_178;
		z_info_178.Name = "z";
		z_info_178.FullName = "SStructTest::z";
		z_info_178.Type = access_helper().z_TypeName;
		z_info_178.Offset = access_helper().z_Offset;
		z_info_178.ElementSize = access_helper().z_ElementSize;
		z_info_178.TotalSize = access_helper().z_TotalSize;
		z_info_178.ArrayRank = access_helper().z_ArrayRank;
		z_info_178.ArrayExtents = access_helper().z_ArrayExtents;
		z_info_178.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(z_info_178, ((access_helper*)obj)->GetzRef());
	}

	static void for_each_var(const SStructTest* obj, auto visitor) {
		member_variable_info x_info_195;
		x_info_195.Name = "x";
		x_info_195.FullName = "SStructTest::x";
		x_info_195.Type = access_helper().x_TypeName;
		x_info_195.Offset = access_helper().x_Offset;
		x_info_195.ElementSize = access_helper().x_ElementSize;
		x_info_195.TotalSize = access_helper().x_TotalSize;
		x_info_195.ArrayRank = access_helper().x_ArrayRank;
		x_info_195.ArrayExtents = access_helper().x_ArrayExtents;
		x_info_195.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(x_info_195, ((access_helper*)obj)->GetxRef());
		member_variable_info y_info_209;
		y_info_209.Name = "y";
		y_info_209.FullName = "SStructTest::y";
		y_info_209.Type = access_helper().y_TypeName;
		y_info_209.Offset = access_helper().y_Offset;
		y_info_209.ElementSize = access_helper().y_ElementSize;
		y_info_209.TotalSize = access_helper().y_TotalSize;
		y_info_209.ArrayRank = access_helper().y_ArrayRank;
		y_info_209.ArrayExtents = access_helper().y_ArrayExtents;
		y_info_209.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(y_info_209, ((access_helper*)obj)->GetyRef());
		member_variable_info z_info_223;
		z_info_223.Name = "z";
		z_info_223.FullName = "SStructTest::z";
		z_info_223.Type = access_helper().z_TypeName;
		z_info_223.Offset = access_helper().z_Offset;
		z_info_223.ElementSize = access_helper().z_ElementSize;
		z_info_223.TotalSize = access_helper().z_TotalSize;
		z_info_223.ArrayRank = access_helper().z_ArrayRank;
		z_info_223.ArrayExtents = access_helper().z_ArrayExtents;
		z_info_223.Attributes = {
			{ "visible", "" },
			{ "serialize", "" }
			};
		visitor(z_info_223, ((access_helper*)obj)->GetzRef());
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
//const int SStructTest::size
}
