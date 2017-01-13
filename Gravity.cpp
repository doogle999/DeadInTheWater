#include "Gravity.h"

Gravity::Gravity() {}

Gravity::~Gravity() {}

void Gravity::update()
{
	/*
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		for(unsigned int j = 0; j < ei.size(); j++)
		{
			double distance = pow(ei[i]->AXS(xPosition) - ei[j]->AXS(xPosition), 2) + pow(ei[i]->AXS(yPosition) - ei[j]->AXS(yPosition), 2);
			if(distance > 0)
			{
				distance = pow(distance, 0.5);

				double scaleMass = 1;
				if(ei[j]->AXS(radius) > distance)
				{
					scaleMass = pow(distance / ei[j]->AXS(radius), 3);
				}

				ei[i]->AXS(xAcceleration) += (Gravity::GRAV_CONSTANT * scaleMass * ei[j]->AXS(mass) * -(ei[i]->AXS(xPosition) - ei[j]->AXS(xPosition)) / (distance * distance * distance));
				ei[i]->AXS(yAcceleration) += (Gravity::GRAV_CONSTANT * scaleMass * ei[j]->AXS(mass) * -(ei[i]->AXS(yPosition) - ei[j]->AXS(yPosition)) / (distance * distance * distance));
			}
		}
	}
	*/
}

std::vector<P::Ids> Gravity::getNecessaryProperties()
{
	return Gravity::necessaryProperties;
}

const std::vector<P::Ids> Gravity::necessaryProperties = { P::Ids::xPosition,  P::Ids::yPosition,  P::Ids::radius, P::Ids::xVelocity,  P::Ids::yVelocity, P::Ids::xAcceleration, P::Ids::yAcceleration, P::Ids::mass };

const double Gravity::GRAV_CONSTANT = 6.67e-11;