#include "ArrowVelocityIC.h"

ArrowVelocityIC::ArrowVelocityIC() {}

void ArrowVelocityIC::input(Entity& e, sf::Window* w)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		e.setVelocityX(-1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		e.setVelocityX(1);
	else
		e.setVelocityX(0);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		e.setVelocityY(-1);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		e.setVelocityY(1);
	else
		e.setVelocityY(0);
}

ArrowVelocityIC::~ArrowVelocityIC() {}
 