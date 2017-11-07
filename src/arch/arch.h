#pragma once

#include <vector>
#include <string>
#include "../process/module.h"
#include "../process/offset.h"
#include "../player/player.h"
#include "../player/you.h"
#include "../player/ally.h"

class Arch
{
protected:
    Module *exe_;
    Offset *numberOfPartyMembers_;
    std::vector<Player*> allies_;
    std::vector<Player*> filteredAllies_;
public:
    Arch();
    virtual ~Arch() = 0;
    virtual void createAllies() = 0;
    virtual void updateNumberOfPartyMembers(Process*, int&) = 0;
    static bool x64;
    void deleteAllies();
    bool checkArrayForDoubles(std::string);
    void filterAllies();
    void updateNames(Process*, int&);
    std::vector<Player*> getFilteredAllies();
};

