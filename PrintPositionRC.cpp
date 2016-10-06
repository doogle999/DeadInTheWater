#include "PrintPositionRC.h"

PrintPositionRC::PrintPositionRC() {}

void PrintPositionRC::render(Entity& e, sf::RenderWindow* w)
{
	std::cout << "X: " << e.getPosition().getX() << ", Y: " << e.getPosition().getY() << std::endl;
}

PrintPositionRC::~PrintPositionRC() {}
