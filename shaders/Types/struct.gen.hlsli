#pragma once


#ifndef __UBO_DECL__
#define __UBO_DECL__

#ifdef __cplusplus


struct UBO
{
	float A;							// Offset: 0 - Size: 4
	uint3 _pad0_UBO;					// Offset: 4 - Size: 12
	float2x2 H[16];						// Offset: 16 - Size: 256
	uint4 _pad1_UBO;					// Offset: 272 - Size: 16
	uint4 _pad2_UBO;					// Offset: 288 - Size: 16
	uint4 _pad3_UBO;					// Offset: 304 - Size: 16
	uint4 _pad4_UBO;					// Offset: 320 - Size: 16
	uint4 _pad5_UBO;					// Offset: 336 - Size: 16
	uint4 _pad6_UBO;					// Offset: 352 - Size: 16
	uint4 _pad7_UBO;					// Offset: 368 - Size: 16
	uint4 _pad8_UBO;					// Offset: 384 - Size: 16
	uint4 _pad9_UBO;					// Offset: 400 - Size: 16
	uint4 _pad10_UBO;					// Offset: 416 - Size: 16
	uint4 _pad11_UBO;					// Offset: 432 - Size: 16
	uint4 _pad12_UBO;					// Offset: 448 - Size: 16
	uint4 _pad13_UBO;					// Offset: 464 - Size: 16
	uint4 _pad14_UBO;					// Offset: 480 - Size: 16
	uint4 _pad15_UBO;					// Offset: 496 - Size: 16
	uint2 _pad16_UBO;					// Offset: 512 - Size: 8
	float B;							// Offset: 520 - Size: 4
}; // Size: 524

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
	float2x2 H[16];						// Offset: 16 - Size: 256
	uint4 _pad1_UBO;					// Offset: 272 - Size: 16
	uint4 _pad2_UBO;					// Offset: 288 - Size: 16
	uint4 _pad3_UBO;					// Offset: 304 - Size: 16
	uint4 _pad4_UBO;					// Offset: 320 - Size: 16
	uint4 _pad5_UBO;					// Offset: 336 - Size: 16
	uint4 _pad6_UBO;					// Offset: 352 - Size: 16
	uint4 _pad7_UBO;					// Offset: 368 - Size: 16
	uint4 _pad8_UBO;					// Offset: 384 - Size: 16
	uint4 _pad9_UBO;					// Offset: 400 - Size: 16
	uint4 _pad10_UBO;					// Offset: 416 - Size: 16
	uint4 _pad11_UBO;					// Offset: 432 - Size: 16
	uint4 _pad12_UBO;					// Offset: 448 - Size: 16
	uint4 _pad13_UBO;					// Offset: 464 - Size: 16
	uint4 _pad14_UBO;					// Offset: 480 - Size: 16
	uint4 _pad15_UBO;					// Offset: 496 - Size: 16
	uint2 _pad16_UBO;					// Offset: 512 - Size: 8
	float B;							// Offset: 520 - Size: 4
}; // Size: 524


#endif //__UBO_DECL__
)-"; 
    static constexpr char uniform_decl[] = R"-(
cbuffer UBO_
{
	float A;							// Offset: 0 - Size: 4
	uint3 _pad0_UBO;					// Offset: 4 - Size: 12
	float2x2 H[16];						// Offset: 16 - Size: 256
	uint4 _pad1_UBO;					// Offset: 272 - Size: 16
	uint4 _pad2_UBO;					// Offset: 288 - Size: 16
	uint4 _pad3_UBO;					// Offset: 304 - Size: 16
	uint4 _pad4_UBO;					// Offset: 320 - Size: 16
	uint4 _pad5_UBO;					// Offset: 336 - Size: 16
	uint4 _pad6_UBO;					// Offset: 352 - Size: 16
	uint4 _pad7_UBO;					// Offset: 368 - Size: 16
	uint4 _pad8_UBO;					// Offset: 384 - Size: 16
	uint4 _pad9_UBO;					// Offset: 400 - Size: 16
	uint4 _pad10_UBO;					// Offset: 416 - Size: 16
	uint4 _pad11_UBO;					// Offset: 432 - Size: 16
	uint4 _pad12_UBO;					// Offset: 448 - Size: 16
	uint4 _pad13_UBO;					// Offset: 464 - Size: 16
	uint4 _pad14_UBO;					// Offset: 480 - Size: 16
	uint4 _pad15_UBO;					// Offset: 496 - Size: 16
	uint2 _pad16_UBO;					// Offset: 512 - Size: 8
	float B;							// Offset: 520 - Size: 4
}; // Size: 524
)-";
};

#else

struct UBO
{
	float A;							// Offset: 0 - Size: 4
	uint3 _pad0_UBO;					// Offset: 4 - Size: 12
	float2x2 H[16];						// Offset: 16 - Size: 256
	uint4 _pad1_UBO;					// Offset: 272 - Size: 16
	uint4 _pad2_UBO;					// Offset: 288 - Size: 16
	uint4 _pad3_UBO;					// Offset: 304 - Size: 16
	uint4 _pad4_UBO;					// Offset: 320 - Size: 16
	uint4 _pad5_UBO;					// Offset: 336 - Size: 16
	uint4 _pad6_UBO;					// Offset: 352 - Size: 16
	uint4 _pad7_UBO;					// Offset: 368 - Size: 16
	uint4 _pad8_UBO;					// Offset: 384 - Size: 16
	uint4 _pad9_UBO;					// Offset: 400 - Size: 16
	uint4 _pad10_UBO;					// Offset: 416 - Size: 16
	uint4 _pad11_UBO;					// Offset: 432 - Size: 16
	uint4 _pad12_UBO;					// Offset: 448 - Size: 16
	uint4 _pad13_UBO;					// Offset: 464 - Size: 16
	uint4 _pad14_UBO;					// Offset: 480 - Size: 16
	uint4 _pad15_UBO;					// Offset: 496 - Size: 16
	uint2 _pad16_UBO;					// Offset: 512 - Size: 8
	float B;							// Offset: 520 - Size: 4
}; // Size: 524

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
	float3x4 H[16];						// Offset: 16 - Size: 768
	uint4 _pad1_STestShaderData;		// Offset: 784 - Size: 16
	uint4 _pad2_STestShaderData;		// Offset: 800 - Size: 16
	uint4 _pad3_STestShaderData;		// Offset: 816 - Size: 16
	uint4 _pad4_STestShaderData;		// Offset: 832 - Size: 16
	uint4 _pad5_STestShaderData;		// Offset: 848 - Size: 16
	uint4 _pad6_STestShaderData;		// Offset: 864 - Size: 16
	uint4 _pad7_STestShaderData;		// Offset: 880 - Size: 16
	uint4 _pad8_STestShaderData;		// Offset: 896 - Size: 16
	uint4 _pad9_STestShaderData;		// Offset: 912 - Size: 16
	uint4 _pad10_STestShaderData;		// Offset: 928 - Size: 16
	uint4 _pad11_STestShaderData;		// Offset: 944 - Size: 16
	uint4 _pad12_STestShaderData;		// Offset: 960 - Size: 16
	uint4 _pad13_STestShaderData;		// Offset: 976 - Size: 16
	uint4 _pad14_STestShaderData;		// Offset: 992 - Size: 16
	uint4 _pad15_STestShaderData;		// Offset: 1008 - Size: 16
	uint3 _pad16_STestShaderData;		// Offset: 1024 - Size: 12
	float B;							// Offset: 1036 - Size: 4
}; // Size: 1040

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
	float3x4 H[16];						// Offset: 16 - Size: 768
	uint4 _pad1_STestShaderData;		// Offset: 784 - Size: 16
	uint4 _pad2_STestShaderData;		// Offset: 800 - Size: 16
	uint4 _pad3_STestShaderData;		// Offset: 816 - Size: 16
	uint4 _pad4_STestShaderData;		// Offset: 832 - Size: 16
	uint4 _pad5_STestShaderData;		// Offset: 848 - Size: 16
	uint4 _pad6_STestShaderData;		// Offset: 864 - Size: 16
	uint4 _pad7_STestShaderData;		// Offset: 880 - Size: 16
	uint4 _pad8_STestShaderData;		// Offset: 896 - Size: 16
	uint4 _pad9_STestShaderData;		// Offset: 912 - Size: 16
	uint4 _pad10_STestShaderData;		// Offset: 928 - Size: 16
	uint4 _pad11_STestShaderData;		// Offset: 944 - Size: 16
	uint4 _pad12_STestShaderData;		// Offset: 960 - Size: 16
	uint4 _pad13_STestShaderData;		// Offset: 976 - Size: 16
	uint4 _pad14_STestShaderData;		// Offset: 992 - Size: 16
	uint4 _pad15_STestShaderData;		// Offset: 1008 - Size: 16
	uint3 _pad16_STestShaderData;		// Offset: 1024 - Size: 12
	float B;							// Offset: 1036 - Size: 4
}; // Size: 1040


#endif //__STESTSHADERDATA_DECL__
)-"; 
    static constexpr char uniform_decl[] = R"-(
cbuffer STestShaderData_
{
	float A;							// Offset: 0 - Size: 4
	uint3 _pad0_STestShaderData;		// Offset: 4 - Size: 12
	float3x4 H[16];						// Offset: 16 - Size: 768
	uint4 _pad1_STestShaderData;		// Offset: 784 - Size: 16
	uint4 _pad2_STestShaderData;		// Offset: 800 - Size: 16
	uint4 _pad3_STestShaderData;		// Offset: 816 - Size: 16
	uint4 _pad4_STestShaderData;		// Offset: 832 - Size: 16
	uint4 _pad5_STestShaderData;		// Offset: 848 - Size: 16
	uint4 _pad6_STestShaderData;		// Offset: 864 - Size: 16
	uint4 _pad7_STestShaderData;		// Offset: 880 - Size: 16
	uint4 _pad8_STestShaderData;		// Offset: 896 - Size: 16
	uint4 _pad9_STestShaderData;		// Offset: 912 - Size: 16
	uint4 _pad10_STestShaderData;		// Offset: 928 - Size: 16
	uint4 _pad11_STestShaderData;		// Offset: 944 - Size: 16
	uint4 _pad12_STestShaderData;		// Offset: 960 - Size: 16
	uint4 _pad13_STestShaderData;		// Offset: 976 - Size: 16
	uint4 _pad14_STestShaderData;		// Offset: 992 - Size: 16
	uint4 _pad15_STestShaderData;		// Offset: 1008 - Size: 16
	uint3 _pad16_STestShaderData;		// Offset: 1024 - Size: 12
	float B;							// Offset: 1036 - Size: 4
}; // Size: 1040
)-";
};

#else

struct STestShaderData
{
	float A;							// Offset: 0 - Size: 4
	uint3 _pad0_STestShaderData;		// Offset: 4 - Size: 12
	float3x4 H[16];						// Offset: 16 - Size: 768
	uint4 _pad1_STestShaderData;		// Offset: 784 - Size: 16
	uint4 _pad2_STestShaderData;		// Offset: 800 - Size: 16
	uint4 _pad3_STestShaderData;		// Offset: 816 - Size: 16
	uint4 _pad4_STestShaderData;		// Offset: 832 - Size: 16
	uint4 _pad5_STestShaderData;		// Offset: 848 - Size: 16
	uint4 _pad6_STestShaderData;		// Offset: 864 - Size: 16
	uint4 _pad7_STestShaderData;		// Offset: 880 - Size: 16
	uint4 _pad8_STestShaderData;		// Offset: 896 - Size: 16
	uint4 _pad9_STestShaderData;		// Offset: 912 - Size: 16
	uint4 _pad10_STestShaderData;		// Offset: 928 - Size: 16
	uint4 _pad11_STestShaderData;		// Offset: 944 - Size: 16
	uint4 _pad12_STestShaderData;		// Offset: 960 - Size: 16
	uint4 _pad13_STestShaderData;		// Offset: 976 - Size: 16
	uint4 _pad14_STestShaderData;		// Offset: 992 - Size: 16
	uint4 _pad15_STestShaderData;		// Offset: 1008 - Size: 16
	uint3 _pad16_STestShaderData;		// Offset: 1024 - Size: 12
	float B;							// Offset: 1036 - Size: 4
}; // Size: 1040

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
