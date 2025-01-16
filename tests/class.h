
class CObject
{
public:
    int PrivateInt = 2;

    void Func() {
        PrivateInt = 3;
    }
    
protected:
    unsigned int ProtectedUint;

public:
    short PublicShort;
    char PublicCharArray[16];

};

class CChild : CObject
{
public:

    //simd
    float Matrix[4][4];
};

