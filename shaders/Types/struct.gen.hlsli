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
	"\n"\
	"#ifndef __STESTSHADERDATA_DECL__\n"\
	"#define __STESTSHADERDATA_DECL__\n"\
	"\n"\
	"\n"\
	"// Size = 776\n"\
	"struct STestShaderData\n"\
	"{\n"\
	"	float A;							// Offset: 0 - Size: 4\n"\
	"	float3x4 H[16];						// Offset: 4 - Size: 768\n"\
	"	float B;							// Offset: 772 - Size: 4\n"\
	"\n"\
	"};\n"\
	"\n"\
	"\n"\
	"#endif //__STESTSHADERDATA_DECL__\n"\
	"\n"\
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
	"\n"\
	"#ifndef __SNAMESPACEDSHADERDATA_DECL__\n"\
	"#define __SNAMESPACEDSHADERDATA_DECL__\n"\
	"\n"\
	"\n"\
	"// Size = 776\n"\
	"struct SNamespacedShaderData\n"\
	"{\n"\
	"	float A;							// Offset: 0 - Size: 4\n"\
	"	float3x4 H[16];						// Offset: 4 - Size: 768\n"\
	"	float B;							// Offset: 772 - Size: 4\n"\
	"\n"\
	"};\n"\
	"\n"\
	"\n"\
	"#endif //__SNAMESPACEDSHADERDATA_DECL__\n"\
	"\n"\
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
	"\n"\
	"#ifndef __SSTRUCTBASE_SSHADERDATA_DECL__\n"\
	"#define __SSTRUCTBASE_SSHADERDATA_DECL__\n"\
	"\n"\
	"\n"\
	"// Size = 776\n"\
	"struct SStructBase_SShaderData\n"\
	"{\n"\
	"	float A;							// Offset: 0 - Size: 4\n"\
	"	float3x4 H[16];						// Offset: 4 - Size: 768\n"\
	"	float B;							// Offset: 772 - Size: 4\n"\
	"\n"\
	"};\n"\
	"\n"\
	"\n"\
	"#endif //__SSTRUCTBASE_SSHADERDATA_DECL__\n"\
	"\n"\
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
	"\n"\
	"#ifndef __SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__\n"\
	"#define __SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__\n"\
	"\n"\
	"\n"\
	"// Size = 776\n"\
	"struct SStructTest_SShaderStructTestData\n"\
	"{\n"\
	"	float A;							// Offset: 0 - Size: 4\n"\
	"	float3x4 H[16];						// Offset: 4 - Size: 768\n"\
	"	float B;							// Offset: 772 - Size: 4\n"\
	"\n"\
	"};\n"\
	"\n"\
	"\n"\
	"#endif //__SSTRUCTTEST_SSHADERSTRUCTTESTDATA_DECL__\n"\
	"\n"\
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
