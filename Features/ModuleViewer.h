#pragma once
#include "MemoryViewer.h"
#include "Feature.h"

class ModuleViewer :
    public Feature
{
    MemoryViewer* memoryViewer = 0;
    char* moduleSearch;
public:
    ModuleViewer(MemoryViewer* memViewer);
    void Draw();
};