#include "menu.h"
#include <iostream>

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
    std::cout << fflogs_->partyMembers_ << "\n";

    for(int i = 0; i < fflogs_->partyMembers_; i++)
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

        fflogs_->arch_->updateNames(fflogs_->ffxiv_, fflogs_->partyMembers_);

        if(prevPartySize_ != fflogs_->partyMembers_)
        {
            prevPartySize_ = fflogs_->partyMembers_;
            redraw();
        }


        if(WaitForSingleObject(hstdin, 0) == WAIT_OBJECT_0)
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
                    if(currentMenuSelection_ < fflogs_->partyMembers_ - 1)
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

    alliesMenu(mode, event, hstdin);

}