#include "Camera2D.h"

Camera2D::Camera2D() : viewportPos({ 0, 0 }), viewportVel({ 0, 0 }) 
{
	viewportS = 1;
}

Camera2D::~Camera2D() {}

void Camera2D::update()
{
	viewportPos = viewportPos + viewportVel * viewportS * Game::getPureTick();
	viewportPos.c[0] += (1 - viewportSMult) * viewportS * (double)Game::getWindowSize().c[0] / 2;
	viewportPos.c[1] += (1 - viewportSMult) * viewportS * (double)Game::getWindowSize().c[1] / 2;

	viewportS *= viewportSMult;
}

void Camera2D::cameraControls(std::array<SFMLInputHandler::Func, 6> f) // move left, right, up, down, zoom in, zoom out
{
	SFMLInputHandler* inputPointer = dynamic_cast<SFMLInputHandler*>(w->fields[Fields::Ids::Id_SFMLInputHandler]);

	viewportVel.c[0] = 500 * (inputPointer->checkFunc(f[1]) - inputPointer->checkFunc(f[0]));
	viewportVel.c[1] = 500 * (inputPointer->checkFunc(f[3]) - inputPointer->checkFunc(f[2]));

	viewportSMult = (1 + Game::getPureTick() * inputPointer->checkFunc(f[5])) / (1 + Game::getPureTick() * inputPointer->checkFunc(f[4]));
}

PVector<double, 2> Camera2D::screenPosToGamePos(PVector<double, 2> sp)
{
	return sp * viewportS + viewportPos;
}
PVector<double, 2> Camera2D::gamePosToScreenPos(PVector<double, 2> sp)
{
	return (sp - viewportPos) * (1 / viewportS);
}

void Camera2D::setViewportPos(PVector<double, 2> p)
{
	viewportPos = p;
}
void Camera2D::setViewportVel(PVector<double, 2> v)
{
	viewportVel = v;
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