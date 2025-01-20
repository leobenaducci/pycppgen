#pragma once

//$[[pycppgen-include CObject CChild]]

class CObject //$[[pycppgen pure]]
{
private:
    int PrivateInt = 2;
    
protected:

    unsigned int ProtectedUint; //$[[pycppgen min=3;max=15]]

public:
    short PublicShort = 123; //$[[pycppgen readonly]]

    char PublicCharArray[16];

    void Func() //$[[pycppgen callable]]
    {
        PrivateInt = 3;
    }

    float Add(float A, double B)
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

