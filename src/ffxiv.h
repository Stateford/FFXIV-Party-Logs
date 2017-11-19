#pragma once

#include "process/process.h"
#include "process/module.h"
#include "arch/arch.h"

#include "player/ally.h"

class FFXIV
{
    friend class Menu;
private:
    Process *ffxiv_;
    int partyMembers_;
    Arch *arch_;
public:
    FFXIV();
    ~FFXIV();
};