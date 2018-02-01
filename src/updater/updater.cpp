#include "updater.h"
#include "../bin/request.h"
#include <Windows.h>


Updater::Updater()
{
    currentVersion_ = L"1.0.4";
    apiUrl_ = L"http://idietmoran.com/ffxiv/party-logs/latest";
    currentMenu_ = CHECKING;
}

Updater::~Updater()
{
    
}

void Updater::makeRequest()
{
    Request::get(apiUrl_, body_);
}

bool Updater::compareVersion()
{
    makeRequest();

    if (body_.empty())
        return true;
    
    

    std::wstring version = body_.substr(body_.find(L"version"), body_.find(L",") - 3);
    version = version.substr(version.find(L":\"") + 2, version.size());

    // if current version is different than api version
    if(currentVersion_ != version)
    {
        releaseUrl_ = body_.substr(body_.find(L"url"), body_.find(L"}"));
        releaseUrl_ = releaseUrl_.substr(releaseUrl_.find(L":\"") + 2, releaseUrl_.size());
        releaseUrl_ = releaseUrl_.substr(0, releaseUrl_.size() - 2);
        return false;
    }
    
    return true;
}

void Updater::openUrl()
{
    ShellExecuteW(NULL, L"open", releaseUrl_.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void Updater::displayUpdate()
{
    if(!compareVersion())
    {
        std::cout << "Update has been found...\n";
        std::cout << "Press any key to update...";

        while(true)
        {
            if(GetAsyncKeyState(VK_RETURN))
            {
                openUrl();
                exit(0);
            }
        }
    }
}