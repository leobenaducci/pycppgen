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

	static void for_each_parent(auto fn) {
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		member_variable_info ProtectedUint_info_115;
		ProtectedUint_info_115.Name = "ProtectedUint";
		ProtectedUint_info_115.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_115.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_115.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_115.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_115.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_115.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_115.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_115.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		fn(ProtectedUint_info_115);

		member_variable_info PublicShort_info_131;
		PublicShort_info_131.Name = "PublicShort";
		PublicShort_info_131.FullName = "CObject::PublicShort";
		PublicShort_info_131.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_131.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_131.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_131.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_131.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_131.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_131.Attributes = {
			{ "serialize", "" }
			};
		fn(PublicShort_info_131);

		member_variable_info PublicCharArray_info_145;
		PublicCharArray_info_145.Name = "PublicCharArray";
		PublicCharArray_info_145.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_145.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_145.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_145.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_145.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_145.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_145.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_145.Attributes = {

			};
		fn(PublicCharArray_info_145);

	}

	static void for_each_var(CObject* obj, auto visitor) {
		member_variable_info ProtectedUint_info_162;
		ProtectedUint_info_162.Name = "ProtectedUint";
		ProtectedUint_info_162.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_162.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_162.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_162.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_162.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_162.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_162.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_162.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		visitor(ProtectedUint_info_162, ((access_helper*)obj)->GetProtectedUintRef());
		member_variable_info PublicShort_info_177;
		PublicShort_info_177.Name = "PublicShort";
		PublicShort_info_177.FullName = "CObject::PublicShort";
		PublicShort_info_177.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_177.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_177.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_177.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_177.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_177.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_177.Attributes = {
			{ "serialize", "" }
			};
		visitor(PublicShort_info_177, ((access_helper*)obj)->GetPublicShortRef());
		member_variable_info PublicCharArray_info_190;
		PublicCharArray_info_190.Name = "PublicCharArray";
		PublicCharArray_info_190.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_190.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_190.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_190.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_190.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_190.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_190.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_190.Attributes = {

			};
		visitor(PublicCharArray_info_190, ((access_helper*)obj)->GetPublicCharArrayRef());
	}

	static void for_each_var(const CObject* obj, auto visitor) {
		member_variable_info ProtectedUint_info_206;
		ProtectedUint_info_206.Name = "ProtectedUint";
		ProtectedUint_info_206.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_206.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_206.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_206.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_206.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_206.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_206.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_206.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		visitor(ProtectedUint_info_206, ((access_helper*)obj)->GetProtectedUintRef());
		member_variable_info PublicShort_info_221;
		PublicShort_info_221.Name = "PublicShort";
		PublicShort_info_221.FullName = "CObject::PublicShort";
		PublicShort_info_221.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_221.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_221.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_221.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_221.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_221.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_221.Attributes = {
			{ "serialize", "" }
			};
		visitor(PublicShort_info_221, ((access_helper*)obj)->GetPublicShortRef());
		member_variable_info PublicCharArray_info_234;
		PublicCharArray_info_234.Name = "PublicCharArray";
		PublicCharArray_info_234.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_234.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_234.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_234.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_234.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_234.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_234.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_234.Attributes = {

			};
		visitor(PublicCharArray_info_234, ((access_helper*)obj)->GetPublicCharArrayRef());
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
		member_function_info Func_info_290;
		Func_info_290.Name = "Func";
		Func_info_290.Declaration = "void ()";
		Func_info_290.Attributes = {
				{ "callable", "" }
				};
		Func_info_290.ReturnType = "void";
		//parameters
		{
		}
		member_function_info Add_info_300;
		Add_info_300.Name = "Add";
		Add_info_300.Declaration = "float (float, double)";
		Add_info_300.Attributes = {
				{ "callable", "" }
				};
		Add_info_300.ReturnType = "float";
		//parameters
		{
			function_parameter_info A_info_309;
			A_info_309.Name = "A";
			A_info_309.Type = "float";
			A_info_309.DefaultValue = "";
			A_info_309.Attributes = {};
			Add_info_300.Parameters.push_back(A_info_309);
			function_parameter_info B_info_315;
			B_info_315.Name = "B";
			B_info_315.Type = "double";
			B_info_315.DefaultValue = "";
			B_info_315.Attributes = {};
			Add_info_300.Parameters.push_back(B_info_315);
		}
		member_function_info Get_info_322;
		Get_info_322.Name = "Get";
		Get_info_322.Declaration = "short () const";
		Get_info_322.Attributes = {
				{ "pure", "" }
				};
		Get_info_322.ReturnType = "short";
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

	static void for_each_parent(auto fn) {
		fn(*(CObject*)0);
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		pycppgen<CObject>::for_each_var(fn);

		member_variable_info Matrix_info_411;
		Matrix_info_411.Name = "Matrix";
		Matrix_info_411.FullName = "CChild::Matrix";
		Matrix_info_411.Type = access_helper().Matrix_TypeName;
		Matrix_info_411.Offset = access_helper().Matrix_Offset;
		Matrix_info_411.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_411.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_411.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_411.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_411.Attributes = {

			};
		fn(Matrix_info_411);

	}

	static void for_each_var(CChild* obj, auto visitor) {
		pycppgen<CObject>::for_each_var(obj, visitor);

		member_variable_info Matrix_info_430;
		Matrix_info_430.Name = "Matrix";
		Matrix_info_430.FullName = "CChild::Matrix";
		Matrix_info_430.Type = access_helper().Matrix_TypeName;
		Matrix_info_430.Offset = access_helper().Matrix_Offset;
		Matrix_info_430.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_430.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_430.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_430.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_430.Attributes = {

			};
		visitor(Matrix_info_430, ((access_helper*)obj)->GetMatrixRef());
	}

	static void for_each_var(const CChild* obj, auto visitor) {
		pycppgen<CObject>::for_each_var(obj, visitor);

		member_variable_info Matrix_info_448;
		Matrix_info_448.Name = "Matrix";
		Matrix_info_448.FullName = "CChild::Matrix";
		Matrix_info_448.Type = access_helper().Matrix_TypeName;
		Matrix_info_448.Offset = access_helper().Matrix_Offset;
		Matrix_info_448.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_448.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_448.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_448.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_448.Attributes = {

			};
		visitor(Matrix_info_448, ((access_helper*)obj)->GetMatrixRef());
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
		member_function_info DoSomething_info_493;
		DoSomething_info_493.Name = "DoSomething";
		DoSomething_info_493.Declaration = "void ()";
		DoSomething_info_493.Attributes = {

				};
		DoSomething_info_493.ReturnType = "void";
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
