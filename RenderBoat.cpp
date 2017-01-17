#include "RenderBoat.h"

RenderBoat::RenderBoat() {}

RenderBoat::~RenderBoat() {}

void RenderBoat::render()
{
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		Camera2D* cameraPtr = dynamic_cast<Camera2D*>(w->fields[Fields::Ids::Id_Camera2D]);

		sf::IntRect r(0, 0, 32, 16);
		sf::Sprite s(Textures::get(Textures::Ids::Boat), r);

		s.setOrigin(16, 8);

		s.setScale(1 / cameraPtr->viewportS, 1 / cameraPtr->viewportS);

		s.setPosition((w->entities[ei[i]].AXS(xPosition) - cameraPtr->viewportX) / cameraPtr->viewportS, (w->entities[ei[i]].AXS(yPosition) - cameraPtr->viewportY) / cameraPtr->viewportS);	

		Game::window->draw(s);
	}
}

std::vector<P::Ids> RenderBoat::getNecessaryProperties()
{
	return RenderBoat::necessaryProperties;
};

const std::vector<P::Ids> RenderBoat::necessaryProperties = { P::Ids::xPosition, P::Ids::yPosition };