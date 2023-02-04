// SPDX-FileCopyrightText: 2022 Noeliel
//
// SPDX-License-Identifier: MIT

#ifndef PROXYGENDECLS_H
#define PROXYGENDECLS_H
#ifdef _WIN32
#pragma once
#endif

#include "ProxyGen.h"

#ifdef __cplusplus
extern "C" {
#endif

// generate extern declarations for forwarded symbols (see ProxyGen.h:13)
#define PROXYGEN(symbol) HEADERREFGEN(symbol)
#include "../symbols.proxygen"
#undef PROXYGEN

#ifdef __cplusplus
}
#endif

#endif // PROXYGENDECLS_H
