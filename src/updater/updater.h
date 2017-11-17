#pragma once

#include <string>
#include <vector>

class Updater
{
private:
    std::wstring apiUrl_;
    std::wstring currentVersion_;
    std::wstring body_;
    std::wstring releaseUrl_;
    enum MENU {CHECKING, UPDATEFOUND, NEXT};
    std::vector<std::string> options_ = { "Yes", "No" };
    int currentMenu_;
    int currentPosition_;
    void makeRequest();
public:
    Updater();
    ~Updater();
    bool compareVersion();
    void openUrl();
    void displayUpdate();
};