#include <libloaderapi.h>

namespace samp_helper {
    const int CHECKPOINT_BASE_OFFSET = 0x21A10C;
    bool base_address_found = false;
    UINT_PTR base_address = 0;

    void constexpr CheckBaseAddress()
    {
        if(base_address_found) return;
        base_address = (UINT_PTR)GetModuleHandleA("samp.dll");
        if(base_address == 0) return;
        base_address += CHECKPOINT_BASE_OFFSET;
        base_address_found = true;
    }

    bool constexpr sampCheckpointActive()
    {
        CheckBaseAddress();
        bool* pointer_ref = *(bool**)(base_address + 0x24);
        return *(bool*)pointer_ref;
    }
}