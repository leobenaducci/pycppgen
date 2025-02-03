#pragma once

#include <array>
#include <vector>

namespace Template
{
    //$[[pycppgen]]
    template<typename T>
    struct TVector 
    {
        T x,y,z;

        T& operator[](uint32_t i) { return (&x)[i]; }
        const T& operator[](uint32_t i) const { return (&x)[i]; }
    };
}

using FVector = Template::TVector<float>; //$[[pycppgen]]