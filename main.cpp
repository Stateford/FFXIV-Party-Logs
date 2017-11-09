#include "src/menu.h"
#include <thread>
#include <iostream>


int main()
{
    Menu menu;

    std::thread t1([=, &menu] { menu.start(); });
    t1.join();

    return 0;
}
