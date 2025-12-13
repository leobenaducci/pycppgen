#pragma once


#ifndef __STESTSHADERDATA_DECL__
#define __STESTSHADERDATA_DECL__

#ifdef __cplusplus


struct STestShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};

template<> struct pyhlslgen<STestShaderData>
{
    using type_t = STestShaderData;
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool cbuffer_alignment = true;
    static constexpr char type_name[] = "STestShaderData"; 
    static constexpr char struct_decl[] = R"-(
#ifndef __STESTSHADERDATA_DECL__
#define __STESTSHADERDATA_DECL__


struct STestShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};


#endif //__STESTSHADERDATA_DECL__
)-"; 
    static constexpr char cbuffer_decl[] = R"-(
cbuffer STestShaderData_
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};
)-";
};

#else

struct STestShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};

#endif //__cplusplus
#endif //__STESTSHADERDATA_DECL__

#ifndef __SNAMESPACEDSHADERDATA_DECL__
#define __SNAMESPACEDSHADERDATA_DECL__

#ifdef __cplusplus
namespace vkfw {


struct SNamespacedShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};

template<> struct pyhlslgen<SNamespacedShaderData>
{
    using type_t = SNamespacedShaderData;
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool cbuffer_alignment = true;
    static constexpr char type_name[] = "SNamespacedShaderData"; 
    static constexpr char struct_decl[] = R"-(
#ifndef __SNAMESPACEDSHADERDATA_DECL__
#define __SNAMESPACEDSHADERDATA_DECL__


struct SNamespacedShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};


#endif //__SNAMESPACEDSHADERDATA_DECL__
)-"; 
    static constexpr char cbuffer_decl[] = R"-(
cbuffer SNamespacedShaderData_
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};
)-";
};
}

#else

struct SNamespacedShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};

#endif //__cplusplus
#endif //__SNAMESPACEDSHADERDATA_DECL__

#ifndef __SSTRUCTBASE_SSHADERDATA_DECL__
#define __SSTRUCTBASE_SSHADERDATA_DECL__

#ifdef __cplusplus


struct SStructBase_SShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};

template<> struct pyhlslgen<SStructBase_SShaderData>
{
    using type_t = SStructBase_SShaderData;
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool cbuffer_alignment = true;
    static constexpr char type_name[] = "SStructBase_SShaderData"; 
    static constexpr char struct_decl[] = R"-(
#ifndef __SSTRUCTBASE_SSHADERDATA_DECL__
#define __SSTRUCTBASE_SSHADERDATA_DECL__


struct SStructBase_SShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};


#endif //__SSTRUCTBASE_SSHADERDATA_DECL__
)-"; 
    static constexpr char cbuffer_decl[] = R"-(
cbuffer SStructBase_SShaderData_
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};
)-";
};

#else

struct SStructBase_SShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};

#endif //__cplusplus
#endif //__SSTRUCTBASE_SSHADERDATA_DECL__

#ifndef __SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__
#define __SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__

#ifdef __cplusplus
namespace vkfw {


struct SStructTest_SShaderStructTestData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};

template<> struct pyhlslgen<SStructTest_SShaderStructTestData>
{
    using type_t = SStructTest_SShaderStructTestData;
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool cbuffer_alignment = true;
    static constexpr char type_name[] = "SStructTest_SShaderStructTestData"; 
    static constexpr char struct_decl[] = R"-(
#ifndef __SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__
#define __SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__


struct SStructTest_SShaderStructTestData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};


#endif //__SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__
)-"; 
    static constexpr char cbuffer_decl[] = R"-(
cbuffer SStructTest_SShaderStructTestData_
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};
)-";
};
}

#else

struct SStructTest_SShaderStructTestData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};

#endif //__cplusplus
#endif //__SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__
