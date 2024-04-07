#include "Feature.h"

std::vector<Feature*> Feature::features;

Feature::Feature()
{
	Feature::features.push_back(this);
}

void Feature::Draw()
{
}

void Feature::DrawFeatures()
{
	for (auto f : Feature::features)
	{
		if (f->draw)
		{
			f->Draw();
		}
	}
}

std::vector<Feature*> Feature::GetFeatures()
{
	return std::vector<Feature*>(features);
}
