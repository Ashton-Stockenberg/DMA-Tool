#pragma once
#include "../ImGui/imgui.h"
#include "../Memory/Memory.h"
#include <string>
#include <Windows.h>
#include <vector>

class Feature
{
public:
	std::string name;
	bool draw = false;
	virtual void Draw();
};

