#include "PrintPositionRC.h"

PrintPositionRC::PrintPositionRC() {}

void PrintPositionRC::render(Entity& e, sf::RenderWindow* w)
{
	std::cout << "X: " << e.getPositionX() << ", Y: " << e.getPositionY() << std::endl;
}

PrintPositionRC::~PrintPositionRC() {}
