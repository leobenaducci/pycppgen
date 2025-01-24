#pragma once

#include "class.h"

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

template<typename T> auto pycppgen_typeof(T&& t) { return pycppgen<std::decay_t<decltype(t)>>(); }

#endif //_PYCPPGEN_DECLARATIONS

//<autogen_pycppgen_CObject_SSubObject>

#ifndef pycppgen_CObject_SSubObject
#define pycppgen_CObject_SSubObject

template<>
struct pycppgen<CObject::SSubObject>{
	std::map<std::string_view, std::string_view> Attributes = {

	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	template<typename T> static T dump(const CObject::SSubObject* object) {
		T result;
		result["object_type"] = "CObject::SSubObject";
	}
	template<typename T> static std::shared_ptr<CObject::SSubObject> parse(const T& data) {
		CObject::SSubObject* object = std::make_shared<CObject::SSubObject>();
	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
	}
	static constexpr bool has_function(std::string_view name) {
		return false;
	}
};

#endif //pycppgen_CObject_SSubObject
//</autogen_pycppgen_CObject_SSubObject>

//<autogen_pycppgen_CObject>

#ifndef pycppgen_CObject
#define pycppgen_CObject

template<>
struct pycppgen<CObject>{
	std::map<std::string_view, std::string_view> Attributes = {
		{ "pure", "" }
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		struct access_helper : CObject {
			const size_t ProtectedUint_Offset = offsetof(access_helper, CObject::ProtectedUint);
			const size_t PublicShort_Offset = offsetof(access_helper, CObject::PublicShort);
			const size_t PublicCharArray_Offset = offsetof(access_helper, CObject::PublicCharArray);
		};
		member_variable_info ProtectedUint_info_88;
		ProtectedUint_info_88.Name = "ProtectedUint";
		ProtectedUint_info_88.Type = typeid(unsigned int).name();
		ProtectedUint_info_88.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_88.ElementSize = sizeof(std::remove_all_extents_t<unsigned int>);
		ProtectedUint_info_88.TotalSize = sizeof(unsigned int);
		ProtectedUint_info_88.ArrayRank = std::rank_v<unsigned int>;
		ProtectedUint_info_88.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
		};
		fn(ProtectedUint_info_88);

		member_variable_info PublicShort_info_102;
		PublicShort_info_102.Name = "PublicShort";
		PublicShort_info_102.Type = typeid(short).name();
		PublicShort_info_102.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_102.ElementSize = sizeof(std::remove_all_extents_t<short>);
		PublicShort_info_102.TotalSize = sizeof(short);
		PublicShort_info_102.ArrayRank = std::rank_v<short>;
		PublicShort_info_102.Attributes = {
			{ "serialize", "" }
		};
		fn(PublicShort_info_102);

		member_variable_info PublicCharArray_info_114;
		PublicCharArray_info_114.Name = "PublicCharArray";
		PublicCharArray_info_114.Type = typeid(char[16]).name();
		PublicCharArray_info_114.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_114.ElementSize = sizeof(std::remove_all_extents_t<char[16]>);
		PublicCharArray_info_114.TotalSize = sizeof(char[16]);
		PublicCharArray_info_114.ArrayRank = std::rank_v<char[16]>;
		PublicCharArray_info_114.ArrayExtents.push_back(std::extent_v<char[16], 0>);
		PublicCharArray_info_114.Attributes = {
			{ "readonly", "" }
		};
		fn(PublicCharArray_info_114);

	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	template<typename T> static T dump(const CObject* object) {
		T result;
		result["object_type"] = "CObject";
		struct access_helper : CObject {
			const auto GetProtectedUint() const { return CObject::ProtectedUint);
			const auto GetPublicShort() const { return CObject::PublicShort);
		};
		result["ProtectedUint"] = ((access_helper*)this)->GetProtectedUint();
		result["PublicShort"] = ((access_helper*)this)->GetPublicShort();
	}
	template<typename T> static std::shared_ptr<CObject> parse(const T& data) {
		CObject* object = std::make_shared<CObject>();
		struct access_helper : CObject {
			const void SetProtectedUint(const unsigned int& value) const { CObject::ProtectedUint = value;
			const void SetPublicShort(const short& value) const { CObject::PublicShort = value;
		};
		((access_helper*)object)->SetProtectedUint(data["ProtectedUint"]);
		((access_helper*)object)->SetPublicShort(data["PublicShort"]);
	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
		member_function_info Func_info_150;
		Func_info_150.Name = "Func";
		Func_info_150.Declaration = "void ()";
		Func_info_150.Attributes = {
				{ "callable", "" }
			};
		Func_info_150.ReturnType = "void";
		//parameters
		{
		}
		member_function_info Add_info_160;
		Add_info_160.Name = "Add";
		Add_info_160.Declaration = "float (float, double)";
		Add_info_160.Attributes = {
				{ "callable", "" }
			};
		Add_info_160.ReturnType = "float";
		//parameters
		{
			function_parameter_info A_info_169;
			A_info_169.Name = "A";
			A_info_169.Type = "float";
			A_info_169.DefaultValue = "";
			A_info_169.Attributes = {};
			Add_info_160.Parameters.push_back(A_info_169);
			function_parameter_info B_info_175;
			B_info_175.Name = "B";
			B_info_175.Type = "double";
			B_info_175.DefaultValue = "";
			B_info_175.Attributes = {};
			Add_info_160.Parameters.push_back(B_info_175);
		}
	}
	static constexpr bool has_function(std::string_view name) {
		if (name == std::string_view("Func")) return true; 
		if (name == std::string_view("Add")) return true; 
		if (name == std::string_view("TestStaticFunc")) return true; 
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
	static bool call_function(std::string_view name, int& result) {
		if (name == "TestStaticFunc") {
			result = CObject::TestStaticFunc();
			return true;
		}
		return false;
	}
};

#endif //pycppgen_CObject
//</autogen_pycppgen_CObject>

//<autogen_pycppgen_CChild>

#ifndef pycppgen_CChild
#define pycppgen_CChild

template<>
struct pycppgen<CChild>{
	std::map<std::string_view, std::string_view> Attributes = {};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	template<typename T> static T dump(const CChild* object) {
		T result;
		result["object_type"] = "CChild";
	}
	template<typename T> static std::shared_ptr<CChild> parse(const T& data) {
		CChild* object = std::make_shared<CChild>();
	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
	}
	static constexpr bool has_function(std::string_view name) {
		return false;
	}
};

#endif //pycppgen_CChild
//</autogen_pycppgen_CChild>

namespace pycppgen_globals {
}
