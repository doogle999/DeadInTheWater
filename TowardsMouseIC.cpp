#include "TowardsMouseIC.h"

TowardsMouseIC::TowardsMouseIC() {}

void TowardsMouseIC::input(Entity& e, sf::Window* w)
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		e.setPositionX(sf::Mouse::getPosition(*w).x);
		e.setPositionY(sf::Mouse::getPosition(*w).y);
	}
}

TowardsMouseIC::~TowardsMouseIC() {}
