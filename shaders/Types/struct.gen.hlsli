
////////////////////////////////
//struct.gen.hlsli

#pragma once


#ifndef __UBO_DECL__
#define __UBO_DECL__

#ifdef __cplusplus


struct UBO
{
	float A;							// Offset: 0 - Size: 4
	uint3 _pad0_UBO;					// Offset: 4 - Size: 12
	float4x2 H[16];						// Offset: 16 - Size: 512
	float B;							// Offset: 528 - Size: 4
}; // Size: 532

template<> struct pyhlslgen<UBO>
{
    using type_t = UBO;
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool uniform_alignment = true;
    static constexpr bool relaxed_alignment = false;
    static constexpr bool scalar_alignment = false;
    static constexpr char type_name[] = "UBO"; 
    static constexpr char struct_decl[] = R"-(
#ifndef __UBO_DECL__
#define __UBO_DECL__


struct UBO
{
	float A;							// Offset: 0 - Size: 4
	uint3 _pad0_UBO;					// Offset: 4 - Size: 12
	float4x2 H[16];						// Offset: 16 - Size: 512
	float B;							// Offset: 528 - Size: 4
}; // Size: 532


#endif //__UBO_DECL__
)-"; 
    static constexpr char uniform_decl[] = R"-(
cbuffer UBO_
{
	float A;							// Offset: 0 - Size: 4
	uint3 _pad0_UBO;					// Offset: 4 - Size: 12
	float4x2 H[16];						// Offset: 16 - Size: 512
	float B;							// Offset: 528 - Size: 4
}; // Size: 532
)-";
};

#else

struct UBO
{
	float A;							// Offset: 0 - Size: 4
	uint3 _pad0_UBO;					// Offset: 4 - Size: 12
	float4x2 H[16];						// Offset: 16 - Size: 512
	float B;							// Offset: 528 - Size: 4
}; // Size: 532

#endif //__cplusplus
#endif //__UBO_DECL__

#ifndef __SSBBO_DECL__
#define __SSBBO_DECL__

#ifdef __cplusplus


struct SSBBO
{
	float3 pos;							// Offset: 0 - Size: 12
	float2 scale;						// Offset: 12 - Size: 8
	uint3 _pad0_SSBBO;					// Offset: 20 - Size: 12
}; // Size: 32

template<> struct pyhlslgen<SSBBO>
{
    using type_t = SSBBO;
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool uniform_alignment = false;
    static constexpr bool relaxed_alignment = true;
    static constexpr bool scalar_alignment = false;
    static constexpr char type_name[] = "SSBBO"; 
    static constexpr char struct_decl[] = R"-(
#ifndef __SSBBO_DECL__
#define __SSBBO_DECL__


struct SSBBO
{
	float3 pos;							// Offset: 0 - Size: 12
	float2 scale;						// Offset: 12 - Size: 8
	uint3 _pad0_SSBBO;					// Offset: 20 - Size: 12
}; // Size: 32


#endif //__SSBBO_DECL__
)-"; 
    static constexpr char uniform_decl[] = R"-(
cbuffer SSBBO_
{
	float3 pos;							// Offset: 0 - Size: 12
	float2 scale;						// Offset: 12 - Size: 8
	uint3 _pad0_SSBBO;					// Offset: 20 - Size: 12
}; // Size: 32
)-";
};

#else

struct SSBBO
{
	float3 pos;							// Offset: 0 - Size: 12
	float2 scale;						// Offset: 12 - Size: 8
	uint3 _pad0_SSBBO;					// Offset: 20 - Size: 12
}; // Size: 32

#endif //__cplusplus
#endif //__SSBBO_DECL__

#ifndef __SBUFFER_DECL__
#define __SBUFFER_DECL__

#ifdef __cplusplus


struct SBuffer
{
	float2 pos;							// Offset: 0 - Size: 8
}; // Size: 8

template<> struct pyhlslgen<SBuffer>
{
    using type_t = SBuffer;
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool uniform_alignment = false;
    static constexpr bool relaxed_alignment = false;
    static constexpr bool scalar_alignment = true;
    static constexpr char type_name[] = "SBuffer"; 
    static constexpr char struct_decl[] = R"-(
#ifndef __SBUFFER_DECL__
#define __SBUFFER_DECL__


struct SBuffer
{
	float2 pos;							// Offset: 0 - Size: 8
}; // Size: 8


#endif //__SBUFFER_DECL__
)-"; 
    static constexpr char uniform_decl[] = R"-(
cbuffer SBuffer_
{
	float2 pos;							// Offset: 0 - Size: 8
}; // Size: 8
)-";
};

#else

struct SBuffer
{
	float2 pos;							// Offset: 0 - Size: 8
}; // Size: 8

#endif //__cplusplus
#endif //__SBUFFER_DECL__

#ifndef __STESTSHADERDATA_DECL__
#define __STESTSHADERDATA_DECL__

#ifdef __cplusplus


struct STestShaderData
{
	float A;							// Offset: 0 - Size: 4
	uint3 _pad0_STestShaderData;		// Offset: 4 - Size: 12
	float4x4 H[16];						// Offset: 16 - Size: 1024
	float B;							// Offset: 1040 - Size: 4
}; // Size: 1044

template<> struct pyhlslgen<STestShaderData>
{
    using type_t = STestShaderData;
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool uniform_alignment = true;
    static constexpr bool relaxed_alignment = false;
    static constexpr bool scalar_alignment = false;
    static constexpr char type_name[] = "STestShaderData"; 
    static constexpr char struct_decl[] = R"-(
#ifndef __STESTSHADERDATA_DECL__
#define __STESTSHADERDATA_DECL__


struct STestShaderData
{
	float A;							// Offset: 0 - Size: 4
	uint3 _pad0_STestShaderData;		// Offset: 4 - Size: 12
	float4x4 H[16];						// Offset: 16 - Size: 1024
	float B;							// Offset: 1040 - Size: 4
}; // Size: 1044


#endif //__STESTSHADERDATA_DECL__
)-"; 
    static constexpr char uniform_decl[] = R"-(
cbuffer STestShaderData_
{
	float A;							// Offset: 0 - Size: 4
	uint3 _pad0_STestShaderData;		// Offset: 4 - Size: 12
	float4x4 H[16];						// Offset: 16 - Size: 1024
	float B;							// Offset: 1040 - Size: 4
}; // Size: 1044
)-";
};

#else

struct STestShaderData
{
	float A;							// Offset: 0 - Size: 4
	uint3 _pad0_STestShaderData;		// Offset: 4 - Size: 12
	float4x4 H[16];						// Offset: 16 - Size: 1024
	float B;							// Offset: 1040 - Size: 4
}; // Size: 1044

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
	uint2 _pad0_SNamespacedShaderData;	// Offset: 776 - Size: 8
}; // Size: 784

template<> struct pyhlslgen<SNamespacedShaderData>
{
    using type_t = SNamespacedShaderData;
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool uniform_alignment = false;
    static constexpr bool relaxed_alignment = true;
    static constexpr bool scalar_alignment = false;
    static constexpr char type_name[] = "SNamespacedShaderData"; 
    static constexpr char struct_decl[] = R"-(
#ifndef __SNAMESPACEDSHADERDATA_DECL__
#define __SNAMESPACEDSHADERDATA_DECL__


struct SNamespacedShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4
	uint2 _pad0_SNamespacedShaderData;	// Offset: 776 - Size: 8
}; // Size: 784


#endif //__SNAMESPACEDSHADERDATA_DECL__
)-"; 
    static constexpr char uniform_decl[] = R"-(
cbuffer SNamespacedShaderData_
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4
	uint2 _pad0_SNamespacedShaderData;	// Offset: 776 - Size: 8
}; // Size: 784
)-";
};
}

#else

struct SNamespacedShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4
	uint2 _pad0_SNamespacedShaderData;	// Offset: 776 - Size: 8
}; // Size: 784

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
	uint2 _pad0_SShaderData;			// Offset: 776 - Size: 8
}; // Size: 784

template<> struct pyhlslgen<SStructBase_SShaderData>
{
    using type_t = SStructBase_SShaderData;
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool uniform_alignment = false;
    static constexpr bool relaxed_alignment = true;
    static constexpr bool scalar_alignment = false;
    static constexpr char type_name[] = "SStructBase_SShaderData"; 
    static constexpr char struct_decl[] = R"-(
#ifndef __SSTRUCTBASE_SSHADERDATA_DECL__
#define __SSTRUCTBASE_SSHADERDATA_DECL__


struct SStructBase_SShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4
	uint2 _pad0_SShaderData;			// Offset: 776 - Size: 8
}; // Size: 784


#endif //__SSTRUCTBASE_SSHADERDATA_DECL__
)-"; 
    static constexpr char uniform_decl[] = R"-(
cbuffer SStructBase_SShaderData_
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4
	uint2 _pad0_SShaderData;			// Offset: 776 - Size: 8
}; // Size: 784
)-";
};

#else

struct SStructBase_SShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4
	uint2 _pad0_SShaderData;			// Offset: 776 - Size: 8
}; // Size: 784

#endif //__cplusplus
#endif //__SSTRUCTBASE_SSHADERDATA_DECL__

#ifndef __SINNER_DECL__
#define __SINNER_DECL__

#ifdef __cplusplus


struct SInner
{
	float x;							// Offset: 0 - Size: 4
	float y;							// Offset: 4 - Size: 4
	float z;							// Offset: 8 - Size: 4
	float w;							// Offset: 12 - Size: 4
}; // Size: 16

template<> struct pyhlslgen<SInner>
{
    using type_t = SInner;
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool uniform_alignment = false;
    static constexpr bool relaxed_alignment = true;
    static constexpr bool scalar_alignment = false;
    static constexpr char type_name[] = "SInner"; 
    static constexpr char struct_decl[] = R"-(
#ifndef __SINNER_DECL__
#define __SINNER_DECL__


struct SInner
{
	float x;							// Offset: 0 - Size: 4
	float y;							// Offset: 4 - Size: 4
	float z;							// Offset: 8 - Size: 4
	float w;							// Offset: 12 - Size: 4
}; // Size: 16


#endif //__SINNER_DECL__
)-"; 
    static constexpr char uniform_decl[] = R"-(
cbuffer SInner_
{
	float x;							// Offset: 0 - Size: 4
	float y;							// Offset: 4 - Size: 4
	float z;							// Offset: 8 - Size: 4
	float w;							// Offset: 12 - Size: 4
}; // Size: 16
)-";
};

#else

struct SInner
{
	float x;							// Offset: 0 - Size: 4
	float y;							// Offset: 4 - Size: 4
	float z;							// Offset: 8 - Size: 4
	float w;							// Offset: 12 - Size: 4
}; // Size: 16

#endif //__cplusplus
#endif //__SINNER_DECL__

#ifndef __SOUTER_DECL__
#define __SOUTER_DECL__

#ifdef __cplusplus


struct SOuter
{
	SInner A;							// Offset: 0 - Size: 16
	uint3 B;							// Offset: 16 - Size: 12
	SInner C[2];						// Offset: 28 - Size: 32
	uint1 _pad0_SOuter;					// Offset: 60 - Size: 4
}; // Size: 64

template<> struct pyhlslgen<SOuter>
{
    using type_t = SOuter;
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool uniform_alignment = false;
    static constexpr bool relaxed_alignment = true;
    static constexpr bool scalar_alignment = false;
    static constexpr char type_name[] = "SOuter"; 
    static constexpr char struct_decl[] = R"-(
#ifndef __SOUTER_DECL__
#define __SOUTER_DECL__


struct SOuter
{
	SInner A;							// Offset: 0 - Size: 16
	uint3 B;							// Offset: 16 - Size: 12
	SInner C[2];						// Offset: 28 - Size: 32
	uint1 _pad0_SOuter;					// Offset: 60 - Size: 4
}; // Size: 64


#endif //__SOUTER_DECL__
)-"; 
    static constexpr char uniform_decl[] = R"-(
cbuffer SOuter_
{
	SInner A;							// Offset: 0 - Size: 16
	uint3 B;							// Offset: 16 - Size: 12
	SInner C[2];						// Offset: 28 - Size: 32
	uint1 _pad0_SOuter;					// Offset: 60 - Size: 4
}; // Size: 64
)-";
};

#else

struct SOuter
{
	SInner A;							// Offset: 0 - Size: 16
	uint3 B;							// Offset: 16 - Size: 12
	SInner C[2];						// Offset: 28 - Size: 32
	uint1 _pad0_SOuter;					// Offset: 60 - Size: 4
}; // Size: 64

#endif //__cplusplus
#endif //__SOUTER_DECL__

#ifndef __SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__
#define __SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__

#ifdef __cplusplus
namespace vkfw {


struct SStructTest_SShaderStructTestData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4
	uint2 _pad0_SShaderStructTestData;	// Offset: 776 - Size: 8
}; // Size: 784

template<> struct pyhlslgen<SStructTest_SShaderStructTestData>
{
    using type_t = SStructTest_SShaderStructTestData;
    static constexpr bool is_valid = true;
    static constexpr bool is_primitive = false;
    static constexpr bool uniform_alignment = false;
    static constexpr bool relaxed_alignment = true;
    static constexpr bool scalar_alignment = false;
    static constexpr char type_name[] = "SStructTest_SShaderStructTestData"; 
    static constexpr char struct_decl[] = R"-(
#ifndef __SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__
#define __SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__


struct SStructTest_SShaderStructTestData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4
	uint2 _pad0_SShaderStructTestData;	// Offset: 776 - Size: 8
}; // Size: 784


#endif //__SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__
)-"; 
    static constexpr char uniform_decl[] = R"-(
cbuffer SStructTest_SShaderStructTestData_
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4
	uint2 _pad0_SShaderStructTestData;	// Offset: 776 - Size: 8
}; // Size: 784
)-";
};
}

#else

struct SStructTest_SShaderStructTestData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4
	uint2 _pad0_SShaderStructTestData;	// Offset: 776 - Size: 8
}; // Size: 784

#endif //__cplusplus
#endif //__SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__


//struct.gen.hlsli
////////////////////////////////
