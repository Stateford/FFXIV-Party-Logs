#pragma once

#include "player.h"

class Ally : public Player
{
public:
    Ally(DWORD64);
    ~Ally();
    void display();
};
