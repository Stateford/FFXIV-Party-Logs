#pragma once
#include "../process/process.h"
#include <Windows.h>
#include <string>

class Player
{
public:
    std::string baseUrl_ = "https://www.fflogs.com/search/?term=";
    char name_[80];
    DWORD64 address_;
    virtual void display() = 0;
    void openBrowser();
    bool compare(Player*);
};