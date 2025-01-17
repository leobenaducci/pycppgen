#include "class.h"

namespace TestNameSpace
{
    void FuncA();
    void FuncB(int paramB);

    //$reflect const
    int FuncC();

    class CChild : CObject
    {
    public:

        //simd
        float Matrix[4][4];
    };

}