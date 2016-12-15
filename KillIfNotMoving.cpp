#include "KillIfNotMoving.h"

KillIfNotMoving::KillIfNotMoving() {}

KillIfNotMoving::~KillIfNotMoving() {}

void KillIfNotMoving::run(Entity& e)
{
	if(e.AXS(xVelocity) == 0 && e.AXS(yVelocity) == 0)
	{
		e.scheduledForDeletion = true;
	}
};

std::vector<P::Ids> KillIfNotMoving::getNecessaryProperties()
{
	return necessaryProperties;
};

const std::vector<P::Ids> KillIfNotMoving::necessaryProperties = { P::Ids::xVelocity, P::Ids::yVelocity };