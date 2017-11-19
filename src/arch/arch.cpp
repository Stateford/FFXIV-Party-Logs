/*
 * Abstract class that is a base for x64, and x86. contains shared methods
 * for each derived class
 */

#include "arch.h"
#include <thread>

bool Arch::x64 = false;

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
        if (p->name_ == name )
        {
            return true;
        }
    }
    return false;
}

bool Arch::checkArrayForDoublesCW(std::string name)
{
    for (auto &p : filteredAlliesCW_)
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
    filteredAlliesCW_.clear();
    //filteredAllies_.reserve(8);
    filteredAllies_.push_back(allies_[0]);
    filteredAlliesCW_.push_back(alliesCW_[0]);

    for (auto &p : allies_)
    {
        // dont add doubles or empty arrays
        if (!checkArrayForDoubles(p->name_) && p->name_[0] != NULL)
        {
            filteredAllies_.push_back(p);
        }
    }

    for(auto &p : alliesCW_)
    {
        if(!checkArrayForDoublesCW(p->name_) && p->name_[0] != NULL)
        {
            filteredAlliesCW_.push_back(p);
        }
    }

}


void Arch::updateNames(Process* proc, int &partyMembers)
{
    for (auto &p : allies_)
    {
        p->updateName(proc, exe_);
    }
    for(auto &p : alliesCW_)
    {
        p->updateName(proc, exe_);
    }

    filterAllies();

    updateNumberOfPartyMembers(proc, partyMembers);
    checkCrossWorldParty(proc);
}



std::vector<Player*> Arch::getFilteredAllies()
{
    return filteredAllies_;
}

std::vector<Player*> Arch::getFilteredAlliesCW()
{
    return filteredAlliesCW_;
}

bool Arch::getCrossWorldStatus()
{
    return inCrossWorldParty_;
}

// opens all users in the web broswer in parallel
void Arch::openAll(int partySize)
{
    if (getCrossWorldStatus())
    {
        // this will be garbage collected automatically thanks to RAII
        std::vector<std::thread*> threads;
        // create new threads
        for (int i = 0; i < partySize; i++)
        {
            threads.push_back(new std::thread([=] 
            {
                filteredAlliesCW_[i]->openBrowser();
            }));
        }

        // join all threads
        for(auto &p : threads)
        {
            p->join();
        }
    }
    else
    {
        // this will be garbage collected automatically thanks to RAII
        std::vector<std::thread*> threads;
        // create new threads
        for (int i = 0; i < partySize; i++)
        {
            threads.push_back(new std::thread([=]
            {
                filteredAllies_[i]->openBrowser();
            }));
        }
        // join all threads
        for(auto &p : threads)
        {
            p->join();
        }
    }
}