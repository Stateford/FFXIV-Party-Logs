#pragma once

#include "process.h"
#include <Windows.h>
#include <TlHelp32.h>

class Module
{
private:
    MODULEENTRY32 nModule;
    DWORD64 address_;
    bool bit64_;
    TCHAR* moduleName_;
public:
    Module(TCHAR[]);
    ~Module();
    bool getModule(Process*);
    bool getModule32bit(Process*);
    DWORD64 getAddress();
};