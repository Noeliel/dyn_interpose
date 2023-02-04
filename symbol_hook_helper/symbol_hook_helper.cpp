// SPDX-FileCopyrightText: 2022 Noeliel
//
// SPDX-License-Identifier: MIT

#include <utility>
#include <sstream>
#include <unordered_map>
#include "symbol_hook_helper.h"
#include "../common.h"

using std::string;
using std::unordered_map;
using std::shared_ptr;

shared_ptr<unordered_map<string, void *>> orig_symbols = std::make_shared<unordered_map<string, void *>>();

extern "C" void *get_orig_symbol(const char *name) {

    void *ptr = nullptr;

    if (name) {

        string symbol {name};

        if (!symbol.empty()) {

            unordered_map<string, void *>::iterator it = orig_symbols->find(symbol);

            if (it != orig_symbols->end())
                ptr = it->second;
        }
    }

    return ptr;
}

extern "C" void set_orig_symbol(const char *name, void *ptr) {
    orig_symbols->insert(std::make_pair(name, ptr));
}
