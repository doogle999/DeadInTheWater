#include "RenderIsland.h"

RenderIsland::RenderIsland() {}

RenderIsland::~RenderIsland() {}

void RenderIsland::render()
{
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		Camera2D* cameraPtr = dynamic_cast<Camera2D*>(w->fields[Fields::Ids::Id_Camera2D]);

		sf::IntRect r(0, 0, 32, 16);
		sf::Sprite s(Textures::get(Textures::Ids::Boat), r);

		s.setOrigin(16, 8);
		s.setScale(1 / cameraPtr->getViewportS(), 1 / cameraPtr->getViewportS());
		s.setPosition((cameraPtr->gamePosToScreenPos(w->entities[ei[i]].AXS(Translation).position)).convert<float>().toVector2());

		Game::window->draw(s);
	}
}

std::vector<Attribute::Ids> RenderIsland::getNecessaryProperties()
{
	return RenderIsland::necessaryProperties;
}

const std::vector<Attribute::Ids> RenderIsland::necessaryProperties = { Attribute::Ids::Translation, Attribute::Ids::HitPolygon };