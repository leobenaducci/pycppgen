#pragma once

#include <array> //included for performance profiling

//$[[pycppgen]]
struct STestShaderData_pyhlslgen
{
    //$[[pycppgen visible]]
    float3 A;
    //$[[pycppgen visible]]
    float B;
    //$[[pycppgen visible]]
    float4 C;
    //$[[pycppgen visible]]
    float2 D;
    //$[[pycppgen visible]]
    float3x3 E;
    //$[[pycppgen visible]]
    float2 F[4];
};


//$[[pycppgen]]
struct SStructBase
{
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
