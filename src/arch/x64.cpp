/*
 * This file is for running the game directx11. When the game is launched in directx11, the game
 * is running in 64-bit, which requires being able to read 64-bit hexadecimal addresses
 */
#include "x64.h"
#include <iostream>

// constructor
x64::x64(Process* proc)
{
    // get window name
    exe_ = new Module("ffxiv_dx11.exe");
    // memory offests for dx11 number of party members
    numberOfPartyMembers_ = new Offset({ 0x018AE778, 0x38, 0x18, 0x20, 0x20, 0x10 });

    // if dx11 (64-bit) set static x64 true
    if (exe_->getModule(proc))
    {
        Arch::x64 = true;
    }

    createAllies(proc);
}

// destructor
x64::~x64()
{
    deleteAllies();
    delete exe_;
    delete numberOfPartyMembers_;
    exe_ = nullptr;
    numberOfPartyMembers_ = nullptr;
}

// create allies
void x64::createAllies(Process* proc)
{
    // A7128
    // 18F30F8
    // dx11 64-bit offsets
    allies_.push_back(new YOU(0x18D1C79));
    // each address is 0x220 away
    allies_.push_back(new Ally(0x18F3540));
    allies_.push_back(new Ally(0x18F3760));
    allies_.push_back(new Ally(0X18F3980));
    allies_.push_back(new Ally(0x18F3BA0));
    allies_.push_back(new Ally(0x18F3DC0));
    allies_.push_back(new Ally(0x18F3FE0));
    allies_.push_back(new Ally(0x18F4200));
    allies_.push_back(new Ally(0X18F3320));
    // 18F3320
    // create crossworld allies
    alliesCW_.push_back(allies_[0]);        // YOU

    DWORD64 address = exe_->getAddress();   // exe base address
    // 0x0188C540 #NEW ADDRESS
    address += 0x0188C540;                  // address offset

    ReadProcessMemory(proc->getHandle(), reinterpret_cast<LPCVOID>(address), &address, sizeof(DWORD64), 0);
    address += 0x2E8;
    alliesCW_.push_back(new AllyCW(address));


    for(int i = 0; i < 6; i++)
    {
        alliesCW_.push_back(new AllyCW(address += 0x48));
    }
}

// get the number of party members
void x64::updateNumberOfPartyMembers(Process* proc, int &partyMembers)
{
    ReadProcessMemory(proc->getHandle(), reinterpret_cast<LPCVOID>(numberOfPartyMembers_->getMemoryAddress64(proc, exe_)), &partyMembers, sizeof(int), 0);
}

// check if currently crossworld party
void x64::checkCrossWorldParty(Process* proc)
{
    ReadProcessMemory(proc->getHandle(), reinterpret_cast<LPCVOID>(exe_->getAddress() + 0x18F22C4), &inCrossWorldParty_, 1, 0);
}