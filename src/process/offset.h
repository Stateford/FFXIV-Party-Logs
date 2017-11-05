#include <vector>
#include <string>
#include <Windows.h>
#include "process.h"
#include "module.h"

class Offset
{
private:
    std::vector<DWORD> offsets_;
public:
    Offset(std::vector<DWORD> offset);
    ~Offset();
    DWORD getMemoryAddress(Process*, Module*);
};