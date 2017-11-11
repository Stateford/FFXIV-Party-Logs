#pragma once
#include <vector>
#include <map>
#include <string>
#include <Windows.h>

class Player
{
protected:
    static std::wstring clientId;
    //std::vector<std::wstring> regions_ = {L"NA", L"EU", L"JP"};
    std::vector<std::wstring> naServers_ = {L"adamantoise", L"balmung", L"cactaur", L"coeurl",
                                            L"faerie", L"gilgamesh", L"goblin", L"jenova",
                                            L"mateus", L"midgardsormr", L"sargatanas", L"siren",
                                            L"zalera", L"behemoth", L"brynhildr", L"diabolos",
                                            L"excalibur", L"exodus", L"famfrit", L"hyperion",
                                            L"lamia", L"leviathan", L"malboro", L"ultros"};
    std::vector<std::wstring> euServers_ = {L"cerberus", L"lich", L"louisoix", L"moogle",
                                            L"odin", L"omega", L"phoenix", L"ragnarok",
                                            L"shiva", L"zodiark"};
    std::vector<std::wstring> jpServers_ = {L"anima", L"asura", L"belias", L"chocobo", 
                                            L"hades", L"ixion", L"mandragora", L"masumune", 
                                            L"pandaemonium", L"shinryu", L"titan", L"alexander", 
                                            L"bahamut", L"durandal", L"fenrir", L"ifrit", 
                                            L"ridill", L"tiamat", L"ultima", L"valefor", 
                                            L"yojimba", L"zeromus", L"aegis", L"atomos", 
                                            L"carbuncle", L"garuda", L"gungnir", L"kujata", 
                                            L"ramuh", L"tonberry", L"typhon", L"unicorn"};
    std::wstring baseApiUrl_ = L"https://www.fflogs.com:443/v1/parses/character/";
    std::string baseUrl_ = "https://www.fflogs.com/search/?term=";
    std::wstring characterId_;
public:
    DWORD64 address_;
    char name_[80];
    virtual void display() = 0;
    bool characterCheck();
    void charRequest(std::wstring, std::vector<std::wstring>,  std::wstring, std::wstring&, int&);
    void naRequests(std::wstring, std::wstring&, int&);
    void euRequests(std::wstring, std::wstring&, int&);
    void jpRequests(std::wstring, std::wstring&, int&);
    void parseJson(std::wstring*&);
    void openBrowser();
    bool compare(Player*);
};