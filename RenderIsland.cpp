#include "RenderIsland.h"

RenderIsland::RenderIsland() {}

RenderIsland::~RenderIsland() {}

void RenderIsland::render()
{
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		Camera2D* cameraPtr = dynamic_cast<Camera2D*>(w->fields[Fields::Ids::Id_Camera2D]);

		sf::Transform trans;
		trans.translate((cameraPtr->gamePosToScreenPos(w->entities[ei[i]].AXS(Translation).position)).convert<float>().toVector2());
		trans.scale(1 / cameraPtr->getViewportS(), 1 / cameraPtr->getViewportS());

		Game::window->draw(w->entities[ei[i]].AXS(IslandTriangles).triangles, trans);
	}
}

std::vector<Attribute::Ids> RenderIsland::getNecessaryProperties()
{
	return RenderIsland::necessaryProperties;
}

const std::vector<Attribute::Ids> RenderIsland::necessaryProperties = { Attribute::Ids::Translation, Attribute::Ids::IslandTriangles };