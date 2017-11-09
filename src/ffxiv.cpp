#include "ffxiv.h"
#include "arch/x64.h"
#include "arch/x86.h"
#include <iostream>

// constructor
FFXIV::FFXIV()
{
    ffxiv_ = new Process("FINAL FANTASY XIV");

    arch_ = new x64(ffxiv_);

    if(!Arch::x64)
    {
        delete arch_;
        arch_ = new x86(ffxiv_);
    }
    
}

// deconstructor
FFXIV::~FFXIV()
{
    delete ffxiv_;
    delete arch_;
    ffxiv_ = nullptr;
    arch_ = nullptr;
}

