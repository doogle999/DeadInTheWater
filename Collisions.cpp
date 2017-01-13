#include "Collisions.h"

Collisions::Collisions() {}

Collisions::~Collisions() {}

std::vector<P::Ids> Collisions::getNecessaryProperties()
{
	return Collisions::necessaryProperties;
};

bool Collisions::collision(Entity& e)
{
	/*
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		if(&e != ei[i])
		{
			if(sqrt(pow(ei[i]->AXS(xPosition) - e.AXS(xPosition), 2) + pow(ei[i]->AXS(yPosition) - e.AXS(yPosition), 2)) < ei[i]->AXS(radius) + e.AXS(radius))
			{
				return true;
			}
		}
	}
	*/
	return false;
}

const std::vector<P::Ids> Collisions::necessaryProperties = { P::Ids::xPosition,  P::Ids::yPosition,  P::Ids::radius, P::Ids::xVelocity,  P::Ids::yVelocity };