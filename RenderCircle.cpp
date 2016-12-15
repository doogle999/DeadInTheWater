#include "RenderCircle.h"

RenderCircle::RenderCircle() {}

RenderCircle::~RenderCircle() {}

void RenderCircle::run(Entity& e)
{
	sf::CircleShape c(e.AXS(radius));

	c.setOrigin(e.AXS(radius), e.AXS(radius));

	c.setPosition(e.AXS(xPosition), e.AXS(yPosition));

	c.setFillColor(sf::Color(100, 250, 50));

	Game::window->draw(c);
};

std::vector<P::Ids> RenderCircle::getNecessaryProperties()
{
	return necessaryProperties;
};

const std::vector<P::Ids> RenderCircle::necessaryProperties = { P::Ids::xPosition, P::Ids::yPosition, P::Ids::radius };