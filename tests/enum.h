#pragma once

enum class EEnum : unsigned //$[[pycppgen bitmask]]
{
    None = 0,
    Something, //$[[pycppgen disabled;visible=True]]
    Value,  //$[[pycppgen hidden;selectable]]
    Test = 10,
};
