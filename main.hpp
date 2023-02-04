// SPDX-FileCopyrightText: 2022 Noeliel
//
// SPDX-License-Identifier: MIT

#ifndef MAIN_HPP
#define MAIN_HPP
#ifdef _WIN32
#pragma once
#endif

#include "common.h"

#ifndef ORIG_DLL_NAME
    #ifdef ENV_IS_64BIT
        #define ORIG_DLL_NAME "orig_target_x64.dll"
    #else
        #define ORIG_DLL_NAME "orig_target_x86.dll"
    #endif
#endif

#endif // MAIN_HPP
