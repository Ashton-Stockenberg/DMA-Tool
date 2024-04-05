#include "handler.h"
#include <iostream>


std::vector<Feature*> handler::features;

void handler::draw()
{
	for (auto f : features)
	{
		if (f->draw)
		{
			f->Draw();
		}
	}
}

void handler::add_feature(Feature* feature)
{
	features.push_back(feature);
}
