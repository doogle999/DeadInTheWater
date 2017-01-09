#include "RenderShip.h"

RenderShip::RenderShip() {}

RenderShip::~RenderShip() {}

void RenderShip::run(Entity& e)
{
	sf::CircleShape c(e.AXS(radius));

	c.setOrigin(e.AXS(radius), e.AXS(radius));

	c.setPosition(e.AXS(xPosition), e.AXS(yPosition));

	c.setFillColor(sf::Color(100, 250, 50));

	Game::window->draw(c);
};

std::vector<P::Ids> RenderShip::getNecessaryProperties()
{
	return necessaryProperties;
};

const std::vector<P::Ids> RenderShip::necessaryProperties = { P::Ids::xPosition, P::Ids::yPosition, P::Ids::radius, P::Ids::xVelocity, P::Ids::yVelocity };