#include "OrientationIncrementer.h"

OrientationIncrementer::OrientationIncrementer() {}

OrientationIncrementer::~OrientationIncrementer() {}

void OrientationIncrementer::update()
{
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		A::Orientation& o = w->entities[ei[i]].AXS(Orientation);

		o.theta = o.theta + o.omega * Game::getTick();
		o.omega = o.omega + o.alpha * Game::getTick();
	}
}

std::vector<Attribute::Ids> OrientationIncrementer::getNecessaryProperties()
{
	return OrientationIncrementer::necessaryProperties;
}

const std::vector<Attribute::Ids> OrientationIncrementer::necessaryProperties = { Attribute::Ids::Orientation };