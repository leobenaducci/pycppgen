#pragma once

// Size = 176
struct STestShaderData
{
	float3		A;	// Offset: 0 - Size: 12
	float		B;	// Offset: 12 - Size: 4
	float4		C;	// Offset: 16 - Size: 16
	float2		D;	// Offset: 32 - Size: 8
	float2		_pad1;	// Offset: 40 - Size: 8
	float4x3	E;	// Offset: 48 - Size: 48
	float4		F[4];	// Offset: 96 - Size: 64
	double		G;	// Offset: 160 - Size: 8
	float		H;	// Offset: 168 - Size: 4
	float1		_pad2;	// Offset: 172 - Size: 4
};
