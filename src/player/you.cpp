#include "you.h"

#include <iostream>

YOU::YOU(DWORD address)
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
