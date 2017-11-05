#include "menu.h"
#include <iostream>

// constructor
Menu::Menu()
{
    fflogs_ = new FFXIV();
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
    fflogs_->updateNames();
    hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole_, 7);
    // display title
    std::cout << "FFXIV Party Logs\n";
    std::cout << "--------------------\n";

    // this is for debugging purposes
    std::cout << "Number of people in the party: ";
    int numOfPartyMembers;
    ReadProcessMemory(fflogs_->ffxiv_->getHandle(), (void*)(fflogs_->numberOfPartyMembers_->getMemoryAddress(fflogs_->ffxiv_, fflogs_->exe_)), &numOfPartyMembers, sizeof(int), 0);
    std::cout << numOfPartyMembers << "\n";


    for(int i = 0; i < fflogs_->filteredAllies_.size(); i++)
    {
        SetConsoleTextAttribute(hConsole_, 7);
        if(i == currentMenuSelection_)
        {
            SetConsoleTextAttribute(hConsole_, 16);
        }
        fflogs_->filteredAllies_[i]->display();
    }
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
    system("CLS");
    displayAllies();

    while(true)
    {
        DWORD count;

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
                    if(currentMenuSelection_ < fflogs_->allies_.size() - 1)
                    {
                        currentMenuSelection_++;
                        redraw();
                    }
                    break;
                case VK_RETURN:
                    fflogs_->allies_[currentMenuSelection_]->openBrowser();
                    break;
                default:
                    redraw();
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