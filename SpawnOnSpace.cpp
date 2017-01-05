#include "SpawnOnSpace.h"

SpawnOnSpace::SpawnOnSpace() {}

SpawnOnSpace::~SpawnOnSpace() {}

void SpawnOnSpace::run(Entity& e)
{
	if(e.AXS(selected))
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			
		}
	}
};

std::vector<P::Ids> SpawnOnSpace::getNecessaryProperties()
{
	return necessaryProperties;
};

const std::vector<P::Ids> SpawnOnSpace::necessaryProperties = { P::Ids::xPosition, P::Ids::yPosition, P::Ids::xVelocity, P::Ids::yVelocity, P::Ids::reloadTime };