<!--
SPDX-FileCopyrightText: 2022 Noeliel

SPDX-License-Identifier: MIT
-->

# Introduction

*dyn_interpose* is a skeleton project or collection of code and macros for creating dynamic library (dll) proxies/wrappers/hijackers on Windows x86 and x86_64.  
Support for other platforms and architectures is **not** planned.

This repo provides code that can help you exchange implementations for specific symbols, C++ classes or methods of specific C++ objects with your own ones while forwarding everything else to the original library.
In its current state, it is neither very well documented nor easy to use–I hope to be able to rectify this at some point and provide examples.

# Components

The project is comprised of three components.

## ProxyGen

A set of macros to semi-automatically generate stubs for exported symbols to be forwarded to the target dll.
Use this to forward everything that you're not interested in to the original library.
To do so, dump your target library's exported symbols to a text file named `symbols.proxygen`, removing those symbols that you intend to provide your own implementation for.
Wrap every symbol in `PROXYGEN(..)`.
See `symbols.proxygen` for examples.

`ProxyGen/ProxyGenDecls.h` creates `extern void *` declarations for all forwarded symbols.
Include this header file in your own code if you need to access one of the forwarded symbols.

## symbol_hook_helper

A small helper to keep track of the original addresses of the symbols that you're reimplementing.
It's a supplement to `ProxyGenDecls.h`, since that one only creates declarations for forwarded symbols while *symbol_hook_helper* is meant for symbols that aren't being forwarded.
If you wish to call an original function from your own code for example, this can come in handy.
Otherwise you might not need to use this at all.

## DynClassHook

A template class that implements some mechanisms for hooking C++ objects' methods through vtable swapping.
It creates a fake copy of the vtable of every object that you wish to hook.
Then it exchanges the object's vtable pointer with the fake one, allowing you to exchange pointers to method implementations with your own.
You're required to provide correct headers for your target classes or the mechanism won't work properly.

Please note that no effort was made to ensure any kind of thread safety/synchronization.

# License

The code in this repository is licensed under the MIT SPDX identifier.  
See `LICENSES/MIT.txt` for further information.
