#pragma once

#include "arch.h"

class x64 : public Arch
{
public:
    x64(Process*);
    ~x64();
    void createAllies(Process*) override;
    void updateNumberOfPartyMembers(Process*, int&) override;
    void checkCrossWorldParty(Process*) override;
};

