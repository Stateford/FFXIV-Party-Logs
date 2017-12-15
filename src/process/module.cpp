#include "module.h"

// constructor
Module::Module(TCHAR moduleName[])
{
    moduleName_ = moduleName;
}

// deconstructor
Module::~Module()
{

}

/*
* Classname: Module
* Method: getModule
* Argument: Process*
* Description: Finds the base address of a module based on the process provided
*/
bool Module::getModule(Process *proc)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, proc->getPid());

    nModule.dwSize = sizeof(MODULEENTRY32);

    Module32First(hSnapshot, &nModule);
    do
    {
        // BUG: This may break
        if (!strcmp(nModule.szModule, moduleName_))
        {
            address_ = (DWORD64)nModule.modBaseAddr;
            return true;
        }
    } while (Module32Next(hSnapshot, &nModule));

    return false;
}

bool Module::getModule32bit(Process *proc)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, proc->getPid());

    nModule.dwSize = sizeof(MODULEENTRY32);

    Module32First(hSnapshot, &nModule);
    do
    {
        if (!strcmp(nModule.szModule, moduleName_))
        {
            address_ = (DWORD64)nModule.modBaseAddr;
            return true;
        }
    } while (Module32Next(hSnapshot, &nModule));

    return false;
}


DWORD64 Module::getAddress()
{
    return address_;
}