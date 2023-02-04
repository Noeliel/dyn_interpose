// SPDX-FileCopyrightText: 2022 Noeliel
//
// SPDX-License-Identifier: MIT

#ifndef DYNCLASSHOOK_HPP
#define DYNCLASSHOOK_HPP
#ifdef _WIN32
#pragma once
#endif

#include <memory>
#include <map>
#include <functional>
#include <cstdlib>

template <typename TargetClassType, typename VTableType>
class DynClassHook {

private:
    inline static std::unique_ptr<std::map<TargetClassType *, std::pair<VTableType *, VTableType *>>> const hook_map {std::make_unique<std::map<TargetClassType *, std::pair<VTableType *, VTableType *>>>()};

public:
    static void InstallHooks(TargetClassType *target);
    static void EnableHooks(TargetClassType *target);
    static void DisableHooks(TargetClassType *target);
    static const VTableType *const GetOrigVTable(TargetClassType *target);
    static VTableType *const GetHookVTable(TargetClassType *target);
    static void RunClosureInOrigEnv(TargetClassType *_self, std::function<void()> const &closure);

};

#endif // DYNCLASSHOOK_HPP
