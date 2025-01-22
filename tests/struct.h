
#include "struct.gen.h"

//$[[pycppgen visible]]
struct SVector
{
    //$[[pycppgen visible]]
    static inline const int size = 3;
    
    //$[[pycppgen visible;serialize]]
    float x,y,z;

    //$[[pycppgen pure]
    static void OnRegister() {}
};