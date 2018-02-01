#include "allyCW.h"
#include <iostream>

AllyCW::AllyCW(DWORD64 address)
{
    address_ = address;
}

AllyCW::~AllyCW()
{

}

void AllyCW::display()
{
    std::cout << name_ << "\n";
}

void AllyCW::updateName(Process* proc, Module* exe)
{
    ReadProcessMemory(proc->getHandle(), reinterpret_cast<LPCVOID>(address_), &name_, 80, 0);
}