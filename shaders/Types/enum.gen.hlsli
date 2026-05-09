
////////////////////////////////
//enum.gen.hlsli

#pragma once


#ifndef __EENUM_ENUM_DECL__
#define __EENUM_ENUM_DECL__

#ifdef __cplusplus

template<> struct pyhlslgen<EEnum>
{
    using type_t = EEnum;
    static constexpr bool is_valid     = true;
    static constexpr bool is_primitive = false;
    static constexpr bool is_enum      = true;
    static constexpr bool is_bitmask   = true;
    static constexpr char type_name[]  = "EEnum";
    static constexpr char enum_decl[]  = R"-(static const uint EEnum_None = 0;
static const uint EEnum_Something = 1;
static const uint EEnum_Value = 2;
static const uint EEnum_Test = 100;
)-";
};

#else
static const uint EEnum_None = 0;
static const uint EEnum_Something = 1;
static const uint EEnum_Value = 2;
static const uint EEnum_Test = 100;

#endif //__cplusplus
#endif //__EENUM_ENUM_DECL__


//enum.gen.hlsli
////////////////////////////////
