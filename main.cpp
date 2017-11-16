#include "src/menu.h"
#include <Windows.h>

int main()
{
    SetConsoleTitle(TEXT("FFXIV Party Logs"));
    Menu menu;
    menu.start();

    return 0;
}
