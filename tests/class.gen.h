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
		member_function_info Func_info_340;
		Func_info_340.Name = "Func";
		Func_info_340.Declaration = "void ()";
		Func_info_340.Attributes = {
				{ "callable", "" }
				};
		Func_info_340.ReturnType = "void";
		//parameters
		{
		}
		member_function_info Add_info_350;
		Add_info_350.Name = "Add";
		Add_info_350.Declaration = "float (float, double)";
		Add_info_350.Attributes = {
				{ "callable", "" }
				};
		Add_info_350.ReturnType = "float";
		//parameters
		{
			function_parameter_info A_info_359;
			A_info_359.Name = "A";
			A_info_359.Type = "float";
			A_info_359.DefaultValue = "";
			A_info_359.Attributes = {};
			Add_info_350.Parameters.push_back(A_info_359);
			function_parameter_info B_info_365;
			B_info_365.Name = "B";
			B_info_365.Type = "double";
			B_info_365.DefaultValue = "";
			B_info_365.Attributes = {};
			Add_info_350.Parameters.push_back(B_info_365);
		}
		member_function_info Get_info_372;
		Get_info_372.Name = "Get";
		Get_info_372.Declaration = "short () const";
		Get_info_372.Attributes = {
				{ "pure", "" }
				};
		Get_info_372.ReturnType = "short";
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
		struct type_CObject { using type = CObject; const type* obj = nullptr; };
		fn(type_CObject());
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		pycppgen<CObject>::for_each_var(fn);

		member_variable_info Matrix_info_462;
		Matrix_info_462.Name = "Matrix";
		Matrix_info_462.FullName = "CChild::Matrix";
		Matrix_info_462.Type = access_helper().Matrix_TypeName;
		Matrix_info_462.Offset = access_helper().Matrix_Offset;
		Matrix_info_462.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_462.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_462.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_462.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_462.Attributes = {

			};
		fn(Matrix_info_462);

	}

	static void for_each_var_typed(auto fn) {
		pycppgen<CObject>::for_each_var_typed(fn);

		member_variable_info Matrix_info_481;
		Matrix_info_481.Name = "Matrix";
		Matrix_info_481.FullName = "CChild::Matrix";
		Matrix_info_481.Type = access_helper().Matrix_TypeName;
		Matrix_info_481.Offset = access_helper().Matrix_Offset;
		Matrix_info_481.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_481.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_481.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_481.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_481.Attributes = {

			};
		fn(Matrix_info_481, access_helper().GetMatrixRef());

	}

	static void for_each_var(CChild* obj, auto visitor) {
		pycppgen<CObject>::for_each_var(obj, visitor);

		member_variable_info Matrix_info_500;
		Matrix_info_500.Name = "Matrix";
		Matrix_info_500.FullName = "CChild::Matrix";
		Matrix_info_500.Type = access_helper().Matrix_TypeName;
		Matrix_info_500.Offset = access_helper().Matrix_Offset;
		Matrix_info_500.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_500.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_500.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_500.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_500.Attributes = {

			};
		visitor(Matrix_info_500, ((access_helper*)obj)->GetMatrixRef());
	}

	static void for_each_var(const CChild* obj, auto visitor) {
		pycppgen<CObject>::for_each_var(obj, visitor);

		member_variable_info Matrix_info_518;
		Matrix_info_518.Name = "Matrix";
		Matrix_info_518.FullName = "CChild::Matrix";
		Matrix_info_518.Type = access_helper().Matrix_TypeName;
		Matrix_info_518.Offset = access_helper().Matrix_Offset;
		Matrix_info_518.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_518.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_518.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_518.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_518.Attributes = {

			};
		visitor(Matrix_info_518, ((access_helper*)obj)->GetMatrixRef());
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
		member_function_info DoSomething_info_563;
		DoSomething_info_563.Name = "DoSomething";
		DoSomething_info_563.Declaration = "void ()";
		DoSomething_info_563.Attributes = {

				};
		DoSomething_info_563.ReturnType = "void";
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
