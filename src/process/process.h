#pragma once

#include <string>
#include <Windows.h>

class Process
{
    DWORD pid_;
    HWND hWnd_;
    HANDLE pHandle_;
public:
    Process(std::string processName);
    ~Process();
    void getProcessId(std::string processName);
    HANDLE getHandle();
    DWORD getPid();
};