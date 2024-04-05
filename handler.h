#include <vector>
#include "Features/Feature.h"

#pragma once
class handler
{
public:
	static std::vector<Feature*> features;
	static void draw();
	static void add_feature(Feature* feature);
};