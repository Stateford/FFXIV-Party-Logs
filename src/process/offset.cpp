#include "offset.h"

#include <iostream>

Offset::Offset(std::vector<DWORD64> offset)
{
    offsets_ = offset;
}

Offset::~Offset()
{
    
}

/*
 * Returns the memory address listed at the offset
 */
DWORD64 Offset::getMemoryAddress(Process* proc, Module* module)
{
    // get offset from the module
    DWORD64 address = module->getAddress();
    for(int i = 0; i < offsets_.size() - 1; i++)
    {
        address += offsets_[i];
        ReadProcessMemory(proc->getHandle(), (void*)(address), &address, sizeof(DWORD), 0);
    }
    address += offsets_[offsets_.size() - 1];
    return address;
}

DWORD64 Offset::getMemoryAddress64(Process* proc, Module* module)
{
    // get offset from the module
    DWORD64 address = module->getAddress();
    for (int i = 0; i < offsets_.size() - 1; i++)
    {
        address += offsets_[i];
        ReadProcessMemory(proc->getHandle(), (void*)(address), &address, sizeof(DWORD64), 0);
    }
    address += offsets_[offsets_.size() - 1];

    return address;
}
