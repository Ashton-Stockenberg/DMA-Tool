#pragma once
#include "Feature.h"
#include <sstream>
#include <iomanip>

class MemoryViewer :
    public Feature
{

public:
    MemoryViewer();
    void Draw();
};

std::string hexStr(unsigned char* data, int len);