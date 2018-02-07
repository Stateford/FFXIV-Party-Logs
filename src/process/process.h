#pragma once

#include <string>
#include <Windows.h>

class Process
{
    DWORD pid_;
    HWND hWnd_;
    HANDLE pHandle_;
public:
    Process(const std::string &processName);
    ~Process();
    void getProcessId(const std::string &processName);
    HANDLE getHandle();
    DWORD getPid();
};