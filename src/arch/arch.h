#pragma once

#include <vector>
#include <string>
#include "../process/module.h"
#include "../process/offset.h"
#include "../player/player.h"
#include "../player/you.h"
#include "../player/ally.h"
#include "../player/allyCW.h"

class Arch
{
protected:
    Module *exe_;
    Offset *numberOfPartyMembers_;
    bool inCrossWorldParty_ = false;
    std::vector<Player*> allies_;
    std::vector<Player*> filteredAllies_;
    std::vector<Player*> alliesCW_;
    std::vector<Player*> filteredAlliesCW_;
public:
    Arch();
    virtual ~Arch() = 0;
    virtual void createAllies(Process*) = 0;
    virtual void updateNumberOfPartyMembers(Process*, int&) = 0;
    virtual void checkCrossWorldParty(Process*) = 0;
    static bool x64;
    void deleteAllies();
    bool checkArrayForDoubles(std::string);
    bool checkArrayForDoublesCW(std::string name);
    void filterAllies();
    void updateNames(Process*, int&);
    std::vector<Player*> getFilteredAllies();
    std::vector<Player*> getFilteredAlliesCW();
    bool getCrossWorldStatus();
    void openAll(int);
};

