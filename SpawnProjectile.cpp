#include "SpawnProjectile.h"

SpawnProjectile::SpawnProjectile() {}

SpawnProjectile::~SpawnProjectile() {}

void SpawnProjectile::input()
{
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		if(w->entities[ei[i]].AXS(ReloadTime).currentReloadTime <= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Entity e({ Attribute::Ids::Translation, Attribute::Ids::TimeoutTime });
			e.AXS(Translation) = w->entities[ei[i]].AXS(Translation);
			e.AXS(Translation).acceleration = e.AXS(Translation).acceleration * 0;
			e.AXS(TimeoutTime).currentTimeoutTime = 1;

			std::vector<Fields::Ids> f;
			f.push_back(Fields::Ids::Id_RenderProjectile);
			f.push_back(Fields::Ids::Id_Timeout);

			w->scheduleToSpawn(e, f);
		
			w->entities[ei[i]].AXS(ReloadTime).currentReloadTime = w->entities[ei[i]].AXS(ReloadTime).reloadTime;
		}
	}
}

void SpawnProjectile::update()
{
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		if(w->entities[ei[i]].AXS(ReloadTime).currentReloadTime > 0)
		{
			w->entities[ei[i]].AXS(ReloadTime).currentReloadTime -= Game::getTick();
		}
	}
}

std::vector<Attribute::Ids> SpawnProjectile::getNecessaryProperties()
{
	return SpawnProjectile::necessaryProperties;
};

const std::vector<Attribute::Ids> SpawnProjectile::necessaryProperties = { Attribute::Ids::ReloadTime, Attribute::Ids::Translation };