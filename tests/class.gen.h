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

	static std::map<std::string, std::string> get_var_attributes(std::string_view name) {
		std::map<std::string, std::string> result;
		return result;
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

	static bool find_function_by_name(std::string_view name, auto fn) {
		bool result = false;
		for_each_function([&](const auto& info) {
			if (info.Name == name) { result = true; fn(info); } 
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
		fn(ProtectedUint_info_50);

		member_variable_info PublicShort_info_61;
		PublicShort_info_61.Name = "PublicShort";
		PublicShort_info_61.FullName = "CObject::PublicShort";
		PublicShort_info_61.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_61.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_61.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_61.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_61.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_61.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		fn(PublicShort_info_61);

		member_variable_info PublicCharArray_info_72;
		PublicCharArray_info_72.Name = "PublicCharArray";
		PublicCharArray_info_72.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_72.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_72.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_72.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_72.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_72.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_72.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		fn(PublicCharArray_info_72);

	}

	static void for_each_var_typed(auto fn) {
		member_variable_info ProtectedUint_info_86;
		ProtectedUint_info_86.Name = "ProtectedUint";
		ProtectedUint_info_86.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_86.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_86.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_86.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_86.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_86.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_86.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		fn(ProtectedUint_info_86, access_helper().GetProtectedUintRef());

		member_variable_info PublicShort_info_97;
		PublicShort_info_97.Name = "PublicShort";
		PublicShort_info_97.FullName = "CObject::PublicShort";
		PublicShort_info_97.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_97.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_97.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_97.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_97.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_97.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		fn(PublicShort_info_97, access_helper().GetPublicShortRef());

		member_variable_info PublicCharArray_info_108;
		PublicCharArray_info_108.Name = "PublicCharArray";
		PublicCharArray_info_108.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_108.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_108.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_108.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_108.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_108.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_108.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		fn(PublicCharArray_info_108, access_helper().GetPublicCharArrayRef());

	}

	static void for_each_var(CObject* obj, auto visitor) {
		member_variable_info ProtectedUint_info_122;
		ProtectedUint_info_122.Name = "ProtectedUint";
		ProtectedUint_info_122.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_122.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_122.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_122.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_122.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_122.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_122.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		visitor(ProtectedUint_info_122, ((access_helper*)obj)->GetProtectedUintRef());
		member_variable_info PublicShort_info_132;
		PublicShort_info_132.Name = "PublicShort";
		PublicShort_info_132.FullName = "CObject::PublicShort";
		PublicShort_info_132.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_132.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_132.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_132.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_132.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_132.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		visitor(PublicShort_info_132, ((access_helper*)obj)->GetPublicShortRef());
		member_variable_info PublicCharArray_info_142;
		PublicCharArray_info_142.Name = "PublicCharArray";
		PublicCharArray_info_142.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_142.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_142.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_142.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_142.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_142.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_142.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		visitor(PublicCharArray_info_142, ((access_helper*)obj)->GetPublicCharArrayRef());
	}

	static void for_each_var(const CObject* obj, auto visitor) {
		member_variable_info ProtectedUint_info_155;
		ProtectedUint_info_155.Name = "ProtectedUint";
		ProtectedUint_info_155.FullName = "CObject::ProtectedUint";
		ProtectedUint_info_155.Type = access_helper().ProtectedUint_TypeName;
		ProtectedUint_info_155.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_155.ElementSize = access_helper().ProtectedUint_ElementSize;
		ProtectedUint_info_155.TotalSize = access_helper().ProtectedUint_TotalSize;
		ProtectedUint_info_155.ArrayRank = access_helper().ProtectedUint_ArrayRank;
		ProtectedUint_info_155.ArrayExtents = access_helper().ProtectedUint_ArrayExtents;
		visitor(ProtectedUint_info_155, ((access_helper*)obj)->GetProtectedUintRef());
		member_variable_info PublicShort_info_165;
		PublicShort_info_165.Name = "PublicShort";
		PublicShort_info_165.FullName = "CObject::PublicShort";
		PublicShort_info_165.Type = access_helper().PublicShort_TypeName;
		PublicShort_info_165.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_165.ElementSize = access_helper().PublicShort_ElementSize;
		PublicShort_info_165.TotalSize = access_helper().PublicShort_TotalSize;
		PublicShort_info_165.ArrayRank = access_helper().PublicShort_ArrayRank;
		PublicShort_info_165.ArrayExtents = access_helper().PublicShort_ArrayExtents;
		visitor(PublicShort_info_165, ((access_helper*)obj)->GetPublicShortRef());
		member_variable_info PublicCharArray_info_175;
		PublicCharArray_info_175.Name = "PublicCharArray";
		PublicCharArray_info_175.FullName = "CObject::PublicCharArray";
		PublicCharArray_info_175.Type = access_helper().PublicCharArray_TypeName;
		PublicCharArray_info_175.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_175.ElementSize = access_helper().PublicCharArray_ElementSize;
		PublicCharArray_info_175.TotalSize = access_helper().PublicCharArray_TotalSize;
		PublicCharArray_info_175.ArrayRank = access_helper().PublicCharArray_ArrayRank;
		PublicCharArray_info_175.ArrayExtents = access_helper().PublicCharArray_ArrayExtents;
		visitor(PublicCharArray_info_175, ((access_helper*)obj)->GetPublicCharArrayRef());
	}

	static std::map<std::string, std::string> get_var_attributes(std::string_view name) {
		std::map<std::string, std::string> result;
		if (name == "ProtectedUint")
			 result = {
				{ "min", "3" },
				{ "max", "15" },
				{ "serialize", "" }
				};
		if (name == "PublicShort")
			 result = {
				{ "serialize", "" }
				};
		if (name == "PublicCharArray")
			 result = {
				{ "serialize", "" }
				};
		return result;
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
		member_function_info<decltype(&CObject::Func)> Func_info_224;
		Func_info_224.Name = "Func";
		Func_info_224.Declaration = "void ()";
		Func_info_224.Attributes = {
				{ "callable", "" }
				};
		Func_info_224.ReturnType = "void";
		Func_info_224.Function = &CObject::Func;
		//parameters
		{
		}
		fn(Func_info_224);
		member_function_info<decltype(&CObject::Add)> Add_info_236;
		Add_info_236.Name = "Add";
		Add_info_236.Declaration = "float (float, double)";
		Add_info_236.Attributes = {
				{ "callable", "" }
				};
		Add_info_236.ReturnType = "float";
		Add_info_236.Function = &CObject::Add;
		//parameters
		{
			function_parameter_info A_info_246;
			A_info_246.Name = "A";
			A_info_246.Type = "float";
			A_info_246.DefaultValue = "";
			A_info_246.Attributes = {};
			Add_info_236.Parameters.push_back(A_info_246);
			function_parameter_info B_info_252;
			B_info_252.Name = "B";
			B_info_252.Type = "double";
			B_info_252.DefaultValue = "";
			B_info_252.Attributes = {};
			Add_info_236.Parameters.push_back(B_info_252);
		}
		fn(Add_info_236);
		member_function_info<decltype(&CObject::Get)> Get_info_260;
		Get_info_260.Name = "Get";
		Get_info_260.Declaration = "short () const";
		Get_info_260.Attributes = {
				{ "pure", "" }
				};
		Get_info_260.ReturnType = "short";
		Get_info_260.Function = &CObject::Get;
		//parameters
		{
		}
		fn(Get_info_260);
	}

	static bool find_function_by_name(std::string_view name, auto fn) {
		bool result = false;
		for_each_function([&](const auto& info) {
			if (info.Name == name) { result = true; fn(info); } 
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
		fn(Matrix_info_35);

	}

	static void for_each_var_typed(auto fn) {
		pycppgen<CObject>::for_each_var_typed(fn);

		member_variable_info Matrix_info_51;
		Matrix_info_51.Name = "Matrix";
		Matrix_info_51.FullName = "CChild::Matrix";
		Matrix_info_51.Type = access_helper().Matrix_TypeName;
		Matrix_info_51.Offset = access_helper().Matrix_Offset;
		Matrix_info_51.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_51.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_51.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_51.ArrayExtents = access_helper().Matrix_ArrayExtents;
		fn(Matrix_info_51, access_helper().GetMatrixRef());

	}

	static void for_each_var(CChild* obj, auto visitor) {
		pycppgen<CObject>::for_each_var(obj, visitor);

		member_variable_info Matrix_info_67;
		Matrix_info_67.Name = "Matrix";
		Matrix_info_67.FullName = "CChild::Matrix";
		Matrix_info_67.Type = access_helper().Matrix_TypeName;
		Matrix_info_67.Offset = access_helper().Matrix_Offset;
		Matrix_info_67.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_67.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_67.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_67.ArrayExtents = access_helper().Matrix_ArrayExtents;
		visitor(Matrix_info_67, ((access_helper*)obj)->GetMatrixRef());
	}

	static void for_each_var(const CChild* obj, auto visitor) {
		pycppgen<CObject>::for_each_var(obj, visitor);

		member_variable_info Matrix_info_82;
		Matrix_info_82.Name = "Matrix";
		Matrix_info_82.FullName = "CChild::Matrix";
		Matrix_info_82.Type = access_helper().Matrix_TypeName;
		Matrix_info_82.Offset = access_helper().Matrix_Offset;
		Matrix_info_82.ElementSize = access_helper().Matrix_ElementSize;
		Matrix_info_82.TotalSize = access_helper().Matrix_TotalSize;
		Matrix_info_82.ArrayRank = access_helper().Matrix_ArrayRank;
		Matrix_info_82.ArrayExtents = access_helper().Matrix_ArrayExtents;
		visitor(Matrix_info_82, ((access_helper*)obj)->GetMatrixRef());
	}

	static std::map<std::string, std::string> get_var_attributes(std::string_view name) {
		std::map<std::string, std::string> result;
		if (name == "Matrix")
			 result = {
				{ "serialize", "" }
				};

		if (result.empty())
			result = pycppgen<CObject>::get_var_attributes(name);

		//overrides
		if (name == "ProtectedUint")
		{
			result["min"] = "1";
			result["include"] = "True";
		}
		return result;
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
		member_function_info<decltype(&CChild::DoSomething)> DoSomething_info_130;
		DoSomething_info_130.Name = "DoSomething";
		DoSomething_info_130.Declaration = "void ()";
		DoSomething_info_130.Attributes = {

				};
		DoSomething_info_130.ReturnType = "void";
		DoSomething_info_130.Function = &CChild::DoSomething;
		//parameters
		{
		}
		fn(DoSomething_info_130);
	}

	static bool find_function_by_name(std::string_view name, auto fn) {
		bool result = false;
		for_each_function([&](const auto& info) {
			if (info.Name == name) { result = true; fn(info); } 
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
