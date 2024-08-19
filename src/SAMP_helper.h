#include <libloaderapi.h>

namespace samp_helper {
    const int CHECKPOINT_BASE_OFFSET = 0x21A10C;
    bool base_address_found = false;
    UINT_PTR base_address = 0;

    void CheckBaseAddress()
    {
        if(base_address_found) return;
        base_address = (UINT_PTR)GetModuleHandleA("samp.dll") + CHECKPOINT_BASE_OFFSET;
        base_address_found = true;
    }

    bool sampCheckpointActive()
    {
        CheckBaseAddress();
        void* pointer_ref = (void*)(base_address);
        pointer_ref = *(void**)((UINT_PTR)pointer_ref + 0x24);
        return *(bool*)pointer_ref;
    }
}