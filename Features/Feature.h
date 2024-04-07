#pragma once
#include "../ImGui/imgui.h"
#include "../Memory/Memory.h"
#include <string>
#include <Windows.h>
#include <vector>

class Feature
{
	static std::vector<Feature*> features;
public:
	std::string name;
	bool draw = false;

	Feature();
	virtual void Draw();

	static void DrawFeatures();
	static std::vector<Feature*> GetFeatures(); 
};

