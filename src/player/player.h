#pragma once
#include <vector>
#include <map>
#include <string>
#include <Windows.h>
#include "../process/module.h"
#include "../process/process.h"

class Player
{
protected:
    static std::wstring clientId;
    std::wstring baseApiUrl_ = L"https://www.fflogs.com:443/v1/parses/character/";
    std::wstring baseUrlW_ = L"https://www.fflogs.com/search/?term=";
    std::string baseUrl_ = "https://www.fflogs.com/search/?term=";
    std::wstring characterId_;
public:
    DWORD64 address_;
    char name_[80];
    virtual void display() = 0;
    virtual void updateName(Process*, Module*) = 0;
    bool getCharId();
    void parseSearch(std::wstring&);
    void openBrowser();
    bool compare(Player*);
};