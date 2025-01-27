#pragma once

#include "pycppgen.h"
#include "class.h"

//<autogen_pycppgen_CObject_SSubObject>

#ifndef pycppgen_CObject_SSubObject
#define pycppgen_CObject_SSubObject

template<>
struct pycppgen<CObject::SSubObject> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string_view, std::string_view> Attributes = {

	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
	}
	static void for_each_var(CObject::SSubObject* obj, auto visitor) {
	}
	static std::map<std::string, std::string> get_member_attributes(std::string_view name) {
		return {};
	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	template<typename T> static T dump(const CObject::SSubObject* object) {
		T result;
		return result;
	}
	template<typename T, typename R> static bool parse(const T& data, R* object) {
		return true;
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
struct pycppgen<CObject> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string_view, std::string_view> Attributes = {
		{ "pure", "" }
	};

	struct access_helper : CObject {
		const size_t ProtectedUint_Offset = offsetof(access_helper, CObject::ProtectedUint);
		const void SetProtectedUint(const decltype(CObject::ProtectedUint )& value) { CObject::ProtectedUint = value; }
		const auto& GetProtectedUint() const { return CObject::ProtectedUint; }
		auto& GetProtectedUintRef() { return CObject::ProtectedUint; }
		const size_t PublicShort_Offset = offsetof(access_helper, CObject::PublicShort);
		const void SetPublicShort(const decltype(CObject::PublicShort )& value) { CObject::PublicShort = value; }
		const auto& GetPublicShort() const { return CObject::PublicShort; }
		auto& GetPublicShortRef() { return CObject::PublicShort; }
	};
	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		member_variable_info ProtectedUint_info_66;
		ProtectedUint_info_66.Name = "ProtectedUint";
		ProtectedUint_info_66.Type = typeid(unsigned int).name();
		ProtectedUint_info_66.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_66.ElementSize = sizeof(std::remove_all_extents_t<unsigned int>);
		ProtectedUint_info_66.TotalSize = sizeof(unsigned int);
		ProtectedUint_info_66.ArrayRank = std::rank_v<unsigned int>;
		ProtectedUint_info_66.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
		};
		fn(ProtectedUint_info_66);

		member_variable_info PublicShort_info_80;
		PublicShort_info_80.Name = "PublicShort";
		PublicShort_info_80.Type = typeid(short).name();
		PublicShort_info_80.Offset = offsetof(CObject, PublicShort);
		PublicShort_info_80.ElementSize = sizeof(std::remove_all_extents_t<short>);
		PublicShort_info_80.TotalSize = sizeof(short);
		PublicShort_info_80.ArrayRank = std::rank_v<short>;
		PublicShort_info_80.Attributes = {
			{ "serialize", "" }
		};
		fn(PublicShort_info_80);

	}
	static void for_each_var(CObject* obj, auto visitor) {
		visitor("ProtectedUint", ((access_helper*)obj)->GetProtectedUintRef());
		visitor("PublicShort", ((access_helper*)obj)->GetPublicShortRef());
	}
	static std::map<std::string, std::string> get_member_attributes(std::string_view name) {
		if (name == "ProtectedUint") return {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
		};
		if (name == "PublicShort") return {
			{ "serialize", "" }
		};
		return {};
	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	template<typename T> static T dump(const CObject* object) {
		T result;
		result["ProtectedUint"] = ((access_helper*)object)->GetProtectedUint();
		result["PublicShort"] = ((access_helper*)object)->GetPublicShort();
		return result;
	}
	template<typename T, typename R> static bool parse(const T& data, R* object) {
		((access_helper*)object)->SetProtectedUint(data["ProtectedUint"]);
		((access_helper*)object)->SetPublicShort(data["PublicShort"]);
		return true;
	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
		member_function_info Func_info_122;
		Func_info_122.Name = "Func";
		Func_info_122.Declaration = "void ()";
		Func_info_122.Attributes = {
				{ "callable", "" }
			};
		Func_info_122.ReturnType = "void";
		//parameters
		{
		}
		member_function_info Add_info_132;
		Add_info_132.Name = "Add";
		Add_info_132.Declaration = "float (float, double)";
		Add_info_132.Attributes = {
				{ "callable", "" }
			};
		Add_info_132.ReturnType = "float";
		//parameters
		{
			function_parameter_info A_info_141;
			A_info_141.Name = "A";
			A_info_141.Type = "float";
			A_info_141.DefaultValue = "";
			A_info_141.Attributes = {};
			Add_info_132.Parameters.push_back(A_info_141);
			function_parameter_info B_info_147;
			B_info_147.Name = "B";
			B_info_147.Type = "double";
			B_info_147.DefaultValue = "";
			B_info_147.Attributes = {};
			Add_info_132.Parameters.push_back(B_info_147);
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

void CObject::for_each_var(std::function<void(const member_variable_info&)> fn) const { return pycppgen<std::decay_t<decltype(*this)>>::for_each_var(fn); }
void CObject::for_each_var(std::function<void(const member_variable_info&)> fn) { return pycppgen<std::decay_t<decltype(*this)>>::for_each_var(fn); }
#endif //pycppgen_CObject
//</autogen_pycppgen_CObject>

//<autogen_pycppgen_CChild>

#ifndef pycppgen_CChild
#define pycppgen_CChild

template<>
struct pycppgen<CChild> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string_view, std::string_view> Attributes = {};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
	}
	static void for_each_var(CChild* obj, auto visitor) {
	}
	static std::map<std::string, std::string> get_member_attributes(std::string_view name) {
		return {};
	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	template<typename T> static T dump(const CChild* object) {
		T result;
		return result;
	}
	template<typename T, typename R> static bool parse(const T& data, R* object) {
		return true;
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
