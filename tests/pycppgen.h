
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
#include <any>

struct member_variable_info {
	std::string Name;
	std::string FullName;
	std::string Type;
	size_t Offset = 0;
	size_t ElementSize = 0;
	size_t TotalSize = 0;
	size_t ArrayRank = 0;
	std::vector<size_t> ArrayExtents;
	std::map<std::string, std::string> Attributes;
};

struct function_parameter_info {
	std::string Name;
	std::string Type;
	std::string DefaultValue;
	std::map<std::string, std::string> Attributes;
};

struct member_function_info {
	std::string Name;
	std::string Declaration;
	std::string ReturnType;
	std::vector<function_parameter_info> Parameters;
	std::map<std::string, std::string> Attributes;
};

template<typename T = void> struct pycppgen { static constexpr bool is_valid() { return false; } };
template<> struct pycppgen<void> 
{
    pycppgen(std::string_view name);
    pycppgen(const std::type_info& info) : HashCode(info.hash_code()) {}
    void for_each_var(std::function<void(const member_variable_info&)> fn) const;
    void for_each_var(const void* obj, auto fn) const;
    void for_each_var(void* obj, auto fn) const;    
    template<typename T> static void for_each_var(const T* obj, auto fn);
    template<typename T> static void for_each_var(T* obj, auto fn);   
    template<typename T, typename R> static bool dump(T& result, const R* object); 
    template<typename T, typename R> static bool parse(const T& data, R* object); 

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

namespace pycppgen_detail
{
	template <typename T>
	size_t get_rank(const T& arr) {
		return std::rank_v<T>;
	}

	template <typename T, std::size_t N>
	size_t get_rank(const std::array<T, N>& arr) {
	    return 1;
	}

	template <typename T>
	std::vector<size_t> get_extents(const T& arr) {
		return { 0 };
	}

	template <typename T, std::size_t N>
	std::vector<size_t> get_extents(const std::array<T, N>& arr) {
	    return { N };
	}

	template <typename T, std::size_t N>
	std::vector<size_t> get_extents(T (&)[N]) {
	    return { N };
	}
	
	template <typename T, std::size_t N, std::size_t M, typename... Dims>
	std::vector<std::size_t> get_extents(T (&)[N][M], Dims... dims) {
	    std::vector<size_t> extents = {N, M};
	    (extents.push_back(dims), ...);
	    return extents;
	}

	template <typename T, std::size_t N, std::size_t M, std::size_t B, typename... Dims>
	std::vector<std::size_t> get_extents(T (&)[N][M][B], Dims... dims) {
	    std::vector<size_t> extents = {N, M, B};
	    (extents.push_back(dims), ...);
	    return extents;
	}
}

#endif //_PYCPPGEN_HEADER_
    