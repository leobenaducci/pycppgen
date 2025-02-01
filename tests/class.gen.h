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

	static void for_each_function(auto fn) {
	}

	static auto get_function_by_name(std::string_view name) {
		member_function_info<void> result = {};
		for_each_function([&](const auto& fn) {
			if (fn.Name == name) result = fn; 
		});
		return result;
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
		member_variable_info ProtectedUint_info_50;
		ProtectedUint_info_50.Name = "ProtectedUint";
		ProtectedUint_info_50.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_50.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_50.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_50.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_50.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_50.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_50.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_50.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		fn(ProtectedUint_info_50);

		member_variable_info PublicShort_info_66;
		PublicShort_info_66.Name = "PublicShort";
		PublicShort_info_66.FullName = "CObject::PublicShort";
		PublicShort_info_66.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_66.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_66.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_66.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_66.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_66.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_66.Attributes = {
			{ "serialize", "" }
			};
		fn(PublicShort_info_66);

		member_variable_info PublicCharArray_info_80;
		PublicCharArray_info_80.Name = "PublicCharArray";
		PublicCharArray_info_80.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_80.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_80.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_80.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_80.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_80.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_80.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_80.Attributes = {
			{ "serialize", "" }
			};
		fn(PublicCharArray_info_80);

	}

	static void for_each_var_typed(auto fn) {
		member_variable_info ProtectedUint_info_97;
		ProtectedUint_info_97.Name = "ProtectedUint";
		ProtectedUint_info_97.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_97.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_97.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_97.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_97.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_97.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_97.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_97.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		fn(ProtectedUint_info_97, access_helper().GetProtectedUintRef());

		member_variable_info PublicShort_info_113;
		PublicShort_info_113.Name = "PublicShort";
		PublicShort_info_113.FullName = "CObject::PublicShort";
		PublicShort_info_113.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_113.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_113.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_113.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_113.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_113.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_113.Attributes = {
			{ "serialize", "" }
			};
		fn(PublicShort_info_113, access_helper().GetPublicShortRef());

		member_variable_info PublicCharArray_info_127;
		PublicCharArray_info_127.Name = "PublicCharArray";
		PublicCharArray_info_127.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_127.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_127.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_127.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_127.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_127.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_127.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_127.Attributes = {
			{ "serialize", "" }
			};
		fn(PublicCharArray_info_127, access_helper().GetPublicCharArrayRef());

	}

	static void for_each_var(CObject* obj, auto visitor) {
		member_variable_info ProtectedUint_info_144;
		ProtectedUint_info_144.Name = "ProtectedUint";
		ProtectedUint_info_144.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_144.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_144.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_144.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_144.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_144.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_144.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_144.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		visitor(ProtectedUint_info_144, ((access_helper*)obj)->GetProtectedUintRef());
		member_variable_info PublicShort_info_159;
		PublicShort_info_159.Name = "PublicShort";
		PublicShort_info_159.FullName = "CObject::PublicShort";
		PublicShort_info_159.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_159.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_159.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_159.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_159.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_159.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_159.Attributes = {
			{ "serialize", "" }
			};
		visitor(PublicShort_info_159, ((access_helper*)obj)->GetPublicShortRef());
		member_variable_info PublicCharArray_info_172;
		PublicCharArray_info_172.Name = "PublicCharArray";
		PublicCharArray_info_172.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_172.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_172.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_172.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_172.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_172.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_172.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_172.Attributes = {
			{ "serialize", "" }
			};
		visitor(PublicCharArray_info_172, ((access_helper*)obj)->GetPublicCharArrayRef());
	}

	static void for_each_var(const CObject* obj, auto visitor) {
		member_variable_info ProtectedUint_info_188;
		ProtectedUint_info_188.Name = "ProtectedUint";
		ProtectedUint_info_188.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_188.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_188.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_188.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_188.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_188.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_188.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		ProtectedUint_info_188.Attributes = {
			{ "min", "3" },
			{ "max", "15" },
			{ "serialize", "" }
			};
		visitor(ProtectedUint_info_188, ((access_helper*)obj)->GetProtectedUintRef());
		member_variable_info PublicShort_info_203;
		PublicShort_info_203.Name = "PublicShort";
		PublicShort_info_203.FullName = "CObject::PublicShort";
		PublicShort_info_203.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_203.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_203.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_203.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_203.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_203.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		PublicShort_info_203.Attributes = {
			{ "serialize", "" }
			};
		visitor(PublicShort_info_203, ((access_helper*)obj)->GetPublicShortRef());
		member_variable_info PublicCharArray_info_216;
		PublicCharArray_info_216.Name = "PublicCharArray";
		PublicCharArray_info_216.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_216.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_216.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_216.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_216.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_216.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_216.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		PublicCharArray_info_216.Attributes = {
			{ "serialize", "" }
			};
		visitor(PublicCharArray_info_216, ((access_helper*)obj)->GetPublicCharArrayRef());
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

	static void for_each_function(auto fn) {
		member_function_info<decltype(&CObject::Func)> Func_info_273;
		Func_info_273.Name = "Func";
		Func_info_273.Declaration = "void ()";
		Func_info_273.Attributes = {
				{ "callable", "" }
				};
		Func_info_273.ReturnType = "void";
		Func_info_273.Function = &CObject::Func;
		//parameters
		{
		}
		fn(infoName);
		member_function_info<decltype(&CObject::Add)> Add_info_285;
		Add_info_285.Name = "Add";
		Add_info_285.Declaration = "float (float, double)";
		Add_info_285.Attributes = {
				{ "callable", "" }
				};
		Add_info_285.ReturnType = "float";
		Add_info_285.Function = &CObject::Add;
		//parameters
		{
			function_parameter_info A_info_295;
			A_info_295.Name = "A";
			A_info_295.Type = "float";
			A_info_295.DefaultValue = "";
			A_info_295.Attributes = {};
			Add_info_285.Parameters.push_back(A_info_295);
			function_parameter_info B_info_301;
			B_info_301.Name = "B";
			B_info_301.Type = "double";
			B_info_301.DefaultValue = "";
			B_info_301.Attributes = {};
			Add_info_285.Parameters.push_back(B_info_301);
		}
		fn(infoName);
		member_function_info<decltype(&CObject::Get)> Get_info_309;
		Get_info_309.Name = "Get";
		Get_info_309.Declaration = "short () const";
		Get_info_309.Attributes = {
				{ "pure", "" }
				};
		Get_info_309.ReturnType = "short";
		Get_info_309.Function = &CObject::Get;
		//parameters
		{
		}
		fn(infoName);
	}

	static auto get_function_by_name(std::string_view name) {
		member_function_info<void> result = {};
		for_each_function([&](const auto& fn) {
			if (fn.Name == name) result = fn; 
		});
		return result;
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
		{ "pure", "" },
		{ "serialize", "" }
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
		pycppgen<CObject>::for_each_parent(fn);
		struct type_CObject { using type = CObject; const type* obj = nullptr; };
		fn(type_CObject());
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		pycppgen<CObject>::for_each_var(fn);

		member_variable_info Matrix_info_35;
		Matrix_info_35.Name = "Matrix";
		Matrix_info_35.FullName = "CChild::Matrix";
		Matrix_info_35.Type = access_helper().Matrix_TypeName;
		Matrix_info_35.Offset = access_helper().Matrix_Offset;
		Matrix_info_35.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_35.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_35.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_35.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_35.Attributes = {
			{ "serialize", "" }
			};
		fn(Matrix_info_35);

	}

	static void for_each_var_typed(auto fn) {
		pycppgen<CObject>::for_each_var_typed(fn);

		member_variable_info Matrix_info_54;
		Matrix_info_54.Name = "Matrix";
		Matrix_info_54.FullName = "CChild::Matrix";
		Matrix_info_54.Type = access_helper().Matrix_TypeName;
		Matrix_info_54.Offset = access_helper().Matrix_Offset;
		Matrix_info_54.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_54.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_54.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_54.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_54.Attributes = {
			{ "serialize", "" }
			};
		fn(Matrix_info_54, access_helper().GetMatrixRef());

	}

	static void for_each_var(CChild* obj, auto visitor) {
		pycppgen<CObject>::for_each_var(obj, visitor);

		member_variable_info Matrix_info_73;
		Matrix_info_73.Name = "Matrix";
		Matrix_info_73.FullName = "CChild::Matrix";
		Matrix_info_73.Type = access_helper().Matrix_TypeName;
		Matrix_info_73.Offset = access_helper().Matrix_Offset;
		Matrix_info_73.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_73.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_73.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_73.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_73.Attributes = {
			{ "serialize", "" }
			};
		visitor(Matrix_info_73, ((access_helper*)obj)->GetMatrixRef());
	}

	static void for_each_var(const CChild* obj, auto visitor) {
		pycppgen<CObject>::for_each_var(obj, visitor);

		member_variable_info Matrix_info_91;
		Matrix_info_91.Name = "Matrix";
		Matrix_info_91.FullName = "CChild::Matrix";
		Matrix_info_91.Type = access_helper().Matrix_TypeName;
		Matrix_info_91.Offset = access_helper().Matrix_Offset;
		Matrix_info_91.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_91.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_91.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_91.ArrayExtents = access_helper().Matrix_ArrayExtents;
		Matrix_info_91.Attributes = {
			{ "serialize", "" }
			};
		visitor(Matrix_info_91, ((access_helper*)obj)->GetMatrixRef());
	}

	static std::map<std::string, std::string> get_member_attributes(std::string_view name) {
		if (name == "Matrix")
		{
			return {
				{ "serialize", "" }
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

	template<typename T> static bool dump(T& result, const CChild* object) {
		pycppgen<CObject>::dump(result, object);
		result["Matrix"] = ((access_helper*)object)->GetMatrix();
		return true;
	}

	template<typename T, typename R> static bool parse(const T& data, R* object) {
		pycppgen<CObject>::parse(data, object);
		((access_helper*)object)->SetMatrix(data["Matrix"]);
		return true;
	}

	static void for_each_function(auto fn) {
		pycppgen<CObject>::for_each_function(fn);
		member_function_info<decltype(&CChild::DoSomething)> DoSomething_info_139;
		DoSomething_info_139.Name = "DoSomething";
		DoSomething_info_139.Declaration = "void ()";
		DoSomething_info_139.Attributes = {

				};
		DoSomething_info_139.ReturnType = "void";
		DoSomething_info_139.Function = &CChild::DoSomething;
		//parameters
		{
		}
		fn(infoName);
	}

	static auto get_function_by_name(std::string_view name) {
		member_function_info<void> result = {};
		for_each_function([&](const auto& fn) {
			if (fn.Name == name) result = fn; 
		});
		return result;
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
