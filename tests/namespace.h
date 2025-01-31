#pragma once

#include <array>
#include <vector>

#include "class.h"
#include "struct.h"

namespace TestNamespace
{
    //$[[pycppgen]]
    void Func1();
    
    //$[[pycppgen]]
    void Func2(int paramB);

    //$[[pycppgen]]
    int Func3();

    //$[[pycppgen]]
    class CNamespaceChild : public CObject
    {
    public:

        //$[[pycppgen]
        SStructTest A;
    };

}