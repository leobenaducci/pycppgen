#pragma once

#include <array> //included for performance profiling

//$[[pycppgen]]
struct SStructBase
{
    //$[[pycppgen visible]]
    static const char size = 12;

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
