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
void Module::getModule(Process *proc)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, proc->getPid());

    nModule.dwSize = sizeof(MODULEENTRY32);

    Module32First(hSnapshot, &nModule);
    do
    {
        if (!strcmp(nModule.szModule, moduleName_))
        {
            address_ = (DWORD)nModule.modBaseAddr;
        }
    } while (Module32Next(hSnapshot, &nModule));
}

DWORD Module::getAddress()
{
    return address_;
}