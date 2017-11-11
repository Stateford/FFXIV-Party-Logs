/*
* This file is for running the game directx9. When the game is launched in directx9, the game
* is running in 32-bit, which requires being able to read and add 32-bit hexadecimal addresses.
* Storing the address with the sizeof a DWORD64 will return the wrong address.
*/
#include "x86.h"
#include <iostream>


x86::x86(Process* proc)
{
    // handle error when getting invalid module
    numberOfPartyMembers_ = new Offset({ 0x11404DC, 0x1C, 0x10, 0x104, 0x1C });
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
    createAllies();
}


x86::~x86()
{
    deleteAllies();
    delete exe_;
    delete numberOfPartyMembers_;
    exe_ = nullptr;
    numberOfPartyMembers_ = nullptr;
}

void x86::createAllies()
{
    allies_.reserve(8);
    // dx9 32-bit offsets
    allies_.push_back(new YOU(0x115E431));
    allies_.push_back(new Ally(0x117AA30));
    allies_.push_back(new Ally(0x117AC50));
    allies_.push_back(new Ally(0x117AE70));
    allies_.push_back(new Ally(0x117B090));
    allies_.push_back(new Ally(0x117B2B0));
    allies_.push_back(new Ally(0x117B4D0));
    allies_.push_back(new Ally(0x117B6F0));
    allies_.push_back(new Ally(0x117B910));
}


void x86::updateNumberOfPartyMembers(Process *proc, int &partyMembers)
{
    ReadProcessMemory(proc->getHandle(), (void*)(numberOfPartyMembers_->getMemoryAddress(proc, exe_)), &partyMembers, sizeof(int), 0);
}