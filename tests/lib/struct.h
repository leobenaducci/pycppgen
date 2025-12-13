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

// ubo430 layout (Uniform Buffer default)
struct UBO_pyhlslgen
{
    float3 pos;   // offset 0, size 12, BUT aligned to 16
    float2  scale; // offset 16 (not 12!), size 4
};


// ssbo layout (Storage Buffer default, or UBO with extension)
struct SSBBO_pyhlslgen_relaxed
{
    float3 pos;   // offset 0, size 12, aligned to 4
    float2 scale; // offset 12, size 4 (tightly packed)
};

// scalar layout (Storage Buffer default, or UBO with extension)
struct SBuffer_pyhlslgen_scalar
{
    float2 pos;
};

struct STestShaderData_pyhlslgen_uniform
{
    float A;
    float3x4 H[16];
    float B;
};

namespace vkfw
{
    struct SNamespacedShaderData_pyhlslgen_relaxed
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

namespace vkfw
{
    //$[[pycppgen visible]]
    struct SStructTest : SStructBase
    {
        struct SShaderStructTestData_pyhlslgen
        {
        	float A;
        	float3x4 H[16];
        	float B;
        };

        //$[[pycppgen visible;serialize]]
        float y,z;

        //$[[pycppgen pure]
        static void OnRegister() {}
    };
}
