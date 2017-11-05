#pragma once

#include "process.h"
#include <Windows.h>
#include <TlHelp32.h>

class Module
{
private:
    MODULEENTRY32 nModule;
    DWORD address_;
    TCHAR* moduleName_;
public:
    Module(TCHAR[]);
    ~Module();
    bool getModule(Process*);
    DWORD getAddress();
};