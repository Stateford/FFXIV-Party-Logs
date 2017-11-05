#include "offset.h"

Offset::Offset(std::vector<DWORD> offset)
{
    offsets_ = offset;
}

DWORD Offset::getMemoryAddress(Process* ffxiv_, Module* exe_)
{
    DWORD temp = exe_->getAddress();
    for(int i = 0; i < offsets_.size(); i++)
    {
        temp += offsets_[i];
        ReadProcessMemory(ffxiv_->getHandle(), (void*)(temp), &temp, sizeof(DWORD), 0);
    }
    return temp;
}
