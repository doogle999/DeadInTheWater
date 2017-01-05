#include "IncrementPosition.h"

IncrementPosition::IncrementPosition() {}

IncrementPosition::~IncrementPosition() {}

void IncrementPosition::run(Entity& e)
{
	e.AXS(xPosition) += e.AXS(xVelocity) * Game::getTick();
	e.AXS(yPosition) += e.AXS(yVelocity) * Game::getTick();
};

std::vector<P::Ids> IncrementPosition::getNecessaryProperties()
{
	return necessaryProperties;
};

const std::vector<P::Ids> IncrementPosition::necessaryProperties = { P::Ids::xPosition, P::Ids::yPosition, P::Ids::xVelocity, P::Ids::yVelocity };