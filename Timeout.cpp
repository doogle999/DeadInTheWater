#include "Timeout.h"

Timeout::Timeout() {}

Timeout::~Timeout() {}

void Timeout::update()
{
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		if(w->entities[ei[i]].AXS(TimeoutTime).currentTimeoutTime > 0)
		{
			w->entities[ei[i]].AXS(TimeoutTime).currentTimeoutTime -= Game::getTick();
		}
		else
		{
			w->scheduleToDespawn(ei[i]);
		}
	}
}

std::vector<Attribute::Ids> Timeout::getNecessaryProperties()
{
	return Timeout::necessaryProperties;
};

const std::vector<Attribute::Ids> Timeout::necessaryProperties = { Attribute::Ids::TimeoutTime };