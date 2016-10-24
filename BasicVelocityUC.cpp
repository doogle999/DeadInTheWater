#include "BasicVelocityUC.h"

BasicVelocityUC::BasicVelocityUC() {}

void BasicVelocityUC::update(Entity& e, double t)
{
	e.setPositionX(e.getPositionX() + e.getVelocityX() * t);
	e.setPositionY(e.getPositionY() + e.getVelocityY() * t);
}

BasicVelocityUC::~BasicVelocityUC() {}
