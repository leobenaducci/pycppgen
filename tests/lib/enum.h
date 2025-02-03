#pragma once

#include <array>
#include <vector>

//$[[pycppgen bitmask]]
enum class EEnum : unsigned
{
    None = 0,
    Something, //$[[pycppgen disabled;visible=True]]
    Value,  //$[[pycppgen hidden;selectable]]
    Test = 10,
};

//$[[pycppgen]]
enum class EAnotherEnum : unsigned
{
    Zero,
    One,
    Two,
    Three,
    COUNT, //$[[pycppgen hidden]
};
