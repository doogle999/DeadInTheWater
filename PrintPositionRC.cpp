#include "PrintPositionRC.h"

PrintPositionRC::PrintPositionRC() {}

void PrintPositionRC::render(Entity& e)
{
	std::cout << "X: " << e.getPosition().getX() << ", Y: " << e.getPosition().getY();
}

PrintPositionRC::~PrintPositionRC() {}
