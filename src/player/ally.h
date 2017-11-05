#pragma once

#include "player.h"

class Ally : public Player
{
public:
    Ally(DWORD);
    ~Ally();
    void display();
};
