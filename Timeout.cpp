#include "Timeout.h"

Timeout::Timeout() {}

Timeout::~Timeout() {}

void Timeout::update()
{
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		if(w->entities[ei[i]].AXS(timeoutTime) > 0)
		{
			w->entities[ei[i]].AXS(timeoutTime) -= Game::getTick();
		}
		else
		{
			w->scheduleToDespawn(ei[i]);
		}
	}
}

std::vector<P::Ids> Timeout::getNecessaryProperties()
{
	return Timeout::necessaryProperties;
};

const std::vector<P::Ids> Timeout::necessaryProperties = { P::Ids::timeoutTime };