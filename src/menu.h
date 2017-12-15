#pragma once

#include <vector>
#include "player/player.h"
#include "ffxiv.h"

class Menu
{
    FFXIV *ffxiv_;
public:
    Menu();
    ~Menu();
    void menu();
    void draw();
};
