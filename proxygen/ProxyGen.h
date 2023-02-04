// SPDX-FileCopyrightText: 2022 Noeliel
//
// SPDX-License-Identifier: MIT

#ifndef PROXYGEN_H
#define PROXYGEN_H
#ifdef _WIN32
#pragma once
#endif

#include "../common.h"

#define HEADERREFGEN(symbol) \
extern void *orig_##symbol;

#ifdef _WIN32
#ifdef ENV_IS_32BIT
#define STUBGEN(symbol) WINSTUBGEN32(symbol)
#else // !defined(ENV_IS_32BIT)
#define STUBGEN(symbol) WINSTUBGEN64(symbol)
#endif // win 32bit vs 64bit
#else // !defined(_WIN32)
#define STUBGEN(symbol) GCCSTUBGEN(symbol)
#endif

#define WINSTUBGEN32(symbol) \
void *orig_##symbol = NULL; \
EXPORT_SYMBOL_NAKED_X86 \
void *__cdecl symbol() { \
    __asm { \
        push orig_##symbol \
    } \
    __asm { \
        ret \
    } \
}

#define WINSTUBGEN64(symbol) \
void *orig_##symbol = NULL; \
EXPORT_SYMBOL \
void *__cdecl symbol() { \
    __asm { \
        jmp orig_##symbol \
    } \
}

// untested
#define GCCSTUBGEN(symbol) \
void *orig_##symbol = NULL; \
EXPORT_SYMBOL \
void *__cdecl symbol() { \
    __asm__ ( \
        "jmp orig_"#symbol \
    ); \
}

#ifdef _WIN32
#define HOOKGEN(symbol) WINHOOKGEN(symbol)
#else
#define HOOKGEN(symbol) GCCHOOKGEN(symbol)
#endif

#define WINHOOKGEN(symbol) \
orig_##symbol = (void *)GetProcAddress(hTargetDll, #symbol);

// TODO: IMPLEMENT!
#define GCCHOOKGEN(symbol)

#endif // PROXYGEN_H
