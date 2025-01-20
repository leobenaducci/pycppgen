#pragma once

#include "class.h"

//$[[pycppgen]]
namespace TestNameSpace
{
    void FuncA();
    void FuncB(int paramB);

    //$[[pycppgen]]
    int FuncC();

    //$[[pycppgen exclude]]
    class CChild : CObject
    {
    public:
        float Matrix[4][4];
    };

}