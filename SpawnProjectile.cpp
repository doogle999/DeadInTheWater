#include "SpawnProjectile.h"

SpawnProjectile::SpawnProjectile() {}

SpawnProjectile::~SpawnProjectile() {}

void SpawnProjectile::input()
{
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		if(w->entities[ei[i]].AXS(reloadTime) <= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Entity e({ P::Ids::xPosition, P::Ids::yPosition, P::Ids::xVelocity, P::Ids::yVelocity, P::Ids::timeoutTime });

			e.AXS(xPosition) = w->entities[ei[i]].AXS(xPosition);
			e.AXS(yPosition) = w->entities[ei[i]].AXS(yPosition);
			e.AXS(xVelocity) = 10;
			e.AXS(yVelocity) = 10;
			e.AXS(timeoutTime) = 1;

			e.fields.push_back(Fields::Ids::Id_RenderProjectile);
			e.fields.push_back(Fields::Ids::Id_Timeout);

			w->entities[ei[i]].scheduledToSpawn.push_back(e);

			w->entities[ei[i]].AXS(reloadTime) = cooldown;
		}
	}
}

void SpawnProjectile::update()
{
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		if(w->entities[ei[i]].AXS(reloadTime) > 0)
		{
			w->entities[ei[i]].AXS(reloadTime) -= Game::getTick();
		}
	}
}

std::vector<P::Ids> SpawnProjectile::getNecessaryProperties()
{
	return SpawnProjectile::necessaryProperties;
};

const std::vector<P::Ids> SpawnProjectile::necessaryProperties = { P::Ids::reloadTime, P::Ids::xPosition, P::Ids::yPosition };

const double SpawnProjectile::cooldown = 2;