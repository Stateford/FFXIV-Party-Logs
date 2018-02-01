#include "ally.h"

#include <iostream>

Ally::Ally(DWORD64 address)
{
    address_ = address;
}

Ally::~Ally()
{
    
}

void Ally::display()
{
    std::cout << name_ << "\n";
}

void Ally::updateName(Process* proc, Module* exe)
{
    ReadProcessMemory(proc->getHandle(), reinterpret_cast<LPCVOID>(exe->getAddress() + address_), &name_, 80, 0);
}
