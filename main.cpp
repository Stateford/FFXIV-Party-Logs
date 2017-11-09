#include "src/menu.h"
#include <thread>
#include <iostream>

void foo(int &a)
{
    while(true)
    {
        a++;
    }
}

void bar(int a)
{
    while(true)
    {
        std::cout << a << std::endl;
    }
}

int main()
{
    int a = 0;
    Menu menu;

    std::thread t1([=, &menu] { menu.start(); });
    t1.join();

    return 0;
}