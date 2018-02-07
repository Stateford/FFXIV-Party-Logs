/*
* This file is for running the game directx9. When the game is launched in directx9, the game
* is running in 32-bit, which requires being able to read and add 32-bit hexadecimal addresses.
* Storing the address with the sizeof a DWORD64 will return the wrong address.
*/
#include "x86.h"
#include <iostream>

// constructor
x86::x86(Process* proc)
{
    // handle error when getting invalid module
    numberOfPartyMembers_ = new Offset({ 0x011B6D74, 0x1C, 0x10, 0x10, 0x1C, 0x10 });
    exe_ = new Module("ffxiv.exe");
    if (!exe_->getModule32bit(proc))
    {
        std::cout << "Could not determine directx versions...\n";
        std::cout << "Could not detect the correct directx version...\n";
        Sleep(2000);
        std::cout << "Exiting...\n";
        Sleep(3000);
        exit(0);
    }
    createAllies(proc);
}

// destructor
x86::~x86()
{
    deleteAllies();
    delete exe_;
    delete numberOfPartyMembers_;
    exe_ = nullptr;
    numberOfPartyMembers_ = nullptr;
}

// create allies
void x86::createAllies(Process* proc)
{
    // dx9 32-bit offsets
    allies_.push_back(new YOU(0x11D7411));
    allies_.push_back(new Ally(0x11F3C00)); // 11F3C00
    allies_.push_back(new Ally(0x11F3E20)); // 11F3E20
    allies_.push_back(new Ally(0x11F4040));
    allies_.push_back(new Ally(0x11F4260));
    allies_.push_back(new Ally(0x11F4480)); //
    allies_.push_back(new Ally(0x11F46A0));
    allies_.push_back(new Ally(0x11F48C0));
    allies_.push_back(new Ally(0x11F4AE0));

    // create crossworld allies
    alliesCW_.push_back(allies_[0]); // YOU
    
    DWORD address = exe_->getAddress();
    address += 0x0109E5A4;

    ReadProcessMemory(proc->getHandle(), reinterpret_cast<LPCVOID>(address), &address, sizeof(DWORD), 0);
    address += 0x2E0;
    alliesCW_.push_back(new AllyCW(address));

    for (int i = 0; i < 6; i++)
    {
        alliesCW_.push_back(new AllyCW(address += 0x48));
    }
    
}

// get the number of party members
void x86::updateNumberOfPartyMembers(Process *proc, int &partyMembers)
{
    ReadProcessMemory(proc->getHandle(), reinterpret_cast<LPCVOID>(numberOfPartyMembers_->getMemoryAddress(proc, exe_)), &partyMembers, sizeof(int), 0);
}

// check if currently crossworld party
void x86::checkCrossWorldParty(Process* proc)
{
    // do nothing for the time being
    ReadProcessMemory(proc->getHandle(), reinterpret_cast<LPCVOID>(exe_->getAddress() + 0x11F2DA4), &inCrossWorldParty_, 1, 0);
}