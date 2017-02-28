#include "RenderProjectile.h"

RenderProjectile::RenderProjectile() {}

RenderProjectile::~RenderProjectile() {}

void RenderProjectile::render()
{
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		Camera2D* cameraPtr = dynamic_cast<Camera2D*>(w->fields[Fields::Ids::Id_Camera2D]);

		sf::IntRect r(0, 0, 32, 16);
		sf::Sprite s(Textures::get(Textures::Ids::Projectile), r);

		s.setOrigin(16, 8);

		s.setScale(1 / cameraPtr->viewportS, 1 / cameraPtr->viewportS);

		s.setPosition((w->entities[ei[i]].AXS(position).c[0] - cameraPtr->viewportX) / cameraPtr->viewportS, (w->entities[ei[i]].AXS(position).c[1] - cameraPtr->viewportY) / cameraPtr->viewportS);

		Game::window->draw(s);
	}
}

std::vector<P::Ids> RenderProjectile::getNecessaryProperties()
{
	return RenderProjectile::necessaryProperties;
};

const std::vector<P::Ids> RenderProjectile::necessaryProperties = { P::Ids::position };