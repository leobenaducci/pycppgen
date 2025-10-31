#pragma once

#include <array> //included for performance profiling


/*
ConstantBuffer<STestShaderData_pyhlslgen_cbuffer> inBuffer;
RWStructuredBuffer<STestShaderData_pyhlslgen_cbuffer> outBuffer;

[numthreads(1,1,1)]
void main(uint dispatchThreadId : SV_DispatchThreadId)
{
    outBuffer[dispatchThreadId] = inBuffer;
}
*/

struct STestShaderData_pyhlslgen
{
    float A;
    float3x4 H[16];
    float B;
};

namespace vkfw
{
    struct SNamespacedShaderData_pyhlslgen
    {
	    float A;
	    float3x4 H[16];
	    float B;
    };
}

//$[[pycppgen]]
struct SStructBase
{
    struct SShaderData_pyhlslgen
    {
    	float A;
    	float3x4 H[16];
    	float B;
    };

    //$[[pycppgen visible]]
    static const char size = 'A';

    //$[[pycppgen visible]]
    int components = 3;

    //$[[pycppgen]]
    float x;
};

//$[[pycppgen visible]]
struct SStructTest : SStructBase
{
    //$[[pycppgen visible;serialize]]
    float y,z;

    //$[[pycppgen pure]
    static void OnRegister() {}
};
