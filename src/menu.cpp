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
    fflogs_->arch_->updateNames(fflogs_->ffxiv_, fflogs_->partyMembers_);
    

    SetConsoleTextAttribute(hConsole_, 7);
    // display title
    std::cout << "FFXIV Party Logs\n";
    std::cout << "--------------------\n";

    // this is for debugging purposes
    std::cout << "Number of people in the party: ";
    //std::cout << fflogs_->partyMembers_ << "\n";
    std::cout << fflogs_->arch_->getFilteredAllies().size() << "\n";


    /*
     * if the size of filteredAllies_ is less than party members,
     * display number of elements in filteredAllies_ instead of
     * party members, or cause vector overflow
     */
    int numOfPartyMembers;

    if(fflogs_->arch_->getFilteredAllies().size() < fflogs_->partyMembers_)
    {
        numOfPartyMembers = fflogs_->arch_->getFilteredAllies().size();
    }
    else
    {
        numOfPartyMembers = fflogs_->partyMembers_;
    }

    for (int i = 0; i < numOfPartyMembers; i++)
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
        DWORD count;

        //fflogs_->arch_->updateNames(fflogs_->ffxiv_, fflogs_->partyMembers_);

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

        /*
        else if(WaitForSingleObject(hstdin, 0) == WAIT_OBJECT_0)
        {
            ReadConsoleInput(hstdin, &event, 1, &count);
            // on keydown
            if((event.EventType == KEY_EVENT) && event.Event.KeyEvent.bKeyDown)
            {
                switch(event.Event.KeyEvent.wVirtualKeyCode)
                {
                case VK_ESCAPE:
                    exit(0);
                case VK_UP:
                    if(currentMenuSelection_ > 0)
                    {
                        currentMenuSelection_--;
                        redraw();
                    }
                    break;
                case VK_DOWN:
                    if(currentMenuSelection_ < fflogs_->arch_->getFilteredAllies().size() - 1)
                    {
                        currentMenuSelection_++;
                        redraw();
                    }
                    break;
                case VK_RETURN:
                    fflogs_->arch_->getFilteredAllies()[currentMenuSelection_]->openBrowser();
                    break;
                default:
                    //redraw();
                    break;
                }
            }
        }
        */
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

    t1.join();
    t2.join();
    //alliesMenu(mode, event, hstdin);
}
