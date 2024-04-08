#pragma once
#include "Feature.h"
#include <sstream>
#include <string>
#include <iomanip>

class MemoryViewer :
    public Feature
{
public:
    char inputBuffer[256];
    procModule currentModule = {};
    uintptr_t address = 0;
    MemoryViewer();
    void Draw();
};

std::string hexStr(unsigned char* data, int len);
uintptr_t hexNum(std::string data);