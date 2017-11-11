#include "player.h"
#include "../bin/request.h"
#include <iostream>
#include <codecvt>
#include <thread>

std::wstring Player::clientId = L"ae759d44880e5523d5fb3b59df028c64";

bool Player::characterCheck()
{
    // convert name_ from char to wstring
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(name_);
    // issue lies here for char strings
    std::wstring tempName = wide;
    std::wstring fullName = tempName.substr(0, tempName.find(L" ")) + L"%20" + tempName.substr((tempName.find(L" ") + 1), tempName.size());

    int characterCount = 0;
    
    std::wstring prevBody;
    /*
     * do it by each datacenter
     */
    //std::thread t1([=, &prevBody, &characterCount] { naRequests(fullName, prevBody, characterCount); });
    //std::thread t2([=, &prevBody, &characterCount] { euRequests(fullName, prevBody, characterCount); });
    //std::thread t3([=, &prevBody, &characterCount] { jpRequests(fullName, prevBody, characterCount); });
    
    naRequests(fullName, prevBody, characterCount);
    euRequests(fullName, prevBody, characterCount);
    jpRequests(fullName, prevBody, characterCount);

    //t1.join();
    //t2.join();
    //t3.join();
    

    // std::wcout << prevBody << std::endl;

    if(characterCount < 2 && characterCount > 0 && prevBody != L"" && !prevBody.empty())
    {
        prevBody = prevBody.substr(prevBody.find(L"character_id"), prevBody.size());
        prevBody = prevBody.substr(prevBody.find_first_of(L": ") + 2, prevBody.find_first_of(L","));
        prevBody.erase(std::remove_if(prevBody.begin(), prevBody.end(), ::isspace), prevBody.end());
        prevBody.pop_back();
        //parseJson(prevBody);
        characterId_ = prevBody;
        return true;
    }

    return false;
}

void Player::charRequest(std::wstring fullName, std::vector<std::wstring> dataCenter, std::wstring region, std::wstring &prevBody, int &characterCount)
{
    for (auto &p : dataCenter)
    {
        std::wstring body;
        // temp url
        std::wstring apiUrl = baseApiUrl_;
        //Chelsea % 20Chelsea / Hyperion / EU / ? api_key = ${ clientID }
        // https://www.fflogs.com:443/v1/parses/character/Chelsea%20Chelsea/hyperion/na/?api_key=ae759d44880e5523d5fb3b59df028c64
        // build url
        apiUrl += fullName + L"/" + p + L"/" + region + L"/?api_key=" + clientId;
        std::wcout << apiUrl << std::endl;
        Request::get(apiUrl, body);

        if (!body.empty() && body.size() > 15)
        {
            std::wcout << body << std::endl;
            prevBody = body;

            characterCount++;
        }
    }
}


void Player::naRequests(std::wstring fullName, std::wstring& prevBody, int& characterCount)
{
    std::vector<std::thread*> threads;
    for (auto &p : naServers_)
    {
        std::wstring body;
        // temp url
        std::wstring apiUrl = baseApiUrl_;
        //Chelsea % 20Chelsea / Hyperion / EU / ? api_key = ${ clientID }
        // https://www.fflogs.com:443/v1/parses/character/Chelsea%20Chelsea/hyperion/na/?api_key=ae759d44880e5523d5fb3b59df028c64
        // build url
        apiUrl += fullName + L"/" + p + L"/na/?api_key=" + clientId;
        //std::wcout << apiUrl << std::endl;

        threads.push_back(new std::thread([=, &body, &prevBody, &characterCount] { 
            Request::get(apiUrl, body); 
            if (!body.empty() && body.size() > 15)
            {
                prevBody = body;
                characterCount++;
            } 
        }));

    }

    for(auto &p: threads)
    {
        p->join();
    }
}

void Player::euRequests(std::wstring fullName, std::wstring& prevBody, int& characterCount)
{
    std::vector<std::thread*> threads;
    for (auto &p : naServers_)
    {
        std::wstring body;
        // temp url
        std::wstring apiUrl = baseApiUrl_;
        //Chelsea % 20Chelsea / Hyperion / EU / ? api_key = ${ clientID }
        // https://www.fflogs.com:443/v1/parses/character/Chelsea%20Chelsea/hyperion/na/?api_key=ae759d44880e5523d5fb3b59df028c64
        // build url
        apiUrl += fullName + L"/" + p + L"/eu/?api_key=" + clientId;
        //std::wcout << apiUrl << std::endl;

        threads.push_back(new std::thread([=, &body, &prevBody, &characterCount] {
            Request::get(apiUrl, body);
            if (!body.empty() && body.size() > 15)
            {
                prevBody = body;
                characterCount++;
            }
        }));

    }

    for (auto &p : threads)
    {
        p->join();
    }
}

void Player::jpRequests(std::wstring fullName, std::wstring& prevBody, int& characterCount)
{
    std::vector<std::thread*> threads;
    for (auto &p : naServers_)
    {
        std::wstring body;
        // temp url
        std::wstring apiUrl = baseApiUrl_;
        //Chelsea % 20Chelsea / Hyperion / EU / ? api_key = ${ clientID }
        // https://www.fflogs.com:443/v1/parses/character/Chelsea%20Chelsea/hyperion/na/?api_key=ae759d44880e5523d5fb3b59df028c64
        // build url
        apiUrl += fullName + L"/" + p + L"/jp/?api_key=" + clientId;
        //std::wcout << apiUrl << std::endl;

        threads.push_back(new std::thread([=, &body, &prevBody, &characterCount] {
            Request::get(apiUrl, body);
            if (!body.empty() && body.size() > 15)
            {
                prevBody = body;
                characterCount++;
            }
        }));

    }

    for (auto &p : threads)
    {
        p->join();
    }
}

void Player::parseJson(std::wstring *&body)
{
    *body = body->substr(body->find(L"character_id"), body->size());
    //auto charIdBegin = body->find_first_of(L": ");
    //auto charIdEnd = body->find_first_of(L",");
    *body = body->substr(body->find_first_of(L": ") + 2, body->find_first_of(L","));
    body->erase(std::remove_if(body->begin(), body->end(), ::isspace), body->end());
    body->pop_back();
    body = body;
}

void Player::openBrowser()
{
    std::string fullUrl = baseUrl_;
    fullUrl += name_;
    std::string tempName = name_;

    std::string firstName = tempName.substr(0, tempName.find(" "));
    std::string lastName = tempName.substr((tempName.find(" ") + 1), tempName.size());

    std::string fullName = firstName + "%20" + lastName;
    
    //if(!getCharacterId())
    //{
    //    ShellExecute(NULL, "open", (baseUrl_ + fullName).c_str(), NULL, NULL, SW_SHOWNORMAL);
    //}

    if (characterCheck())
    {
        std::wstring url = L"https://www.fflogs.com/character/id/";
        url += characterId_;
        ShellExecuteW(NULL, L"open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
    }
    else
    {
        ShellExecute(NULL, "open", (baseUrl_ + fullName).c_str(), NULL, NULL, SW_SHOWNORMAL);
    }
 
}

bool Player::compare(Player* player)
{
    if(name_ == player->name_)
    {
        return true;
    }
    return false;
}