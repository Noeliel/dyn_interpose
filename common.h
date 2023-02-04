// SPDX-FileCopyrightText: 2022 Noeliel
//
// SPDX-License-Identifier: MIT

#ifndef COMMON_H
#define COMMON_H
#ifdef _WIN32
#pragma once
#endif

// thanks, clang, very nice
// even mingw managed to just ignore this
#define __cdecl

#if !defined(ENV_IS_64BIT) && !defined(ENV_IS_32BIT)
    #ifdef _WIN32 // MSVC
        #ifdef _WIN64
            #define ENV_IS_64BIT
        #else
            #define ENV_IS_32BIT
        #endif
    #else // GCC
        #ifdef __x86_64__
            #define ENV_IS_64BIT
        #else
            #define ENV_IS_32BIT
        #endif
    #endif
#endif

#ifndef EXPORT_SYMBOL
    #ifdef _WIN32
        #define EXPORT_SYMBOL __declspec(dllexport)
    #else
        #define EXPORT_SYMBOL __attribute__((visibility("default")))
    #endif
#endif

/*
#ifndef EXPORT_SYMBOL
    #if defined(__clang__) || defined(__GNUC__)
        #define EXPORT_SYMBOL __attribute__((visibility("default")))
    #else
        #define EXPORT_SYMBOL __declspec(dllexport)
    #endif
#endif
*/

// naked := don't save and restore registers, don't adjust stack frame
#ifndef EXPORT_SYMBOL_NAKED_X86
    #if defined(_WIN32) && defined(ENV_IS_32BIT)
        #define EXPORT_SYMBOL_NAKED_X86 __declspec(naked, dllexport)
    #endif
#endif

#ifndef CALL_CONV
    #ifdef _WIN32
        #define CALL_CONV WINAPI
    #else
        #define CALL_CONV __stdcall
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif // COMMON_H
