#pragma once

#include "class.h"
#include "struct.h"
#include "namespace.gen.h"

//$[[pycppgen]]
namespace TestNamespace
{
    //$[[pycppgen]]
    void Func1();
    
    //$[[pycppgen]]
    void Func2(int paramB);

    //$[[pycppgen]]
    int Func3();

    //$[[pycppgen exclude]]
    class CNamespaceChild : public CObject
    {
    public:

        //$[[pycppgen]
        SStructTest A;
    };

}