#include "menu.h"
#include <iostream>
#include <thread>

// constructor
Menu::Menu()
{
    fflogs_ = new FFXIV();
    hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
    live_ = true;
}

// deconstructor
Menu::~Menu()
{
    delete fflogs_;
    fflogs_ = nullptr;
}

void Menu::displayAllies()
{
    // update play characters names
    fflogs_->arch_->updateNames(fflogs_->ffxiv_, fflogs_->partyMembers_);
    
    int partyMembers = fflogs_->partyMembers_;
    SetConsoleTextAttribute(hConsole_, 7);
    // display title
    std::cout << "FFXIV Party Logs\n";
    std::cout << "--------------------";
    
    if(fflogs_->arch_->getCrossWorldStatus())
    {
        SetConsoleTextAttribute(hConsole_, 13);
        std::cout << "\nCROSSWORLD PARTY" << std::endl;

        if(fflogs_->arch_->getFilteredAlliesCW().size() < fflogs_->partyMembers_)
        {
            partyMembers = fflogs_->arch_->getFilteredAlliesCW().size();
        }

        for (int i = 0; i < partyMembers; i++)
        {
            SetConsoleTextAttribute(hConsole_, 7);
            // highlight current line
            if (i == currentMenuSelection_)
            {
                SetConsoleTextAttribute(hConsole_, 23);
            }
            fflogs_->arch_->getFilteredAlliesCW()[i]->display();
        }
        // this prevents the colors from breaking

    }
    // if normal party
    else
    {
        SetConsoleTextAttribute(hConsole_, 3);
        std::cout << "\nNORMAL PARTY" << std::endl;

        if (fflogs_->arch_->getFilteredAllies().size() < fflogs_->partyMembers_)
        {
            partyMembers = fflogs_->arch_->getFilteredAllies().size();
        }

        for (int i = 0; i < partyMembers; i++)
        {
            SetConsoleTextAttribute(hConsole_, 7);
            // higlight current line
            if (i == currentMenuSelection_)
            {
                SetConsoleTextAttribute(hConsole_, 23); 
            }
            fflogs_->arch_->getFilteredAllies()[i]->display();
        }
        // this prevents the colors from breaking
    }
    /*
     * NOTE: It's impossible to determine people no longer in the party without parsing the chat log
     * TODO: Maybe in the future
     */

    
    SetConsoleTextAttribute(hConsole_, 7);
}


void Menu::redraw()
{
    //std::cout.flush();
    system("CLS");
    displayAllies();
}

void Menu::alliesMenu(DWORD &mode, INPUT_RECORD &event, HANDLE &hstdin)
{
    //std::cout.flush();
    system("CLS");
    displayAllies();
    prevPartySize_ = fflogs_->partyMembers_;
    prevCrossWorldStatus_ = fflogs_->arch_->getCrossWorldStatus();

    while(live_)
    {
        fflogs_->arch_->updateNames(fflogs_->ffxiv_, fflogs_->partyMembers_);


        // checks if party size changes, or party changes to crossworld and displays the changes
        if(prevPartySize_ != fflogs_->partyMembers_ || prevCrossWorldStatus_ != fflogs_->arch_->getCrossWorldStatus())
        {
            prevPartySize_ = fflogs_->partyMembers_;
            prevCrossWorldStatus_ = fflogs_->arch_->getCrossWorldStatus();
            redraw();
        }

        bool isConsoleWindowFocussed = (GetConsoleWindow() == GetForegroundWindow());
        
        if(GetAsyncKeyState(VK_ESCAPE) & 0x1 && isConsoleWindowFocussed)
        {
            live_ = false;
        }

        if(GetAsyncKeyState(VK_UP) & 0x1 && isConsoleWindowFocussed)
        {
            if (currentMenuSelection_ > 0)
            {
                currentMenuSelection_--;
                redraw();
            }
        }

        if(GetAsyncKeyState(VK_DOWN) & 0x1 && isConsoleWindowFocussed)
        {
            if (currentMenuSelection_ < fflogs_->partyMembers_ - 1)
            {
                currentMenuSelection_++;
                redraw();
            }
        }

        if(GetAsyncKeyState(VK_RETURN) & 0x1 && isConsoleWindowFocussed)
        {
            if(fflogs_->arch_->getCrossWorldStatus())
            {
                fflogs_->arch_->getFilteredAlliesCW()[currentMenuSelection_]->openBrowser();
            }
            else
            {
                fflogs_->arch_->getFilteredAllies()[currentMenuSelection_]->openBrowser();
            }
        }
        Sleep(1);
    }
}

void Menu::start()
{
    system("CLS");
    // initalize variables to contain input
    DWORD mode;
    INPUT_RECORD event;
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hstdin, &mode);
    SetConsoleMode(hstdin, 0);

    std::thread t1([=, &mode, &event, &hstdin] { alliesMenu(mode, event, hstdin); });

    t1.join();
}
