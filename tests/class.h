#pragma once

class CObject
{
private:
    int PrivateInt = 2;
    
protected:
    unsigned int ProtectedUint;

public:
    short PublicShort;
    char PublicCharArray[16];

    void Func() {
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

