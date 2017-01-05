#include "Camera2D.h"

Camera2D::RenderCircle::RenderCircle(Camera2D& o) : owner(o) {}

Camera2D::RenderCircle::~RenderCircle() {}

void Camera2D::RenderCircle::run(Entity& e)
{
	sf::CircleShape c(e.AXS(renderRadius) / owner.viewportS);

	c.setOrigin(e.AXS(renderRadius) / owner.viewportS, e.AXS(renderRadius) / owner.viewportS);

	c.setPosition((e.AXS(xPosition) - owner.viewportX) / owner.viewportS, (e.AXS(yPosition) - owner.viewportY) / owner.viewportS);

	c.setFillColor(e.AXS(color));

	Game::window->draw(c);
};

std::vector<P::Ids> Camera2D::RenderCircle::getNecessaryProperties()
{
	return Camera2D::RenderCircle::necessaryProperties;
};

const std::vector<P::Ids>  Camera2D::RenderCircle::necessaryProperties = { P::Ids::xPosition, P::Ids::yPosition, P::Ids::renderRadius, P::Ids::color };