#include "player.h"
#include "../bin/request.h"
#include <codecvt>


bool Player::getCharId()
{
    // convert name_ from char to wstring
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(name_);
    // issue lies here for char strings
    std::wstring tempName = wide;
    std::wstring fullName = tempName.substr(0, tempName.find(L" ")) + L"%20" + tempName.substr((tempName.find(L" ") + 1), tempName.size());

    std::wstring body;


    Request::get(baseUrlW_ + fullName, body);

    if (!body.empty())
    {
     

        if (body.find(L"/character/id/") == std::string::npos)
        {
            return false;
        }

        std::wstring tempBody = body.substr(body.find(L"/character/id/"), body.size());
        std::wstring tempBody2 = tempBody;
        body = tempBody.substr(0, tempBody.find_first_of(L"\""));
        tempBody2 = tempBody2.substr(tempBody2.find(L"</a>"), tempBody2.size());

        if (tempBody2.find(L"/character/id/") != std::wstring::npos)
        {
            return false;
        }

        characterId_ = body.substr(body.find_last_of(L"/") + 1, body.size());
        return true;
    }
    return false;
}

void Player::parseSearch(std::wstring &body)
{
    body = body.substr(body.find(L"/character/id/", body.size()));
    body = body.substr(0, body.find(L"\""));
}

void Player::openBrowser()
{
    
    if (getCharId())
    {
        std::wstring url = L"https://www.fflogs.com/character/id/" + characterId_;
        //url += characterId_;
        ShellExecuteW(nullptr, L"open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    }
    else
    {
        std::string tempName = name_;

        std::string firstName = tempName.substr(0, tempName.find(" "));
        std::string lastName = tempName.substr((tempName.find(" ") + 1), tempName.size());

        std::string fullName = firstName + "%20" + lastName;

        ShellExecute(NULL, "open", (baseUrl_ + fullName).c_str(), NULL, NULL, SW_SHOWNORMAL);
    }
    
}

bool Player::compare(Player* player)
{
    return name_ == player->name_;
}
