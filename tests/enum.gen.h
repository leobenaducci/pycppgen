#include "enum.h"

#ifndef _PYCPPGEN_DECLARATIONS
#define _PYCPPGEN_DECLARATIONS

struct member_variable_info {
	std::string_view Name;
	std::string_view Type;
	size_t Offset = 0;
	size_t ElementSize = 0;
	size_t TotalSize = 0;
	size_t ArrayRank = 0;
	std::vector<size_t> ArrayExtents;
	std::map<std::string, std::string> Attributes;
};

template<typename T> struct meta {};

#endif //_PYCPPGEN_DECLARATIONS

template<> struct meta<EEnum>{
	template<typename FN> static void for_each_enum(FN&& fn) {
		fn( EEnum::None );
		fn( EEnum::Something );
		fn( EEnum::Value );
		fn( EEnum::Test );
	}
	static constexpr std::string_view enum_to_string(EEnum value) {
		if (value == EEnum::None ) return "None";
		if (value == EEnum::Something ) return "Something";
		if (value == EEnum::Value ) return "Value";
		if (value == EEnum::Test ) return "Test";
		return "";
	}
	static constexpr EEnum string_to_enum(std::string_view value) {
		if (value == "None") return EEnum::None;
		if (value == "Something") return EEnum::Something;
		if (value == "Value") return EEnum::Value;
		if (value == "Test") return EEnum::Test;
		return static_cast<EEnum>(-1);
	}
};

