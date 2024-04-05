#pragma once
#include "Feature.h"

class ProcessViewer :
    public Feature
{
    char* processSearch;
public:
    ProcessViewer();
    void Draw();
};

