#pragma once

#include "process/process.h"
#include "process/module.h"
#include "process/offset.h"

#include "player/ally.h"
#include <vector>

typedef DWORD MEM;

class FFXIV
{
    friend class Menu;
private:
    Module *exe_;
    Process *ffxiv_;
    char foo_[80];
    Offset *numberOfPartyMembers_;
    int partyMembers_;
    std::vector<Player*> allies_;
    std::vector<Player*> filteredAllies_;
public:
    FFXIV();
    ~FFXIV();
    void getAllies();
    void deleteAllies();
    void updateNames();
    void updateNumberOfPartyMembers();
    bool checkArrayForDoubles(std::string);
    void filterAllies();
};