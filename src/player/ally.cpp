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
