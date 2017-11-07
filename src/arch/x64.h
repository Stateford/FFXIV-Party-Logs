#pragma once

#include "arch.h"

class x64 : public Arch
{
public:
    x64(Process*);
    ~x64();
    void createAllies() override;
    void updateNumberOfPartyMembers(Process*, int&) override;
};

