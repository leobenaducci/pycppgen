#pragma once

#include <array>

//$[[pycppgen visible]]
struct SStructTest
{
    //$[[pycppgen visible]]
    static inline const int size = 3;
    
    //$[[pycppgen visible;serialize]]
    float x,y,z;

    //$[[pycppgen pure]
    static void OnRegister() {}
};
