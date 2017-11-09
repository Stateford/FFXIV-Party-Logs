#pragma once

#include "ffxiv.h"

class Menu
{
private:
    int currentMenuSelection_;
    int prevPartySize_;
    FFXIV *fflogs_;
    bool live_;
    // console objects
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
