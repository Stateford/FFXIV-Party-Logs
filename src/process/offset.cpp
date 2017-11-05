#include "offset.h"

Offset::Offset(std::vector<DWORD> offset)
{
    offsets_ = offset;
}

Offset::~Offset()
{
    
}

/*
 * Returns the memory address listed at the offset
 */
DWORD Offset::getMemoryAddress(Process* proc, Module* module)
{
    // get offset from the module
    DWORD address = module->getAddress();
    for(int i = 0; i < offsets_.size(); i++)
    {
        address += offsets_[i];
        ReadProcessMemory(proc->getHandle(), (void*)(address), &address, sizeof(DWORD), 0);
    }
    return address;
}
