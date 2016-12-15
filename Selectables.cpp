#include "Selectables.h"

Selectables::Selectables() {}

Selectables::~Selectables() {}

	Selectables::SelectOnClick::SelectOnClick(Selectables& o) : owner(o) {}

	Selectables::SelectOnClick::~SelectOnClick() {}

	void Selectables::SelectOnClick::run(Entity& e)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if(sqrt(pow(sf::Mouse::getPosition(*Game::window).x - e.AXS(xPosition), 2) + pow(sf::Mouse::getPosition(*Game::window).y - e.AXS(yPosition), 2)) < e.AXS(radius))
			{
				e.AXS(selected) = true;
			}
			else
			{
				e.AXS(selected) = false;
			}
		}
	};

	std::vector<P::Ids> Selectables::SelectOnClick::getNecessaryProperties()
	{
		return Selectables::necessaryProperties;
	};

std::vector<P::Ids> Selectables::getNecessaryProperties()
{
	return Selectables::necessaryProperties;
};

const std::vector<P::Ids> Selectables::necessaryProperties = { P::Ids::xPosition,  P::Ids::yPosition,  P::Ids::radius, P::Ids::selected };