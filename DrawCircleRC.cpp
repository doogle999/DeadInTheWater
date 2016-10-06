#include "DrawCircleRC.h"

DrawCircleRC::DrawCircleRC()
{

}

void DrawCircleRC::render(Entity& e, sf::RenderWindow* w)
{
	sf::CircleShape shape(50);

	shape.setOrigin(50, 50);
	shape.setPosition(e.getPosition().getX(), e.getPosition().getY());
	shape.setFillColor(sf::Color(100, 250, 50));

	w->draw(shape);
}

DrawCircleRC::~DrawCircleRC()
{

}
