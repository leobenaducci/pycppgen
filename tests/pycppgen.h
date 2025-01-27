#pragma once

#ifndef _PYCPPGEN_HEADER_
#define _PYCPPGEN_HEADER_

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

struct function_parameter_info {
	std::string_view Name;
	std::string_view Type;
	std::string_view DefaultValue;
	std::map<std::string, std::string> Attributes;
};

struct member_function_info {
	std::string_view Name;
	std::string_view Declaration;
	std::string_view ReturnType;
	std::vector<function_parameter_info> Parameters;
	std::map<std::string, std::string> Attributes;
};

template<typename T> struct pycppgen { static constexpr bool is_valid() { return false; } };

template<typename T> auto pycppgen_typeof(T&& t) { return pycppgen<std::decay_t<decltype(t)>>(); }

#define PYCPPGEN_STRUCT \
	virtual void for_each_var(std::function<void(const member_variable_info&)> fn) const; \
	virtual void for_each_var(std::function<void(const member_variable_info&)> fn); 
#endif //_PYCPPGEN_HEADER_

