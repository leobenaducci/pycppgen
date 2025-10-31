#pragma once

#ifndef __STESTSHADERDATA_DECL__
#define __STESTSHADERDATA_DECL__

// Size = 784
#ifdef __cplusplus
struct STestShaderData
#else //__cplusplus
struct STestShaderData
#endif //__cplusplus
{
	float A;					// Offset: 0 - Size: 4
	float3x4 H[16];				// Offset: 4 - Size: 768
	float B;					// Offset: 772 - Size: 4
	uint2 _pad0;				// Offset: 776 - Size: 8
};

#ifdef __cplusplus

static constexpr char STestShaderData_HlslDeclaration[] = {
	"struct STestShaderData\n"\
	"{\n"\
	"	float A;					// Offset: 0 - Size: 4\n"\
	"	float3x4 H[16];				// Offset: 4 - Size: 768\n"\
	"	float B;					// Offset: 772 - Size: 4\n"\
	"	uint2 _pad0;				// Offset: 776 - Size: 8\n"\
	"\n"\
	"};"
};

#endif //__cplusplus

#endif //__STESTSHADERDATA_DECL__

#ifndef __SNAMESPACEDSHADERDATA_DECL__
#define __SNAMESPACEDSHADERDATA_DECL__

// Size = 784
#ifdef __cplusplus
namespace vkfw{
struct SNamespacedShaderData
#else //__cplusplus
struct SNamespacedShaderData
#endif //__cplusplus
{
	float A;					// Offset: 0 - Size: 4
	float3x4 H[16];				// Offset: 4 - Size: 768
	float B;					// Offset: 772 - Size: 4
	uint2 _pad0;				// Offset: 776 - Size: 8
};
#ifdef __cplusplus
} // namespace vkfw
#endif //__cplusplus

#ifdef __cplusplus

static constexpr char SNamespacedShaderData_HlslDeclaration[] = {
	"struct SNamespacedShaderData\n"\
	"{\n"\
	"	float A;					// Offset: 0 - Size: 4\n"\
	"	float3x4 H[16];				// Offset: 4 - Size: 768\n"\
	"	float B;					// Offset: 772 - Size: 4\n"\
	"	uint2 _pad0;				// Offset: 776 - Size: 8\n"\
	"\n"\
	"};"
};

#endif //__cplusplus

#endif //__SNAMESPACEDSHADERDATA_DECL__

#ifndef __SSTRUCTBASESSHADERDATA_DECL__
#define __SSTRUCTBASESSHADERDATA_DECL__

// Size = 784
#ifdef __cplusplus
struct SStructBaseSShaderData
#else //__cplusplus
struct SShaderData
#endif //__cplusplus
{
	float A;					// Offset: 0 - Size: 4
	float3x4 H[16];				// Offset: 4 - Size: 768
	float B;					// Offset: 772 - Size: 4
	uint2 _pad0;				// Offset: 776 - Size: 8
};

#ifdef __cplusplus

static constexpr char SStructBaseSShaderData_HlslDeclaration[] = {
	"struct SShaderData\n"\
	"{\n"\
	"	float A;					// Offset: 0 - Size: 4\n"\
	"	float3x4 H[16];				// Offset: 4 - Size: 768\n"\
	"	float B;					// Offset: 772 - Size: 4\n"\
	"	uint2 _pad0;				// Offset: 776 - Size: 8\n"\
	"\n"\
	"};"
};

#endif //__cplusplus

#endif //__SSTRUCTBASESSHADERDATA_DECL__

