#pragma once
#include "Feature.h"

class ModuleViewer :
    public Feature
{
    char* moduleSearch;
public:
    ModuleViewer();
    void Draw();
};