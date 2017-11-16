#pragma once

#include "player.h"

class AllyCW : public Player
{
public:
    AllyCW(DWORD64);
    ~AllyCW();
    void display();
    void updateName(Process*, Module*);
};
