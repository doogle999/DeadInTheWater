#include "Camera2D.h"

Camera2D::Camera2D() 
{
	viewportX = 0;
	viewportY = 0;
	viewportS = 1;
}

Camera2D::~Camera2D() {}

void Camera2D::input()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		viewportXVelocity = -500;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		viewportXVelocity = 500;
	}
	else
	{
		viewportXVelocity = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		viewportYVelocity = -500;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		viewportYVelocity = 500;
	}
	else
	{
		viewportYVelocity = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		viewportSFactor = 1 + 1 * Game::getPureTick();
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		viewportSFactor = 1 / (1 + 1 * Game::getPureTick());
	}
	else
	{
		viewportSFactor = 1;
	}
}

void Camera2D::update()
{
	viewportX += viewportXVelocity * viewportS * Game::getPureTick();
	viewportX += (1 - viewportSFactor) * viewportS * Game::window->getSize().x / 2;

	viewportY += viewportYVelocity * viewportS * Game::getPureTick();
	viewportY += (1 - viewportSFactor) * viewportS * Game::window->getSize().y / 2;

	viewportS *= viewportSFactor;
}

void Camera2D::render()
{
	for(unsigned int i = 0; i < entities.size(); i++)
	{
		sf::CircleShape c(entities[i]->AXS(renderRadius) / viewportS);

		c.setOrigin(entities[i]->AXS(renderRadius) / viewportS, entities[i]->AXS(renderRadius) / viewportS);

		c.setPosition((entities[i]->AXS(xPosition) - viewportX) / viewportS, (entities[i]->AXS(yPosition) - viewportY) / viewportS);

		c.setFillColor(entities[i]->AXS(color));

		Game::window->draw(c);
	}
}

std::vector<P::Ids> Camera2D::getNecessaryProperties()
{
	return Camera2D::necessaryProperties;
};

const std::vector<P::Ids> Camera2D::necessaryProperties = { P::Ids::color, P::Ids::xPosition, P::Ids::yPosition, P::Ids::renderRadius };