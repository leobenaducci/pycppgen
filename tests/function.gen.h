#include "function.h"

#ifndef _PYCPPGEN_DECLARATIONS
#define _PYCPPGEN_DECLARATIONS

struct member_variable_info {
	std::string_view Name;
	std::string_view Type;
	size_t Offset = 0;
	size_t Size = 0;
	size_t ArrayLength = 0;
};

template<typename T> struct meta {};

#endif //_PYCPPGEN_DECLARATIONS

