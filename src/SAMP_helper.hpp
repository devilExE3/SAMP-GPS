#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

const int CHECKPOINT_BASE_OFFSET = 0x21A10C;

inline uintptr_t sampGetBase()
{
    static uintptr_t sampBase = 0;
    if (sampBase == 0)
        sampBase = reinterpret_cast<uintptr_t>(GetModuleHandleA("samp.dll"));
    return sampBase;
}
inline bool isSampAvailable()
{
    return *reinterpret_cast<void**>(sampGetBase() + 0x21A0F8) != nullptr;
}

inline bool sampCheckpointActive()
{
    if(!isSampAvailable()) return false;
    bool* pointer_ref = *(bool**)(sampGetBase() + 0x21A10C + 0x24);
    return *(bool*)pointer_ref;
}