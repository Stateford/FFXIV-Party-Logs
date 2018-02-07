#include "you.h"

#include <iostream>

YOU::YOU(DWORD64 address)
{
    address_ = address;
}

YOU::~YOU()
{
    
}

void YOU::display()
{
    std::cout << "YOU (" << name_ << ")" << "\n";
}

void YOU::updateName(Process* proc, Module* exe)
{
    ReadProcessMemory(proc->getHandle(), reinterpret_cast<LPCVOID>(exe->getAddress() + address_), &name_, 80, 0);
}
