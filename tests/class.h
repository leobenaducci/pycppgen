#pragma once

//$[[pycppgen-include CObject CChild]]

//$[[pycppgen pure]]
class CObject
{
private:
    int PrivateInt = 2;
    
protected:

    //$[[pycppgen min=3;max=15]]
    unsigned int ProtectedUint;

public:
    //$[[pycppgen readonly]]
    short PublicShort = 123;

    char PublicCharArray[16];

    //$[[pycppgen]]
    static int TestStaticFunc() {}
    
    //$[[pycppgen callable]]
    void Func()
    {
        PrivateInt = 3;
    }

    //$[[pycppgen callable]]
    float Add(float A /*$[[pycppgen clamp]]*/, double B /*$[[pycppgen auto_cast;enum]]*/)
    {
        return A + float(B);
    }

    float Sub(float A, double B)
    {
        return A + float(B);
    }

    //$[[pycppgen pure]
    short Get() const
    {
        return PublicShort;
    }
};

class CChild : CObject
{
public:
    float Matrix[4][4];
};

