
#pragma once

#ifndef _PYCPPGEN_HEADER_
#define _PYCPPGEN_HEADER_

#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <map>
#include <functional>
#include <type_traits>

struct member_variable_info {
	std::string_view Name;
	std::string_view FullName;
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
template<> struct pycppgen<void> 
{
    pycppgen(const std::type_info& info) : HashCode(info.hash_code()) {}
    void for_each_var(std::function<void(const member_variable_info&)> fn) const;

protected:
    decltype(std::declval<std::type_info>().hash_code()) HashCode;
};

template<typename T> requires (!std::is_pointer_v<T>)
auto pycppgen_of(const T& t) 
{
	return pycppgen<std::decay_t<T>>(); 
}

template<typename T> requires (std::is_pointer_v<T>)
auto pycppgen_of(const T t) 
{
	return pycppgen<void>(typeid(*t));
}

#endif //_PYCPPGEN_HEADER_
    