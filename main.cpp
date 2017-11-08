#include "src/menu.h"
#include <thread>

int main()
{

    Menu menu;
    //menu.start();

    std::thread t1([=, &menu] { menu.start(); });
    t1.join();

    system("pause");
    return 0;
}