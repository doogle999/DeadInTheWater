#include "Gravity.h"

Gravity::Gravity() {}

Gravity::~Gravity() {}

void Gravity::update()
{
	for(unsigned int i = 0; i < entities.size(); i++)
	{
		for(unsigned int j = 0; j < entities.size(); j++)
		{
			double distance = pow(entities[i]->AXS(xPosition) - entities[j]->AXS(xPosition), 2) + pow(entities[i]->AXS(yPosition) - entities[j]->AXS(yPosition), 2);
			if(distance > 0)
			{
				distance = pow(distance, 0.5);

				double scaleMass = 1;
				if(entities[j]->AXS(radius) > distance)
				{
					scaleMass = pow(distance / entities[j]->AXS(radius), 3);
				}

				entities[i]->AXS(xAcceleration) += (Gravity::GRAV_CONSTANT * scaleMass * entities[j]->AXS(mass) * -(entities[i]->AXS(xPosition) - entities[j]->AXS(xPosition)) / (distance * distance * distance));
				entities[i]->AXS(yAcceleration) += (Gravity::GRAV_CONSTANT * scaleMass * entities[j]->AXS(mass) * -(entities[i]->AXS(yPosition) - entities[j]->AXS(yPosition)) / (distance * distance * distance));
			}
		}
	}
}

std::vector<P::Ids> Gravity::getNecessaryProperties()
{
	return Gravity::necessaryProperties;
}

const std::vector<P::Ids> Gravity::necessaryProperties = { P::Ids::xPosition,  P::Ids::yPosition,  P::Ids::radius, P::Ids::xVelocity,  P::Ids::yVelocity, P::Ids::xAcceleration, P::Ids::yAcceleration, P::Ids::mass };

const double Gravity::GRAV_CONSTANT = 6.67e-11;