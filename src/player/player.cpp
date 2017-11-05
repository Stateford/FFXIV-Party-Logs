#include "player.h"
#include <iostream>

void Player::openBrowser()
{
    std::string fullUrl = baseUrl_;
    fullUrl += name_;
    std::string tempName = name_;

    std::string firstName = tempName.substr(0, tempName.find(" "));
    std::string lastName = tempName.substr((tempName.find(" ") + 1), tempName.size());

    std::string fullName = firstName + "%20" + lastName;

    ShellExecute(NULL, "open", (baseUrl_ + fullName).c_str(), NULL, NULL, SW_SHOWNORMAL);
}

bool Player::compare(Player* player)
{
    if(name_ == player->name_)
    {
        return true;
    }
    return false;
}