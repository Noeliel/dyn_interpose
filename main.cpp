// SPDX-FileCopyrightText: 2022 Noeliel
//
// SPDX-License-Identifier: MIT

#include <cstdint>
#include <iostream>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#include <process.h>
#endif

#include "main.hpp"
#include "symbol_hook_helper/symbol_hook_helper.h"
#include "proxygen/ProxyGen.h"
#include "proxygen/ProxyGenDecls.h"

// list the symbols that you're not forwarding using ProxyGen
// this is not required if you plan on resolving them on-demand
// (...or if you don't need them at all)
static const char *const targets[] = {
    "some_symbol_that_i_am_hooking"
};

// todo: make os-agnostic
#ifdef _WIN32

BOOL CALL_CONV DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {

    // if you rename this variable, make sure to adjust ProxyGen.h:60
    static HMODULE hTargetDll = NULL;

    if (fdwReason == DLL_PROCESS_ATTACH) {

        if (hTargetDll) {
            FreeLibrary(hTargetDll);
            hTargetDll = NULL;
        }

        hTargetDll = LoadLibraryA(ORIG_DLL_NAME);

        if (!hTargetDll) {

            std::stringstream s_str;
            DWORD size = GetCurrentDirectory(0, NULL);
            LPSTR fs_path = (LPSTR)malloc(size);
            GetCurrentDirectory(size, fs_path);
            s_str << "Failed to locate " << ORIG_DLL_NAME << " in \"" << fs_path << "\". Quitting...";
            MessageBoxA(NULL, s_str.str().c_str(), "dyn_interpose", (MB_OK | MB_TASKMODAL));
            free(fs_path);

            return FALSE;
        }

	// invoke symbol_hook_helper...
        for (uint32_t i = 0; i < (sizeof(targets) / sizeof(targets[0])); i++) {
            set_orig_symbol(targets[i], (void *)GetProcAddress(hTargetDll, targets[i]));
        }

// locate and store addresses for all forwarded symbols (see ProxyGen.h:59)
#define PROXYGEN(symbol) HOOKGEN(symbol)
#include "symbols.proxygen"
#undef PROXYGEN

    }
    else if (fdwReason == DLL_PROCESS_DETACH) {

        if (hTargetDll) {
            FreeLibrary(hTargetDll);
            hTargetDll = NULL;
        }
    }

    return TRUE;
}

#else
// nope
#endif

EXPORT_SYMBOL
extern "C" void *__cdecl some_symbol_that_i_am_hooking() {
    // your implementation
}
