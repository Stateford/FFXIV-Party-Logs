#include <vector>
#include <string>
#include <Windows.h>
#include "process.h"
#include "module.h"

class Offset
{
private:
    std::vector<DWORD64> offsets_;
public:
    Offset(std::vector<DWORD64> offset);
    ~Offset();
    DWORD64 getMemoryAddress(Process*, Module*);
    DWORD64 getMemoryAddress64(Process* proc, Module* module);
};