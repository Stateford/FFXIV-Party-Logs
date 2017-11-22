#include "menu.h"
#include <iostream>
#include <thread>
#include <chrono>

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
    //fflogs_->arch_->updateNames(fflogs_->ffxiv_, fflogs_->partyMembers_);
    int partyMembers = fflogs_->partyMembers_;

    // if currentMenuSelection is greater than the number of party members
    // set currentMenuSelection equal to number of party members so the
    // cursor doesn't go off screen
    if(currentMenuSelection_ > fflogs_->partyMembers_)
    {
        currentMenuSelection_ = fflogs_->partyMembers_;
    }
    
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
    }
    SetConsoleTextAttribute(hConsole_, 7);

    if(currentMenuSelection_ == partyMembers)
    {
        SetConsoleTextAttribute(hConsole_, 23);
    }
    std::cout << "ALL" << std::endl;

    // this prevents the colors from breaking
    SetConsoleTextAttribute(hConsole_, 7);
}

void Menu::redraw()
{
    system("CLS");
    displayAllies();
}

void Menu::alliesMenu(DWORD &mode, INPUT_RECORD &event, HANDLE &hstdin)
{
    
    mu_.lock();     // lock the thread
    system("CLS");  // clear the screen
    // display allies
    displayAllies();
    // set previous values
    prevPartySize_ = fflogs_->partyMembers_;
    prevCrossWorldStatus_ = fflogs_->arch_->getCrossWorldStatus();
    mu_.unlock();   // unlock the thread

    while(live_)
    {
        mu_.lock();     // lock the thread

        // checks if party size changes, or party changes to crossworld and displays the changes
        if(prevPartySize_ != fflogs_->partyMembers_ || prevCrossWorldStatus_ != fflogs_->arch_->getCrossWorldStatus())
        {
            prevPartySize_ = fflogs_->partyMembers_;
            prevCrossWorldStatus_ = fflogs_->arch_->getCrossWorldStatus();
            redraw();
        }

        // checks if console is currently focused
        bool isConsoleWindowFocussed = (GetConsoleWindow() == GetForegroundWindow());
        
        // checks key states
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
            if (currentMenuSelection_ < fflogs_->partyMembers_)
            {
                currentMenuSelection_++;
                redraw();
            }
        }

        if(GetAsyncKeyState(VK_RETURN) & 0x1 && isConsoleWindowFocussed)
        {
            std::thread t3([=] {
                if (currentMenuSelection_ == fflogs_->partyMembers_)
                {
                    fflogs_->arch_->openAll(fflogs_->partyMembers_);
                }

                else if (fflogs_->arch_->getCrossWorldStatus())
                {
                    fflogs_->arch_->getFilteredAlliesCW()[currentMenuSelection_]->openBrowser();
                }
                else
                {
                    fflogs_->arch_->getFilteredAllies()[currentMenuSelection_]->openBrowser();
                }
            });
            t3.join();
        }
        mu_.unlock();   // unlock the thread
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
}

void Menu::start()
{
    system("CLS");  // clear the screen
    // initalize variables to contain input
    DWORD mode;
    INPUT_RECORD event;
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hstdin, &mode);
    SetConsoleMode(hstdin, 0);

    // thread to update the menu
    std::thread t1([=, &mode, &event, &hstdin]{ alliesMenu(mode, event, hstdin); });
    // thread to get names
    std::thread t2([=] { 
        while (true)
        {
            mu_.lock(); // lock the thread
            // update names
            fflogs_->arch_->updateNames(fflogs_->ffxiv_, fflogs_->partyMembers_);
            mu_.unlock();   // unlock the thread
            // sleep the thread
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        }
    });

    t2.join();
    t1.join();
}
