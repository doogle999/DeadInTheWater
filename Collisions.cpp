#include "Collisions.h"

Collisions::Collisions() {}

Collisions::~Collisions() {}

void Collisions::initialize() {}

	Collisions::StopOnCollision::StopOnCollision(Collisions& o) : owner(o) {}

	Collisions::StopOnCollision::~StopOnCollision() {}

	void Collisions::StopOnCollision::run(Entity& e)
	{
		if(owner.collision(e))
		{
			e.AXS(xVelocity) = 0;
			e.AXS(yVelocity) = 0;
		}
	};

	std::vector<P::Ids> Collisions::StopOnCollision::getNecessaryProperties()
	{
		return Collisions::necessaryProperties;
	};

std::vector<P::Ids> Collisions::getNecessaryProperties()
{
	return Collisions::necessaryProperties;
};

bool Collisions::collision(Entity& e)
{
	for(unsigned int i = 0; i < entities.size(); i++)
	{
		if(&e != entities[i])
		{
			if(sqrt(pow(entities[i]->AXS(xPosition) - e.AXS(xPosition), 2) + pow(entities[i]->AXS(yPosition) - e.AXS(yPosition), 2)) < entities[i]->AXS(radius) + e.AXS(radius))
			{
				return true;
			}
		}
	}
	return false;
}

const std::vector<P::Ids> Collisions::necessaryProperties = { P::Ids::xPosition,  P::Ids::yPosition,  P::Ids::radius, P::Ids::xVelocity,  P::Ids::yVelocity };