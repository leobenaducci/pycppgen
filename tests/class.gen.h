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
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
	}
	static bool call_function(std::string_view name) {
		if (name == "OnRegister") {
			CObject::SSubObject::OnRegister();
			return true;
		}
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
		member_variable_info ProtectedUint_info_85;
		ProtectedUint_info_85.Name = "ProtectedUint";
		ProtectedUint_info_85.Type = typeid(unsigned int).name();
		ProtectedUint_info_85.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_85.ElementSize = sizeof(std::remove_all_extents_t<unsigned int>);
		ProtectedUint_info_85.TotalSize = sizeof(unsigned int);
		ProtectedUint_info_85.ArrayRank = std::rank_v<unsigned int>;
		ProtectedUint_info_85.Attributes = {
			{ "pure", "" }
		};
		fn(ProtectedUint_info_85);

		member_variable_info PublicShort_info_97;
		PublicShort_info_97.Name = "PublicShort";
		PublicShort_info_97.Type = typeid(short).name();
		PublicShort_info_97.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_97.ElementSize = sizeof(std::remove_all_extents_t<short>);
		PublicShort_info_97.TotalSize = sizeof(short);
		PublicShort_info_97.ArrayRank = std::rank_v<short>;
		PublicShort_info_97.Attributes = {
			{ "pure", "" }
		};
		fn(PublicShort_info_97);

		member_variable_info PublicCharArray_info_109;
		PublicCharArray_info_109.Name = "PublicCharArray";
		PublicCharArray_info_109.Type = typeid(char[16]).name();
		PublicCharArray_info_109.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_109.ElementSize = sizeof(std::remove_all_extents_t<char[16]>);
		PublicCharArray_info_109.TotalSize = sizeof(char[16]);
		PublicCharArray_info_109.ArrayRank = std::rank_v<char[16]>;
		PublicCharArray_info_109.ArrayExtents.push_back(std::extent_v<char[16], 0>);
		PublicCharArray_info_109.Attributes = {
			{ "pure", "" }
		};
		fn(PublicCharArray_info_109);

	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
		member_function_info Func_info_126;
		Func_info_126.Name = "Func";
		Func_info_126.Declaration = "void ()";
		Func_info_126.Attributes = {};
		Func_info_126.ReturnType = "void";
		//parameters
		{
		}
		member_function_info Add_info_134;
		Add_info_134.Name = "Add";
		Add_info_134.Declaration = "float (float, double)";
		Add_info_134.Attributes = {
				{ "callable", "" }
			};
		Add_info_134.ReturnType = "float";
		//parameters
		{
			function_parameter_info A_info_143;
			A_info_143.Name = "A";
			A_info_143.Type = "float";
			A_info_143.DefaultValue = "";
			A_info_143.Attributes = {
				{ "clamp", "" }
			};
			Add_info_134.Parameters.push_back(A_info_143);
			function_parameter_info B_info_151;
			B_info_151.Name = "B";
			B_info_151.Type = "double";
			B_info_151.DefaultValue = "";
			B_info_151.Attributes = {
				{ "auto_cast", "" },
				{ "enum", "" }
			};
			Add_info_134.Parameters.push_back(B_info_151);
		}
		member_function_info Sub_info_161;
		Sub_info_161.Name = "Sub";
		Sub_info_161.Declaration = "float (float, double)";
		Sub_info_161.Attributes = {
				{ "callable", "" }
			};
		Sub_info_161.ReturnType = "float";
		//parameters
		{
			function_parameter_info A_info_170;
			A_info_170.Name = "A";
			A_info_170.Type = "float";
			A_info_170.DefaultValue = "";
			A_info_170.Attributes = {};
			Sub_info_161.Parameters.push_back(A_info_170);
			function_parameter_info B_info_176;
			B_info_176.Name = "B";
			B_info_176.Type = "double";
			B_info_176.DefaultValue = "";
			B_info_176.Attributes = {};
			Sub_info_161.Parameters.push_back(B_info_176);
		}
		member_function_info Get_info_183;
		Get_info_183.Name = "Get";
		Get_info_183.Declaration = "short () const";
		Get_info_183.Attributes = {
				{ "readonly", "" }
			};
		Get_info_183.ReturnType = "short";
		//parameters
		{
		}
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
		if (name == "Sub") {
			result = object->Sub( _1,  _2);
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
struct pycppgen<CChild>{
	std::map<std::string_view, std::string_view> Attributes = {
		{ "pure", "" }
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		struct access_helper : CChild {
			const size_t Matrix_Offset = offsetof(access_helper, CChild::Matrix);
		};
		member_variable_info Matrix_info_253;
		Matrix_info_253.Name = "Matrix";
		Matrix_info_253.Type = typeid(float[4][4]).name();
		Matrix_info_253.Offset = access_helper().Matrix_Offset;
		Matrix_info_253.ElementSize = sizeof(std::remove_all_extents_t<float[4][4]>);
		Matrix_info_253.TotalSize = sizeof(float[4][4]);
		Matrix_info_253.ArrayRank = std::rank_v<float[4][4]>;
		Matrix_info_253.ArrayExtents.push_back(std::extent_v<float[4][4], 0>);
		Matrix_info_253.ArrayExtents.push_back(std::extent_v<float[4][4], 1>);
		Matrix_info_253.Attributes = {
			{ "pure", "" }
		};
		fn(Matrix_info_253);

	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
	}
};

#endif //pycppgen_CChild
//</autogen_pycppgen_CChild>

namespace pycppgen_globals {
}
