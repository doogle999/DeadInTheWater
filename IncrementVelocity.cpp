#include "IncrementVelocity.h"

IncrementVelocity::IncrementVelocity() {}

IncrementVelocity::~IncrementVelocity() {}

void IncrementVelocity::run(Entity& e)
{
	e.AXS(xVelocity) += e.AXS(xAcceleration) * Game::getTick();
	e.AXS(yVelocity) += e.AXS(yAcceleration) * Game::getTick();
	
	e.AXS(xAcceleration) = 0;
	e.AXS(yAcceleration) = 0;
};

std::vector<P::Ids> IncrementVelocity::getNecessaryProperties()
{
	return necessaryProperties;
};

const std::vector<P::Ids> IncrementVelocity::necessaryProperties = { P::Ids::xAcceleration, P::Ids::yAcceleration, P::Ids::xVelocity, P::Ids::yVelocity };