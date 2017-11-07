#pragma once
#include "arch.h"

class x86 : public Arch
{
public:
    x86(Process*);
    ~x86();
    void updateNumberOfPartyMembers(Process*, int&) override;
    void createAllies() override;
};

