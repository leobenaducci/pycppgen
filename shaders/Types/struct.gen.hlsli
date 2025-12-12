#pragma once


#ifndef __STESTSHADERDATA_DECL__
#define __STESTSHADERDATA_DECL__

#ifdef __cplusplus


// Size = 776
struct STestShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};

template<> struct pyhlslgen<STestShaderData>
{
    using type = STestShaderData;
    static constexpr char decl[] = ""\
	""\
	"#ifndef __STESTSHADERDATA_DECL__"\
	"#define __STESTSHADERDATA_DECL__"\
	""\
	""\
	"// Size = 776"\
	"struct STestShaderData"\
	"{"\
	"	float A;							// Offset: 0 - Size: 4"\
	"	float3x4 H[16];						// Offset: 4 - Size: 768"\
	"	float B;							// Offset: 772 - Size: 4"\
	""\
	"};"\
	""\
	""\
	"#endif //__STESTSHADERDATA_DECL__"\
	""\
"";

};

#else
    
// Size = 776
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


// Size = 776
struct SNamespacedShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};

template<> struct pyhlslgen<SNamespacedShaderData>
{
    using type = SNamespacedShaderData;
    static constexpr char decl[] = ""\
	""\
	"#ifndef __SNAMESPACEDSHADERDATA_DECL__"\
	"#define __SNAMESPACEDSHADERDATA_DECL__"\
	""\
	""\
	"// Size = 776"\
	"struct SNamespacedShaderData"\
	"{"\
	"	float A;							// Offset: 0 - Size: 4"\
	"	float3x4 H[16];						// Offset: 4 - Size: 768"\
	"	float B;							// Offset: 772 - Size: 4"\
	""\
	"};"\
	""\
	""\
	"#endif //__SNAMESPACEDSHADERDATA_DECL__"\
	""\
"";

};
}

#else
    
// Size = 776
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


// Size = 776
struct SStructBase_SShaderData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};

template<> struct pyhlslgen<SStructBase_SShaderData>
{
    using type = SStructBase_SShaderData;
    static constexpr char decl[] = ""\
	""\
	"#ifndef __SSTRUCTBASE_SSHADERDATA_DECL__"\
	"#define __SSTRUCTBASE_SSHADERDATA_DECL__"\
	""\
	""\
	"// Size = 776"\
	"struct SStructBase_SShaderData"\
	"{"\
	"	float A;							// Offset: 0 - Size: 4"\
	"	float3x4 H[16];						// Offset: 4 - Size: 768"\
	"	float B;							// Offset: 772 - Size: 4"\
	""\
	"};"\
	""\
	""\
	"#endif //__SSTRUCTBASE_SSHADERDATA_DECL__"\
	""\
"";

};

#else
    
// Size = 776
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


// Size = 776
struct SStructTest_SShaderStructTestData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};

template<> struct pyhlslgen<SStructTest_SShaderStructTestData>
{
    using type = SStructTest_SShaderStructTestData;
    static constexpr char decl[] = ""\
	""\
	"#ifndef __SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__"\
	"#define __SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__"\
	""\
	""\
	"// Size = 776"\
	"struct SStructTest_SShaderStructTestData"\
	"{"\
	"	float A;							// Offset: 0 - Size: 4"\
	"	float3x4 H[16];						// Offset: 4 - Size: 768"\
	"	float B;							// Offset: 772 - Size: 4"\
	""\
	"};"\
	""\
	""\
	"#endif //__SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__"\
	""\
"";

};
}

#else
    
// Size = 776
struct SStructTest_SShaderStructTestData
{
	float A;							// Offset: 0 - Size: 4
	float3x4 H[16];						// Offset: 4 - Size: 768
	float B;							// Offset: 772 - Size: 4

};

#endif //__cplusplus
#endif //__SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__
