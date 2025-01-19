#include "namespace.h"

#ifndef _PYCPPGEN_DECLARATIONS
#define _PYCPPGEN_DECLARATIONS

struct member_variable_info {
	std::string_view Name;
	std::string_view Type;
	size_t Offset = 0;
	size_t Size = 0;
	size_t ArrayLength = 0;
};

template<typename T> struct meta {};

#endif //_PYCPPGEN_DECLARATIONS

template<>
struct meta<CObject>{
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
		ProtectedUint_info.Size = sizeof(unsigned int);
		fn(ProtectedUint_info);
		member_variable_info PublicShort_info;
		PublicShort_info.Name = "PublicShort";
		PublicShort_info.Type = typeid(short).name();
		PublicShort_info.Offset = access_helper().PublicShort_Offset;
		PublicShort_info.Size = sizeof(short);
		fn(PublicShort_info);
		member_variable_info PublicCharArray_info;
		PublicCharArray_info.Name = "PublicCharArray";
		PublicCharArray_info.Type = typeid(char[16]).name();
		PublicCharArray_info.Offset = access_helper().PublicCharArray_Offset;
		PublicCharArray_info.Size = sizeof(char[16]);
		fn(PublicCharArray_info);
	}
};

template<>
struct meta<CChild>{
	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		struct access_helper : CChild {
			const size_t Matrix_Offset = offsetof(access_helper, CChild::Matrix);
		};
		member_variable_info Matrix_info;
		Matrix_info.Name = "Matrix";
		Matrix_info.Type = typeid(float[4][4]).name();
		Matrix_info.Offset = access_helper().Matrix_Offset;
		Matrix_info.Size = sizeof(float[4][4]);
		fn(Matrix_info);
	}
};

template<>
struct meta<TestNameSpace::CChild>{
	static void for_each_var(std::function<void(const member_variable_info&)> fn) {
		struct access_helper : TestNameSpace::CChild {
			const size_t Matrix_Offset = offsetof(access_helper, TestNameSpace::CChild::Matrix);
		};
		member_variable_info Matrix_info;
		Matrix_info.Name = "Matrix";
		Matrix_info.Type = typeid(float[4][4]).name();
		Matrix_info.Offset = access_helper().Matrix_Offset;
		Matrix_info.Size = sizeof(float[4][4]);
		fn(Matrix_info);
	}
};

