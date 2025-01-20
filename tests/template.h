
namespace Template
{
    template<typename T>
    struct TVector //$[[pycppgen]]
    {
        T x,y,z;

        T& operator[](uint32_t i) { return (&x)[i]; }
        const T& operator[](uint32_t i) const { return (&x)[i]; }
    };
}

using FVector = Template::TVector<float>; //$[[pycppgen]]