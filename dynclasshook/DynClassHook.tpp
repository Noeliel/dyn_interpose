// SPDX-FileCopyrightText: 2022 Noeliel
//
// SPDX-License-Identifier: MIT

#ifndef DYNCLASSHOOK_TPP
#define DYNCLASSHOOK_TPP
#ifdef _WIN32
#pragma once
#endif

#include "DynClassHook.hpp"

template <typename TargetClassType, typename VTableType>
void DynClassHook<TargetClassType, VTableType>::InstallHooks(TargetClassType *target) {

    if (!target)
        return;

    if (hook_map->find(target) != hook_map->end())
        return;

    VTableType *orig_vtable = *(VTableType **)target;
    VTableType *fake_vtable = (VTableType *)malloc(sizeof(VTableType));

    memset(fake_vtable, 0, sizeof(VTableType));
    memcpy(fake_vtable, orig_vtable, sizeof(VTableType));

    hook_map->insert(std::make_pair(target, std::make_pair(orig_vtable, fake_vtable)));
}

template <typename TargetClassType, typename VTableType>
void DynClassHook<TargetClassType, VTableType>::EnableHooks(TargetClassType *target) {

    if (!target)
        return;

    // if (hook_map->find(target) == hook_map->end())
        // InstallHooks(target);

    if (hook_map->find(target) == hook_map->end())
        return;

    VTableType *fake_vtable = GetHookVTable(target);
    *(VTableType **)target = fake_vtable;
}

template <typename TargetClassType, typename VTableType>
void DynClassHook<TargetClassType, VTableType>::DisableHooks(TargetClassType *target) {

    if (!target)
        return;

    if (hook_map->find(target) == hook_map->end())
        return;

    const VTableType *orig_vtable = GetOrigVTable(target);
    *(const VTableType **)target = orig_vtable;
}

template <typename TargetClassType, typename VTableType>
const VTableType *const DynClassHook<TargetClassType, VTableType>::GetOrigVTable(TargetClassType *target) {

    if (!target)
        return nullptr;

    if (hook_map->find(target) == hook_map->end())
        return nullptr;

    return hook_map->at(target).first;
}

template <typename TargetClassType, typename VTableType>
VTableType *const DynClassHook<TargetClassType, VTableType>::GetHookVTable(TargetClassType *target) {

    if (!target)
        return nullptr;

    if (hook_map->find(target) == hook_map->end())
        return nullptr;

    return hook_map->at(target).second;
}

template<typename TargetClassType, typename VTableType>
void DynClassHook<TargetClassType, VTableType>::RunClosureInOrigEnv(TargetClassType *_self, std::function<void()> const &closure) {

    DisableHooks(_self);
    closure();
    EnableHooks(_self);
}

#endif // DYNCLASSHOOK_TPP
