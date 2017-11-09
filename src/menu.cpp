#include "menu.h"
#include <iostream>
#include <thread>

// constructor
Menu::Menu()
{
    fflogs_ = new FFXIV();
    hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
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
    //fflogs_->arch_->updateNames(fflogs_->ffxiv_, fflogs_->partyMembers_);
    

    SetConsoleTextAttribute(hConsole_, 7);
    // display title
    std::cout << "FFXIV Party Logs\n";
    std::cout << "--------------------\n";
    

    /*
     * NOTE: It's impossible to determine people no longer in the party without parsing the chat log
     * TODO: Maybe in the future
     */

    for (int i = 0; i < fflogs_->arch_->getFilteredAllies().size(); i++)
    {
        SetConsoleTextAttribute(hConsole_, 7);
        if (i == currentMenuSelection_)
        {
            SetConsoleTextAttribute(hConsole_, 23);
        }
        fflogs_->arch_->getFilteredAllies()[i]->display();
    }
    // this prevents the colors from breaking
    SetConsoleTextAttribute(hConsole_, 7);
}


void Menu::redraw()
{
    std::cout.flush();
    system("CLS");
    displayAllies();
}

void Menu::alliesMenu(DWORD &mode, INPUT_RECORD &event, HANDLE &hstdin)
{
    std::cout.flush();
    system("CLS");
    displayAllies();
    prevPartySize_ = fflogs_->partyMembers_;

    while(true)
    {

        if(prevPartySize_ != fflogs_->partyMembers_)
        {
            prevPartySize_ = fflogs_->partyMembers_;
            redraw();
        }
        bool isConsoleWindowFocussed = (GetConsoleWindow() == GetForegroundWindow());
        
        if(GetAsyncKeyState(VK_ESCAPE) & 0x1 && isConsoleWindowFocussed)
        {
            exit(0);
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
            if (currentMenuSelection_ < fflogs_->arch_->getFilteredAllies().size() - 1)
            {
                currentMenuSelection_++;
                redraw();
            }
        }

        if(GetAsyncKeyState(VK_RETURN) & 0x1 && isConsoleWindowFocussed)
        {
            fflogs_->arch_->getFilteredAllies()[currentMenuSelection_]->openBrowser();
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

    std::thread t2([=] { 
        while (true)
        {
            fflogs_->arch_->updateNames(fflogs_->ffxiv_, fflogs_->partyMembers_);
            Sleep(2);
        } 
    });

    // these threads will run in parallel.
    // one thread will power the menu
    // the other thread will updatenames
    t1.join();
    t2.join();
}
