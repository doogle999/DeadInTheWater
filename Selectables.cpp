#include "Selectables.h"

Selectables::Selectables() {}

Selectables::~Selectables() {}

void Selectables::input()
{
	/*
	firstSelected = false;

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		for(unsigned int i = 0; i < ei.size(); i++)
		{
			if(!firstSelected && sqrt(pow(sf::Mouse::getPosition(*Game::window).x - ei[i]->AXS(xPosition), 2) + pow(sf::Mouse::getPosition(*Game::window).y - ei[i]->AXS(yPosition), 2)) < ei[i]->AXS(radius))
			{
				ei[i]->AXS(selected) = true;
				firstSelected = true;
			}
			else
			{
				ei[i]->AXS(selected) = false;
			}
		}
	}
	*/
}

std::vector<P::Ids> Selectables::getNecessaryProperties()
{
	return Selectables::necessaryProperties;
};

const std::vector<P::Ids> Selectables::necessaryProperties = { P::Ids::xPosition,  P::Ids::yPosition,  P::Ids::radius, P::Ids::selected };