#pragma once

#include <array> //included for performance profiling

struct STestShaderData_pyhlslgen
{
    float3 A;
    float B;
    float4 C;
    float2 D;
    float3x3 E;
    float2 F[4];
    double G;
    float H;
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
