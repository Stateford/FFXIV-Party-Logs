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
    numberOfPartyMembers_ = new Offset({ 0x0180A038, 0x38, 0x18, 0x20, 0x20, 0x10 });

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
    // dx11 64-bit offsets
    allies_.push_back(new YOU(0x182AB51));
    allies_.push_back(new Ally(0x184BFD0));
    allies_.push_back(new Ally(0x184C1F0));
    allies_.push_back(new Ally(0X184C410));
    allies_.push_back(new Ally(0x184C630));
    allies_.push_back(new Ally(0x184C850));
    allies_.push_back(new Ally(0x184CA70));
    allies_.push_back(new Ally(0x184CC90));
    allies_.push_back(new Ally(0X184CEB0));
    
    // create crossworld allies
    alliesCW_.push_back(allies_[0]); // YOU
    DWORD64 address = exe_->getAddress();
    address += 0x017E86A0;

    ReadProcessMemory(proc->getHandle(), (void*)address, &address, sizeof(DWORD64), 0);
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
    ReadProcessMemory(proc->getHandle(), (void*)(numberOfPartyMembers_->getMemoryAddress64(proc, exe_)), &partyMembers, sizeof(int), 0);
}

// check if currently crossworld party
void x64::checkCrossWorldParty(Process* proc)
{
    ReadProcessMemory(proc->getHandle(), (void*)(exe_->getAddress() + 0x184AF8C), &inCrossWorldParty_, 1, 0);
}