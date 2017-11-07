#include "arch.h"


bool Arch::x64 = true;

Arch::Arch()
{

}


Arch::~Arch()
{

}

void Arch::deleteAllies()
{
    for (auto &p : allies_)
    {
        delete p;
        p = nullptr;
    }
}

bool Arch::checkArrayForDoubles(std::string name)
{
    for (auto &p : filteredAllies_)
    {
        if (p->name_ == name)
        {
            return true;
        }
    }
    return false;
}

void Arch::filterAllies()
{
    filteredAllies_.clear();
    filteredAllies_.reserve(8);
    filteredAllies_.push_back(allies_[0]);
    for (auto &p : allies_)
    {
        if (!checkArrayForDoubles(p->name_))
        {
            filteredAllies_.push_back(p);
        }
    }
}

void Arch::updateNames(Process* proc, int &partyMembers)
{
    for (auto &p : allies_)
    {
        ReadProcessMemory(proc->getHandle(), (void*)(exe_->getAddress() + p->address_), &p->name_, 80, 0);
    }
    filterAllies();

    updateNumberOfPartyMembers(proc, partyMembers);
}



std::vector<Player*> Arch::getFilteredAllies()
{
    return filteredAllies_;
}