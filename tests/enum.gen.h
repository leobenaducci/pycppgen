#pragma once

#include "pycppgen.h"
#include "enum.h"

//<autogen__pycppgen_EEnum>

#ifndef _pycppgen_EEnum
#define _pycppgen_EEnum

template<>
struct pycppgen<EEnum> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string, std::string> Attributes = {
		{ "bitmask", "" }
		};

	template<typename FN> static void for_each_enum_value(FN&& fn) {
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
	static std::map<std::string, std::string> enum_value_attributes(EEnum value) {
		if (value == EEnum::None) {
			return {};
		}
		if (value == EEnum::Something) {
			return {};
		}
		if (value == EEnum::Value) {
			return {};
		}
		if (value == EEnum::Test) {
			return {};
		}
		return {};
	}
};

#endif //_pycppgen_EEnum
//</autogen__pycppgen_EEnum>

//<autogen__pycppgen_EAnotherEnum>

#ifndef _pycppgen_EAnotherEnum
#define _pycppgen_EAnotherEnum

template<>
struct pycppgen<EAnotherEnum> {
	static constexpr bool is_valid() { return true; }
	std::map<std::string, std::string> Attributes = {

		};

	template<typename FN> static void for_each_enum_value(FN&& fn) {
		fn( EAnotherEnum::Zero );
		fn( EAnotherEnum::One );
		fn( EAnotherEnum::Two );
		fn( EAnotherEnum::Three );
		fn( EAnotherEnum::COUNT );
	}
	static constexpr std::string_view enum_to_string(EAnotherEnum value) {
		if (value == EAnotherEnum::Zero ) return "Zero";
		if (value == EAnotherEnum::One ) return "One";
		if (value == EAnotherEnum::Two ) return "Two";
		if (value == EAnotherEnum::Three ) return "Three";
		if (value == EAnotherEnum::COUNT ) return "COUNT";
		return "";
	}
	static constexpr EAnotherEnum string_to_enum(std::string_view value) {
		if (value == "Zero") return EAnotherEnum::Zero;
		if (value == "One") return EAnotherEnum::One;
		if (value == "Two") return EAnotherEnum::Two;
		if (value == "Three") return EAnotherEnum::Three;
		if (value == "COUNT") return EAnotherEnum::COUNT;
		return static_cast<EAnotherEnum>(-1);
	}
	static std::map<std::string, std::string> enum_value_attributes(EAnotherEnum value) {
		if (value == EAnotherEnum::Zero) {
			return {};
		}
		if (value == EAnotherEnum::One) {
			return {};
		}
		if (value == EAnotherEnum::Two) {
			return {};
		}
		if (value == EAnotherEnum::Three) {
			return {};
		}
		if (value == EAnotherEnum::COUNT) {
			return {};
		}
		return {};
	}
};

#endif //_pycppgen_EAnotherEnum
//</autogen__pycppgen_EAnotherEnum>

namespace pycppgen_globals {
}
