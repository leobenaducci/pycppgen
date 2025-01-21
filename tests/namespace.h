#pragma once

#include "class.h"

#include "namespace.gen.h"

//$[[pycppgen]]
namespace TestNameSpace
{
    //$[[pycppgen]]
    int GlobalInt = 2;

    //$[[pycppgen]]
    void FuncA();
    
    void FuncB(int paramB);

    int FuncC();

    //$[[pycppgen exclude]]
    class CChild : CObject
    {
    public:
        float Matrix[4][4];
    };

}