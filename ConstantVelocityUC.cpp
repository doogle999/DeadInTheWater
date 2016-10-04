#include "ConstantVelocityUC.h"

ConstantVelocityUC::ConstantVelocityUC() {}

void ConstantVelocityUC::update(Entity& e, double t)
{
	e.setPosition(e.getPosition() + e.getVelocity());
}

ConstantVelocityUC::~ConstantVelocityUC() {}
