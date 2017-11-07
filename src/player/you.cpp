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
