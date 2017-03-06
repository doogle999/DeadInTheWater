#include "Camera2D.h"

Camera2D::Camera2D() : viewportPos({ 0, 0 }), viewportVel({ 0, 0 }) 
{
	viewportS = 1;
}

Camera2D::~Camera2D() {}

void Camera2D::input()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		viewportVel.c[0] = -500;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		viewportVel.c[0] = 500;
	}
	else
	{
		viewportVel.c[0] = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		viewportVel.c[1] = -500;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		viewportVel.c[1] = 500;
	}
	else
	{
		viewportVel.c[1] = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		viewportSMult = 1 + 1 * Game::getPureTick();
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		viewportSMult = 1 / (1 + 1 * Game::getPureTick());
	}
	else
	{
		viewportSMult = 1;
	}
}

void Camera2D::update()
{
	viewportPos = viewportPos + viewportVel * viewportS * Game::getPureTick();
	viewportPos.c[0] += (1 - viewportSMult) * viewportS * (double)Game::getWindowSize().c[0] / 2;
	viewportPos.c[1] += (1 - viewportSMult) * viewportS * (double)Game::getWindowSize().c[1] / 2;

	viewportS *= viewportSMult;
}

PVector<double, 2> Camera2D::screenPosToGamePos(PVector<double, 2> sp)
{
	return sp * viewportS + viewportPos;
}
PVector<double, 2> Camera2D::gamePosToScreenPos(PVector<double, 2> sp)
{
	return (sp - viewportPos) * (1 / viewportS);
}

PVector<double, 2> Camera2D::getViewportPos()
{
	return viewportPos;
}
PVector<double, 2> Camera2D::getViewportVel()
{
	return viewportVel;
}

double Camera2D::getViewportS()
{
	return viewportS;
}
double Camera2D::getViewportSMult()
{
	return viewportSMult;
}

std::vector<Attribute::Ids> Camera2D::getNecessaryProperties()
{
	return {};
};