#pragma once

//$[[pycppgen bitmask]]
enum class EEnum : unsigned
{
    None = 0,
    Something, //$[[pycppgen disabled;visible=True]]
    Value,  //$[[pycppgen hidden;selectable]]
    Test = 10,
};
