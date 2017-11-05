#include "ally.h"

#include <iostream>

Ally::Ally(DWORD address)
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
