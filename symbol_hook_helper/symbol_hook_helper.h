// SPDX-FileCopyrightText: 2022 Noeliel
//
// SPDX-License-Identifier: MIT

#ifndef SYMBOLHOOKHELPER_H
#define SYMBOLHOOKHELPER_H
#ifdef _WIN32
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern void *get_orig_symbol(const char *name);
extern void set_orig_symbol(const char *name, void *ptr);

#ifdef __cplusplus
}
#endif

#endif // SYMBOLHOOKHELPER_H
