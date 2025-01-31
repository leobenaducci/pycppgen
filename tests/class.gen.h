#pragma once

#include "pycppgen.h"
#include "class.h"

//<autogen__pycppgen_CObject_SSubObject>

#ifndef _pycppgen_CObject_SSubObject
#define _pycppgen_CObject_SSubObject

template<>
struct pycppgen<CObject::SSubObject> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string_view, std::string_view> Attributes = {

		};

	static void for_each_parent(auto fn) {
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
	}

	static void for_each_var_typed(auto fn) {
	}

	static void for_each_var(CObject::SSubObject* obj, auto visitor) {
	}

	static void for_each_var(const CObject::SSubObject* obj, auto visitor) {
	}

	static std::map<std::string, std::string> get_member_attributes(std::string_view name) {
		return {};
	}

	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}

	template<typename T> static bool dump(T& result, const CObject::SSubObject* object) {
		return true;
	}

	template<typename T, typename R> static bool parse(const T& data, R* object) {
		return true;
	}

	static void for_each_function(std::function<void(const member_function_info&)> fn) {
	}

	static constexpr bool has_function(std::string_view name) {
		if (name == std::string_view("OnRegister")) return true; 
		return false;
	}

	static bool call_function(std::string_view name) {
		if (name == "OnRegister") {
			CObject::SSubObject::OnRegister();
			return true;
		}
		return false;
	}

};

#endif //_pycppgen_CObject_SSubObject
//</autogen__pycppgen_CObject_SSubObject>

//<autogen__pycppgen_CObject>

#ifndef _pycppgen_CObject
#define _pycppgen_CObject

template<>
struct pycppgen<CObject> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string_view, std::string_view> Attributes = {
		{ "pure", "" },
		{ "serialize", "" }
		};

	struct access_helper : public CObject {
		using ProtectedUint_t = decltype(CObject::ProtectedUint);
		const size_t ProtectedUint_Offset = offsetof(access_helper, CObject::ProtectedUint);
		const size_t ProtectedUint_ElementSize = sizeof(std::remove_all_extents_t<ProtectedUint_t>);
		const size_t ProtectedUint_TotalSize = sizeof(ProtectedUint_t);
		const size_t ProtectedUint_ArrayRank = pycppgen_detail::get_rank(ProtectedUint);
		const std::vector<size_t> ProtectedUint_ArrayExtents = pycppgen_detail::get_extents(ProtectedUint);
		const std::string ProtectedUint_TypeName = typeid(decltype(CObject::ProtectedUint)).name();
		const void SetProtectedUint(const decltype(CObject::ProtectedUint )& value) { CObject::ProtectedUint = value; }
		const auto& GetProtectedUint() const { return CObject::ProtectedUint; }
		auto& GetProtectedUintRef() { return CObject::ProtectedUint; }
		using PublicShort_t = decltype(CObject::PublicShort);
		const size_t PublicShort_Offset = offsetof(access_helper, CObject::PublicShort);
		const size_t PublicShort_ElementSize = sizeof(std::remove_all_extents_t<PublicShort_t>);
		const size_t PublicShort_TotalSize = sizeof(PublicShort_t);
		const size_t PublicShort_ArrayRank = pycppgen_detail::get_rank(PublicShort);
		const std::vector<size_t> PublicShort_ArrayExtents = pycppgen_detail::get_extents(PublicShort);
		const std::string PublicShort_TypeName = typeid(decltype(CObject::PublicShort)).name();
		const void SetPublicShort(const decltype(CObject::PublicShort )& value) { CObject::PublicShort = value; }
		const auto& GetPublicShort() const { return CObject::PublicShort; }
		auto& GetPublicShortRef() { return CObject::PublicShort; }
		using PublicCharArray_t = decltype(CObject::PublicCharArray);
		const size_t PublicCharArray_Offset = offsetof(access_helper, CObject::PublicCharArray);
		const size_t PublicCharArray_ElementSize = sizeof(std::remove_all_extents_t<PublicCharArray_t>);
		const size_t PublicCharArray_TotalSize = sizeof(PublicCharArray_t);
		const size_t PublicCharArray_ArrayRank = pycppgen_detail::get_rank(PublicCharArray);
		const std::vector<size_t> PublicCharArray_ArrayExtents = pycppgen_detail::get_extents(PublicCharArray);
		const std::string PublicCharArray_TypeName = typeid(decltype(CObject::PublicCharArray)).name();
		const void SetPublicCharArray(const decltype(CObject::PublicCharArray )& value) { CObject::PublicCharArray = value; }
		const auto& GetPublicCharArray() const { return CObject::PublicCharArray; }
		auto& GetPublicCharArrayRef() { return CObject::PublicCharArray; }
	};

	static void for_each_parent(auto fn) {
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		member_variable_info ProtectedUint_info_118;
		ProtectedUint_info_118.Name = "ProtectedUint";
		ProtectedUint_info_118.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_118.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_118.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_118.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_118.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_118.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_118.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_118.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		fn(ProtectedUint_info_118);

		member_variable_info PublicShort_info_134;
		PublicShort_info_134.Name = "PublicShort";
		PublicShort_info_134.FullName = "CObject::PublicShort";
		PublicShort_info_134.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_134.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_134.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_134.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_134.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_134.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_134.Attributes = {
			{ "serialize", "" }
			};
		fn(PublicShort_info_134);

		member_variable_info PublicCharArray_info_148;
		PublicCharArray_info_148.Name = "PublicCharArray";
		PublicCharArray_info_148.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_148.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_148.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_148.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_148.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_148.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_148.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_148.Attributes = {
			{ "serialize", "" }
			};
		fn(PublicCharArray_info_148);

	}

	static void for_each_var_typed(auto fn) {
		member_variable_info ProtectedUint_info_165;
		ProtectedUint_info_165.Name = "ProtectedUint";
		ProtectedUint_info_165.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_165.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_165.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_165.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_165.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_165.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_165.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_165.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		fn(ProtectedUint_info_165, access_helper().GetProtectedUintRef());

		member_variable_info PublicShort_info_181;
		PublicShort_info_181.Name = "PublicShort";
		PublicShort_info_181.FullName = "CObject::PublicShort";
		PublicShort_info_181.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_181.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_181.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_181.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_181.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_181.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_181.Attributes = {
			{ "serialize", "" }
			};
		fn(PublicShort_info_181, access_helper().GetPublicShortRef());

		member_variable_info PublicCharArray_info_195;
		PublicCharArray_info_195.Name = "PublicCharArray";
		PublicCharArray_info_195.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_195.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_195.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_195.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_195.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_195.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_195.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_195.Attributes = {
			{ "serialize", "" }
			};
		fn(PublicCharArray_info_195, access_helper().GetPublicCharArrayRef());

	}

	static void for_each_var(CObject* obj, auto visitor) {
		member_variable_info ProtectedUint_info_212;
		ProtectedUint_info_212.Name = "ProtectedUint";
		ProtectedUint_info_212.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_212.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_212.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_212.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_212.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_212.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_212.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_212.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		visitor(ProtectedUint_info_212, ((access_helper*)obj)->GetProtectedUintRef());
		member_variable_info PublicShort_info_227;
		PublicShort_info_227.Name = "PublicShort";
		PublicShort_info_227.FullName = "CObject::PublicShort";
		PublicShort_info_227.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_227.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_227.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_227.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_227.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_227.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_227.Attributes = {
			{ "serialize", "" }
			};
		visitor(PublicShort_info_227, ((access_helper*)obj)->GetPublicShortRef());
		member_variable_info PublicCharArray_info_240;
		PublicCharArray_info_240.Name = "PublicCharArray";
		PublicCharArray_info_240.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_240.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_240.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_240.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_240.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_240.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_240.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_240.Attributes = {
			{ "serialize", "" }
			};
		visitor(PublicCharArray_info_240, ((access_helper*)obj)->GetPublicCharArrayRef());
	}

	static void for_each_var(const CObject* obj, auto visitor) {
		member_variable_info ProtectedUint_info_256;
		ProtectedUint_info_256.Name = "ProtectedUint";
		ProtectedUint_info_256.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_256.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_256.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_256.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_256.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_256.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_256.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_256.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		visitor(ProtectedUint_info_256, ((access_helper*)obj)->GetProtectedUintRef());
		member_variable_info PublicShort_info_271;
		PublicShort_info_271.Name = "PublicShort";
		PublicShort_info_271.FullName = "CObject::PublicShort";
		PublicShort_info_271.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_271.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_271.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_271.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_271.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_271.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_271.Attributes = {
			{ "serialize", "" }
			};
		visitor(PublicShort_info_271, ((access_helper*)obj)->GetPublicShortRef());
		member_variable_info PublicCharArray_info_284;
		PublicCharArray_info_284.Name = "PublicCharArray";
		PublicCharArray_info_284.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_284.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_284.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_284.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_284.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_284.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_284.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_284.Attributes = {
			{ "serialize", "" }
			};
		visitor(PublicCharArray_info_284, ((access_helper*)obj)->GetPublicCharArrayRef());
	}

	static std::map<std::string, std::string> get_member_attributes(std::string_view name) {
		if (name == "ProtectedUint")
		{
			return {
				{ "min", "3" },
				{ "max", "15" },
				{ "serialize", "" }
				};
		}
		if (name == "PublicShort")
		{
			return {
				{ "serialize", "" }
				};
		}
		if (name == "PublicCharArray")
		{
			return {
				{ "serialize", "" }
				};
		}
		return {};
	}

	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}

	template<typename T> static bool dump(T& result, const CObject* object) {
		result["ProtectedUint"] = ((access_helper*)object)->GetProtectedUint();
		result["PublicShort"] = ((access_helper*)object)->GetPublicShort();
		result["PublicCharArray"] = ((access_helper*)object)->GetPublicCharArray();
		return true;
	}

	template<typename T, typename R> static bool parse(const T& data, R* object) {
		((access_helper*)object)->SetProtectedUint(data["ProtectedUint"]);
		((access_helper*)object)->SetPublicShort(data["PublicShort"]);
		((access_helper*)object)->SetPublicCharArray(data["PublicCharArray"]);
		return true;
	}

	static void for_each_function(std::function<void(const member_function_info&)> fn) {
		member_function_info Func_info_341;
		Func_info_341.Name = "Func";
		Func_info_341.Declaration = "void ()";
		Func_info_341.Attributes = {
				{ "callable", "" }
				};
		Func_info_341.ReturnType = "void";
		//parameters
		{
		}
		member_function_info Add_info_351;
		Add_info_351.Name = "Add";
		Add_info_351.Declaration = "float (float, double)";
		Add_info_351.Attributes = {
				{ "callable", "" }
				};
		Add_info_351.ReturnType = "float";
		//parameters
		{
			function_parameter_info A_info_360;
			A_info_360.Name = "A";
			A_info_360.Type = "float";
			A_info_360.DefaultValue = "";
			A_info_360.Attributes = {};
			Add_info_351.Parameters.push_back(A_info_360);
			function_parameter_info B_info_366;
			B_info_366.Name = "B";
			B_info_366.Type = "double";
			B_info_366.DefaultValue = "";
			B_info_366.Attributes = {};
			Add_info_351.Parameters.push_back(B_info_366);
		}
		member_function_info Get_info_373;
		Get_info_373.Name = "Get";
		Get_info_373.Declaration = "short () const";
		Get_info_373.Attributes = {
				{ "pure", "" }
				};
		Get_info_373.ReturnType = "short";
		//parameters
		{
		}
	}

	static constexpr bool has_function(std::string_view name) {
		if (name == std::string_view("Func")) return true; 
		if (name == std::string_view("Add")) return true; 
		if (name == std::string_view("Get")) return true; 
		if (name == std::string_view("OnRegister")) return true; 
		return false;
	}

	static bool call_function(std::string_view name, CObject* object) {
		if (name == "Func") {
			object->Func();
			return true;
		}
		return false;
	}

	static bool call_function(std::string_view name, CObject* object, float& result, float _1, double _2) {
		if (name == "Add") {
			result = object->Add( _1,  _2);
			return true;
		}
		return false;
	}

	static bool call_function(std::string_view name, const CObject* object, short& result) {
		if (name == "Get") {
			result = object->Get();
			return true;
		}
		return false;
	}

	static bool call_function(std::string_view name) {
		if (name == "OnRegister") {
			CObject::OnRegister();
			return true;
		}
		return false;
	}

};

#endif //_pycppgen_CObject
//</autogen__pycppgen_CObject>

namespace pycppgen_globals {
}
