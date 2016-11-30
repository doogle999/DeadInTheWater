#include "KeyboardVelocity.h"

KeyboardVelocity::KeyboardVelocity() {}

KeyboardVelocity::~KeyboardVelocity() {}

void KeyboardVelocity::run(Entity& e)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		e.AXS(xVelocity) = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		e.AXS(xVelocity) = 1;
	}
	else
	{
		e.AXS(xVelocity) = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		e.AXS(yVelocity) = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		e.AXS(yVelocity) = 1;
	}
	else
	{
		e.AXS(yVelocity) = 0;
	}
};

std::vector<P::Ids> KeyboardVelocity::getNecessaryProperties()
{
	return necessaryProperties;
};

const std::vector<P::Ids> KeyboardVelocity::necessaryProperties = { P::Ids::xVelocity, P::Ids::yVelocity };