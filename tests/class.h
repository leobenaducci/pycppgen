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
};

class CChild : CObject
{
public:
    float Matrix[4][4];
};

