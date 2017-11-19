#include "src/menu.h"
#include <Windows.h>
#include "src/updater/updater.h"

int main()
{
    SetConsoleTitle(TEXT("FFXIV Party Logs"));
    Updater update;
    update.displayUpdate();
    
    Menu menu;
    menu.start();

    return 0;
}
