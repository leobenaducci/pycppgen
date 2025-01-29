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

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
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
		{ "pure", "" }
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

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		member_variable_info ProtectedUint_info_109;
		ProtectedUint_info_109.Name = "ProtectedUint";
		ProtectedUint_info_109.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_109.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_109.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_109.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_109.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_109.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_109.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_109.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		fn(ProtectedUint_info_109);

		member_variable_info PublicShort_info_125;
		PublicShort_info_125.Name = "PublicShort";
		PublicShort_info_125.FullName = "CObject::PublicShort";
		PublicShort_info_125.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_125.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_125.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_125.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_125.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_125.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_125.Attributes = {
			{ "serialize", "" }
			};
		fn(PublicShort_info_125);

		member_variable_info PublicCharArray_info_139;
		PublicCharArray_info_139.Name = "PublicCharArray";
		PublicCharArray_info_139.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_139.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_139.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_139.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_139.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_139.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_139.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_139.Attributes = {

			};
		fn(PublicCharArray_info_139);

	}

	static void for_each_var(CObject* obj, auto visitor) {
		member_variable_info ProtectedUint_info_156;
		ProtectedUint_info_156.Name = "ProtectedUint";
		ProtectedUint_info_156.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_156.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_156.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_156.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_156.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_156.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_156.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_156.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		visitor(ProtectedUint_info_156, ((access_helper*)obj)->GetProtectedUintRef());
		member_variable_info PublicShort_info_171;
		PublicShort_info_171.Name = "PublicShort";
		PublicShort_info_171.FullName = "CObject::PublicShort";
		PublicShort_info_171.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_171.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_171.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_171.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_171.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_171.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_171.Attributes = {
			{ "serialize", "" }
			};
		visitor(PublicShort_info_171, ((access_helper*)obj)->GetPublicShortRef());
		member_variable_info PublicCharArray_info_184;
		PublicCharArray_info_184.Name = "PublicCharArray";
		PublicCharArray_info_184.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_184.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_184.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_184.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_184.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_184.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_184.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_184.Attributes = {

			};
		visitor(PublicCharArray_info_184, ((access_helper*)obj)->GetPublicCharArrayRef());
	}

	static void for_each_var(const CObject* obj, auto visitor) {
		member_variable_info ProtectedUint_info_200;
		ProtectedUint_info_200.Name = "ProtectedUint";
		ProtectedUint_info_200.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_200.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_200.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_200.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_200.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_200.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_200.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_200.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		visitor(ProtectedUint_info_200, ((access_helper*)obj)->GetProtectedUintRef());
		member_variable_info PublicShort_info_215;
		PublicShort_info_215.Name = "PublicShort";
		PublicShort_info_215.FullName = "CObject::PublicShort";
		PublicShort_info_215.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_215.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_215.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_215.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_215.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_215.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_215.Attributes = {
			{ "serialize", "" }
			};
		visitor(PublicShort_info_215, ((access_helper*)obj)->GetPublicShortRef());
		member_variable_info PublicCharArray_info_228;
		PublicCharArray_info_228.Name = "PublicCharArray";
		PublicCharArray_info_228.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_228.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_228.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_228.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_228.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_228.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_228.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_228.Attributes = {

			};
		visitor(PublicCharArray_info_228, ((access_helper*)obj)->GetPublicCharArrayRef());
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
		member_function_info Func_info_284;
		Func_info_284.Name = "Func";
		Func_info_284.Declaration = "void ()";
		Func_info_284.Attributes = {
				{ "callable", "" }
				};
		Func_info_284.ReturnType = "void";
		//parameters
		{
		}
		member_function_info Add_info_294;
		Add_info_294.Name = "Add";
		Add_info_294.Declaration = "float (float, double)";
		Add_info_294.Attributes = {
				{ "callable", "" }
				};
		Add_info_294.ReturnType = "float";
		//parameters
		{
			function_parameter_info A_info_303;
			A_info_303.Name = "A";
			A_info_303.Type = "float";
			A_info_303.DefaultValue = "";
			A_info_303.Attributes = {};
			Add_info_294.Parameters.push_back(A_info_303);
			function_parameter_info B_info_309;
			B_info_309.Name = "B";
			B_info_309.Type = "double";
			B_info_309.DefaultValue = "";
			B_info_309.Attributes = {};
			Add_info_294.Parameters.push_back(B_info_309);
		}
		member_function_info Get_info_316;
		Get_info_316.Name = "Get";
		Get_info_316.Declaration = "short () const";
		Get_info_316.Attributes = {
				{ "pure", "" }
				};
		Get_info_316.ReturnType = "short";
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

//<autogen__pycppgen_CChild>

#ifndef _pycppgen_CChild
#define _pycppgen_CChild

template<>
struct pycppgen<CChild> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string_view, std::string_view> Attributes = {
		{ "pure", "" }
		};

	struct access_helper : public CChild {
		using Matrix_t = decltype(CChild::Matrix);
		const size_t Matrix_Offset = offsetof(access_helper, CChild::Matrix);
		const size_t Matrix_ElementSize = sizeof(std::remove_all_extents_t<Matrix_t>);
		const size_t Matrix_TotalSize = sizeof(Matrix_t);
		const size_t Matrix_ArrayRank = pycppgen_detail::get_rank(Matrix);
		const std::vector<size_t> Matrix_ArrayExtents = pycppgen_detail::get_extents(Matrix);
		const std::string Matrix_TypeName = typeid(decltype(CChild::Matrix)).name();
		const void SetMatrix(const decltype(CChild::Matrix )& value) { CChild::Matrix = value; }
		const auto& GetMatrix() const { return CChild::Matrix; }
		auto& GetMatrixRef() { return CChild::Matrix; }
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		pycppgen<CObject>::for_each_var(fn);

		member_variable_info Matrix_info_401;
		Matrix_info_401.Name = "Matrix";
		Matrix_info_401.FullName = "CChild::Matrix";
		Matrix_info_401.Type = access_helper().Matrix_TypeName;
		Matrix_info_401.Offset = access_helper().Matrix_Offset;
		Matrix_info_401.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_401.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_401.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_401.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_401.Attributes = {

			};
		fn(Matrix_info_401);

	}

	static void for_each_var(CChild* obj, auto visitor) {
		pycppgen<CObject>::for_each_var(obj, visitor);

		member_variable_info Matrix_info_420;
		Matrix_info_420.Name = "Matrix";
		Matrix_info_420.FullName = "CChild::Matrix";
		Matrix_info_420.Type = access_helper().Matrix_TypeName;
		Matrix_info_420.Offset = access_helper().Matrix_Offset;
		Matrix_info_420.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_420.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_420.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_420.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_420.Attributes = {

			};
		visitor(Matrix_info_420, ((access_helper*)obj)->GetMatrixRef());
	}

	static void for_each_var(const CChild* obj, auto visitor) {
		pycppgen<CObject>::for_each_var(obj, visitor);

		member_variable_info Matrix_info_438;
		Matrix_info_438.Name = "Matrix";
		Matrix_info_438.FullName = "CChild::Matrix";
		Matrix_info_438.Type = access_helper().Matrix_TypeName;
		Matrix_info_438.Offset = access_helper().Matrix_Offset;
		Matrix_info_438.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_438.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_438.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_438.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_438.Attributes = {

			};
		visitor(Matrix_info_438, ((access_helper*)obj)->GetMatrixRef());
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
		member_function_info DoSomething_info_483;
		DoSomething_info_483.Name = "DoSomething";
		DoSomething_info_483.Declaration = "void ()";
		DoSomething_info_483.Attributes = {

				};
		DoSomething_info_483.ReturnType = "void";
		//parameters
		{
		}
	}

	static constexpr bool has_function(std::string_view name) {
		if (name == std::string_view("DoSomething")) return true; 
		if (pycppgen<CObject>::has_function(name)) return true;
		return false;
	}

	static bool call_function(std::string_view name, CChild* object) {
		if (name == "DoSomething") {
			object->DoSomething();
			return true;
		}
		return false;
	}

};

#endif //_pycppgen_CChild
//</autogen__pycppgen_CChild>

namespace pycppgen_globals {
}
