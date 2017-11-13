/*
 * This file is for running the game directx11. When the game is launched in directx11, the game
 * is running in 64-bit, which requires being able to read 64-bit hexadecimal addresses
 */
#include "x64.h"


x64::x64(Process* proc)
{
    numberOfPartyMembers_ = new Offset({ 0x1807FB8, 0x38, 0x10, 0x208, 0x20 });
    exe_ = new Module("ffxiv_dx11.exe");

    if (exe_->getModule(proc))
    {
        Arch::x64 = true;
    }

    createAllies();
}

x64::~x64()
{
    deleteAllies();
    delete exe_;
    delete numberOfPartyMembers_;
    exe_ = nullptr;
    numberOfPartyMembers_ = nullptr;
}

void x64::createAllies()
{
    // dx11 64-bit offsets
    allies_.push_back(new YOU(0x1828AE1));
    allies_.push_back(new Ally(0x184A170));
    allies_.push_back(new Ally(0x1849F50));
    allies_.push_back(new Ally(0x184A5B0));
    allies_.push_back(new Ally(0x184A9F0));
    allies_.push_back(new Ally(0x184A7D0));
    allies_.push_back(new Ally(0x184AC10));
    allies_.push_back(new Ally(0x184A390));
    allies_.push_back(new Ally(0x184AE30));
}

void x64::updateNumberOfPartyMembers(Process* proc, int &partyMembers)
{
    ReadProcessMemory(proc->getHandle(), (void*)(numberOfPartyMembers_->getMemoryAddress64(proc, exe_)), &partyMembers, sizeof(int), 0);
}