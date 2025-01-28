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
		member_variable_info ProtectedUint_info_75;
		ProtectedUint_info_75.Name = "ProtectedUint";
		ProtectedUint_info_75.Type = typeid(unsigned int).name();
		ProtectedUint_info_75.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_75.ElementSize = sizeof(std::remove_all_extents_t<unsigned int>);
		ProtectedUint_info_75.TotalSize = sizeof(unsigned int);
		ProtectedUint_info_75.ArrayRank = std::rank_v<unsigned int>;
		ProtectedUint_info_75.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		fn(ProtectedUint_info_75);

		member_variable_info PublicShort_info_89;
		PublicShort_info_89.Name = "PublicShort";
		PublicShort_info_89.Type = typeid(short).name();
		PublicShort_info_89.Offset = offsetof(CObject, PublicShort);
		PublicShort_info_89.ElementSize = sizeof(std::remove_all_extents_t<short>);
		PublicShort_info_89.TotalSize = sizeof(short);
		PublicShort_info_89.ArrayRank = std::rank_v<short>;
		PublicShort_info_89.Attributes = {
			{ "serialize", "" }
			};
		fn(PublicShort_info_89);

	}

	static void for_each_var(CObject* obj, auto visitor) {
		visitor("ProtectedUint", ((access_helper*)obj)->GetProtectedUintRef());
		visitor("PublicShort", ((access_helper*)obj)->GetPublicShortRef());
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
		member_function_info Func_info_143;
		Func_info_143.Name = "Func";
		Func_info_143.Declaration = "void ()";
		Func_info_143.Attributes = {
				{ "callable", "" }
				};
		Func_info_143.ReturnType = "void";
		//parameters
		{
		}
		member_function_info Add_info_153;
		Add_info_153.Name = "Add";
		Add_info_153.Declaration = "float (float, double)";
		Add_info_153.Attributes = {
				{ "callable", "" }
				};
		Add_info_153.ReturnType = "float";
		//parameters
		{
			function_parameter_info A_info_162;
			A_info_162.Name = "A";
			A_info_162.Type = "float";
			A_info_162.DefaultValue = "";
			A_info_162.Attributes = {};
			Add_info_153.Parameters.push_back(A_info_162);
			function_parameter_info B_info_168;
			B_info_168.Name = "B";
			B_info_168.Type = "double";
			B_info_168.DefaultValue = "";
			B_info_168.Attributes = {};
			Add_info_153.Parameters.push_back(B_info_168);
		}
		member_function_info Get_info_175;
		Get_info_175.Name = "Get";
		Get_info_175.Declaration = "short () const";
		Get_info_175.Attributes = {
				{ "pure", "" }
				};
		Get_info_175.ReturnType = "short";
		//parameters
		{
		}
	}

	static constexpr bool has_function(std::string_view name) {
		if (name == std::string_view("Func")) return true; 
		if (name == std::string_view("Add")) return true; 
		if (name == std::string_view("Get")) return true; 
		if (name == std::string_view("TestStaticFunc")) return true; 
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

	static bool call_function(std::string_view name, int& result) {
		if (name == "TestStaticFunc") {
			result = CObject::TestStaticFunc();
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

#endif //pycppgen_CObject
//</autogen_pycppgen_CObject>

//<autogen_pycppgen_CChild>

#ifndef pycppgen_CChild
#define pycppgen_CChild

template<>
struct pycppgen<CChild> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string_view, std::string_view> Attributes = {
		{ "pure", "" }
		};

	struct access_helper : CChild {
		const size_t Matrix_Offset = offsetof(access_helper, CChild::Matrix);
		const void SetMatrix(const decltype(CChild::Matrix )& value) { CChild::Matrix = value; }
		const auto& GetMatrix() const { return CChild::Matrix; }
		auto& GetMatrixRef() { return CChild::Matrix; }
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		pycppgen<CObject>::for_each_var(fn);

		member_variable_info Matrix_info_263;
		Matrix_info_263.Name = "Matrix";
		Matrix_info_263.Type = typeid(int).name();
		Matrix_info_263.Offset = offsetof(CChild, Matrix);
		Matrix_info_263.ElementSize = sizeof(std::remove_all_extents_t<int>);
		Matrix_info_263.TotalSize = sizeof(int);
		Matrix_info_263.ArrayRank = std::rank_v<int>;
		Matrix_info_263.Attributes = {

			};
		fn(Matrix_info_263);

	}

	static void for_each_var(CChild* obj, auto visitor) {
		pycppgen<CObject>::for_each_var(obj, visitor);

		visitor("Matrix", ((access_helper*)obj)->GetMatrixRef());
	}

	static std::map<std::string, std::string> get_member_attributes(std::string_view name) {
		if (name == "Matrix")
		{
			return {

				};
		}

		{
			const auto m = pycppgen<CObject>::get_member_attributes(name);
			if (!m.empty()) return m;
		}

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
		pycppgen<CObject>::for_each_function(fn);
	}

	static constexpr bool has_function(std::string_view name) {
		if (pycppgen<CObject>::has_function(name)) return true;
		return false;
	}

};

#endif //pycppgen_CChild
//</autogen_pycppgen_CChild>

namespace pycppgen_globals {
}
