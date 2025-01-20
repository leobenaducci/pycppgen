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

template<typename T> struct meta {};

#endif //_PYCPPGEN_DECLARATIONS

template<>
struct meta<CObject>{
	std::map<std::string, std::string> Attributes = {
		{ "pure", "" }
	};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		struct access_helper : CObject {
			const size_t ProtectedUint_Offset = offsetof(access_helper, CObject::ProtectedUint);
			const size_t PublicShort_Offset = offsetof(access_helper, CObject::PublicShort);
			const size_t PublicCharArray_Offset = offsetof(access_helper, CObject::PublicCharArray);
		};
		member_variable_info ProtectedUint_info;
		ProtectedUint_info.Name = "ProtectedUint";
		ProtectedUint_info.Type = typeid(unsigned int).name();
		ProtectedUint_info.Offset = access_helper().ProtectedUint_Offset;
		ProtectedUint_info.ElementSize = sizeof(std::remove_all_extents_t<unsigned int>);
		ProtectedUint_info.TotalSize = sizeof(unsigned int);
		ProtectedUint_info.ArrayRank = std::rank_v<unsigned int>;
		ProtectedUint_info.Attributes = {
			{ "pure", "" }
		};

		fn(ProtectedUint_info);
		member_variable_info PublicShort_info;
		PublicShort_info.Name = "PublicShort";
		PublicShort_info.Type = typeid(short).name();
		PublicShort_info.Offset = access_helper().PublicShort_Offset;
		PublicShort_info.ElementSize = sizeof(std::remove_all_extents_t<short>);
		PublicShort_info.TotalSize = sizeof(short);
		PublicShort_info.ArrayRank = std::rank_v<short>;
		PublicShort_info.Attributes = {
			{ "pure", "" }
		};

		fn(PublicShort_info);
		member_variable_info PublicCharArray_info;
		PublicCharArray_info.Name = "PublicCharArray";
		PublicCharArray_info.Type = typeid(char[16]).name();
		PublicCharArray_info.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info.ElementSize = sizeof(std::remove_all_extents_t<char[16]>);
		PublicCharArray_info.TotalSize = sizeof(char[16]);
		PublicCharArray_info.ArrayRank = std::rank_v<char[16]>;
		PublicCharArray_info.ArrayExtents.push_back(std::extent_v<char[16], 0>);
		PublicCharArray_info.Attributes = {
			{ "pure", "" }
		};

		fn(PublicCharArray_info);
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
};

template<>
struct meta<CChild>{
	std::map<std::string, std::string> Attributes = {};

	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		struct access_helper : CChild {
			const size_t Matrix_Offset = offsetof(access_helper, CChild::Matrix);
		};
		member_variable_info Matrix_info;
		Matrix_info.Name = "Matrix";
		Matrix_info.Type = typeid(float[4][4]).name();
		Matrix_info.Offset = access_helper().Matrix_Offset;
		Matrix_info.ElementSize = sizeof(std::remove_all_extents_t<float[4][4]>);
		Matrix_info.TotalSize = sizeof(float[4][4]);
		Matrix_info.ArrayRank = std::rank_v<float[4][4]>;
		Matrix_info.ArrayExtents.push_back(std::extent_v<float[4][4], 0>);
		Matrix_info.ArrayExtents.push_back(std::extent_v<float[4][4], 1>);
		Matrix_info.Attributes = {};

		fn(Matrix_info);
	}
};

