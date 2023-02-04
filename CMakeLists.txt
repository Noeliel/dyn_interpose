# SPDX-FileCopyrightText: 2022 Noeliel
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.10.2)
cmake_policy(SET CMP0091 NEW)

set(CMAKE_C_EXTENSIONS FALSE)
set(CMAKE_CXX_EXTENSIONS FALSE)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

project("dyn_interpose")

set(dyn_interpose_32 "target_x86")
set(dyn_interpose_64 "target_x64")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(dyn_interpose ${dyn_interpose_64})
else()
  set(dyn_interpose ${dyn_interpose_32})
endif()

### override for clang-cl hax
set(dyn_interpose ${dyn_interpose_64})
###

add_library(
    ${dyn_interpose}
    SHARED
    proxygen/ProxyGen.c
    symbol_hook_helper/symbol_hook_helper.cpp
    main.cpp
)

if(MSVC)
  set_property(TARGET ${dyn_interpose} PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

  # "/DEBUG:FULL"
  target_link_options(
    ${dyn_interpose}
    PRIVATE
    "/SUBSYSTEM:WINDOWS"
    "/MANIFEST:NO"
    "ws2_32.lib"
    "bcrypt.lib"
    "advapi32.lib"
    "crypt32.lib"
    "secur32.lib"
    "user32.lib" # MessageBoxA
    # "msvcrt.lib" # 32bit needs this
  )
else()
  set(CMAKE_CXX_FLAGS "-fpermissive")

  target_include_directories(
    ${dyn_interpose} PUBLIC
    "/usr/x86_64-w64-mingw32"
  )

  target_link_options(
    ${dyn_interpose}
    PRIVATE
    "-shared"
    "-static"
    "-Wl,-subsystem,windows"
  )
endif()

target_link_libraries(
  ${dyn_interpose} PUBLIC
)
