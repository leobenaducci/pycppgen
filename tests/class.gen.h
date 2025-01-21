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

#endif //_PYCPPGEN_DECLARATIONS

#ifndef pycppgen_CObject
#define pycppgen_CObject

template<>
struct pycppgen<CObject>{
	static std::map<std::string_view, std::string_view> Attributes = {
		{ "pure", "" }
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		struct access_helper : CObject {
			const size_t ProtectedUint_Offset = offsetof(access_helper, CObject::ProtectedUint);
			const size_t PublicShort_Offset = offsetof(access_helper, CObject::PublicShort);
			const size_t PublicCharArray_Offset = offsetof(access_helper, CObject::PublicCharArray);
		};
		member_variable_info ProtectedUint_info_52;
		ProtectedUint_info_52.Name = "ProtectedUint";
		ProtectedUint_info_52.Type = typeid(unsigned int).name();
		ProtectedUint_info_52.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info_52.ElementSize = sizeof(std::remove_all_extents_t<unsigned int>);
		ProtectedUint_info_52.TotalSize = sizeof(unsigned int);
		ProtectedUint_info_52.ArrayRank = std::rank_v<unsigned int>;
		ProtectedUint_info_52.Attributes = {
			{ "pure", "" }
		};
		fn(ProtectedUint_info_52);

		member_variable_info PublicShort_info_64;
		PublicShort_info_64.Name = "PublicShort";
		PublicShort_info_64.Type = typeid(short).name();
		PublicShort_info_64.Offset = access_helper().PublicShort_Offset;
		PublicShort_info_64.ElementSize = sizeof(std::remove_all_extents_t<short>);
		PublicShort_info_64.TotalSize = sizeof(short);
		PublicShort_info_64.ArrayRank = std::rank_v<short>;
		PublicShort_info_64.Attributes = {
			{ "pure", "" }
		};
		fn(PublicShort_info_64);

		member_variable_info PublicCharArray_info_76;
		PublicCharArray_info_76.Name = "PublicCharArray";
		PublicCharArray_info_76.Type = typeid(char[16]).name();
		PublicCharArray_info_76.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info_76.ElementSize = sizeof(std::remove_all_extents_t<char[16]>);
		PublicCharArray_info_76.TotalSize = sizeof(char[16]);
		PublicCharArray_info_76.ArrayRank = std::rank_v<char[16]>;
		PublicCharArray_info_76.ArrayExtents.push_back(std::extent_v<char[16], 0>);
		PublicCharArray_info_76.Attributes = {
			{ "pure", "" }
		};
		fn(PublicCharArray_info_76);

	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
		member_function_info Func_info_91;
		Func_info_91.Name = "Func";
		Func_info_91.Declaration = "void ()";
		Func_info_91.Attributes = {
				{ "callable", "" }
			};
		Func_info_91.ReturnType = "void";
		//parameters
		{
		}
		member_function_info Add_info_101;
		Add_info_101.Name = "Add";
		Add_info_101.Declaration = "float (float, double)";
		Add_info_101.Attributes = {
				{ "callable", "" }
			};
		Add_info_101.ReturnType = "float";
		//parameters
		{
			function_parameter_info A_info_110;
			A_info_110.Name = "A";
			A_info_110.Type = "float";
			A_info_110.DefaultValue = "";
			A_info_110.Attributes = {
				{ "clamp", "" }
			};
			Add_info_101.Parameters.push_back(A_info_110);
			function_parameter_info B_info_118;
			B_info_118.Name = "B";
			B_info_118.Type = "double";
			B_info_118.DefaultValue = "";
			B_info_118.Attributes = {
				{ "auto_cast", "" },
				{ "enum", "" }
			};
			Add_info_101.Parameters.push_back(B_info_118);
		}
		member_function_info Sub_info_128;
		Sub_info_128.Name = "Sub";
		Sub_info_128.Declaration = "float (float, double)";
		Sub_info_128.Attributes = {
				{ "callable", "" }
			};
		Sub_info_128.ReturnType = "float";
		//parameters
		{
			function_parameter_info A_info_137;
			A_info_137.Name = "A";
			A_info_137.Type = "float";
			A_info_137.DefaultValue = "";
			A_info_137.Attributes = {};
			Sub_info_128.Parameters.push_back(A_info_137);
			function_parameter_info B_info_143;
			B_info_143.Name = "B";
			B_info_143.Type = "double";
			B_info_143.DefaultValue = "";
			B_info_143.Attributes = {};
			Sub_info_128.Parameters.push_back(B_info_143);
		}
		member_function_info Get_info_150;
		Get_info_150.Name = "Get";
		Get_info_150.Declaration = "short () const";
		Get_info_150.Attributes = {
				{ "readonly", "" }
			};
		Get_info_150.ReturnType = "short";
		//parameters
		{
		}
	}
	static void call_function(std::string_view name, CObject* object) {
		if (name == "Func") {
			object->Func();
			return;
		}
		__debugbreak();
	}
	static void call_function(std::string_view name, CObject* object, float& result, float _1, double _2) {
		if (name == "Add") {
			result = object->Add( _1,  _2);
			return;
		}
		if (name == "Sub") {
			result = object->Sub( _1,  _2);
			return;
		}
		__debugbreak();
	}
	static void call_function(std::string_view name, const CObject* object, short& result) {
		if (name == "Get") {
			result = object->Get();
			return;
		}
		__debugbreak();
	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	static void call_function(std::string_view name, int& result) {
		if (name == "TestStaticFunc") {
			result = CObject::TestStaticFunc();
			return;
		}
		__debugbreak();
	}
	}
};

#endif //pycppgen_CObject
#ifndef pycppgen_CChild
#define pycppgen_CChild

template<>
struct pycppgen<CChild>{
	static std::map<std::string_view, std::string_view> Attributes = {
		{ "pure", "" }
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		struct access_helper : CChild {
			const size_t Matrix_Offset = offsetof(access_helper, CChild::Matrix);
		};
		member_variable_info Matrix_info_212;
		Matrix_info_212.Name = "Matrix";
		Matrix_info_212.Type = typeid(float[4][4]).name();
		Matrix_info_212.Offset = access_helper().Matrix_Offset;
		Matrix_info_212.ElementSize = sizeof(std::remove_all_extents_t<float[4][4]>);
		Matrix_info_212.TotalSize = sizeof(float[4][4]);
		Matrix_info_212.ArrayRank = std::rank_v<float[4][4]>;
		Matrix_info_212.ArrayExtents.push_back(std::extent_v<float[4][4], 0>);
		Matrix_info_212.ArrayExtents.push_back(std::extent_v<float[4][4], 1>);
		Matrix_info_212.Attributes = {
			{ "pure", "" }
		};
		fn(Matrix_info_212);

	}
	static void for_each_function(std::function<void(const member_function_info&)> fn) {
	}
	static void for_each_static_var(std::function<void(std::string_view name)> fn) {
	}
	}
};

#endif //pycppgen_CChild
namespace pycppgen_globals {
}
