// SPDX-FileCopyrightText: 2022 Noeliel
//
// SPDX-License-Identifier: MIT

#include <stddef.h>
#include "ProxyGen.h"

// generate stubs for forwarded symbols (see ProxyGen.h)
#define PROXYGEN(symbol) STUBGEN(symbol)
#include "../symbols.proxygen"
#undef PROXYGEN
