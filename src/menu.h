#pragma once

#include "ffxiv.h"

class Menu
{
private:
    int currentMenuSelection_;
    FFXIV *fflogs_;
    // console object
    HANDLE hConsole_;
    HANDLE hstdin_;
public:
    Menu();
    ~Menu();
    void displayAllies();
    void redraw();
    void alliesMenu(DWORD&, INPUT_RECORD&, HANDLE&);
    void start();
};
