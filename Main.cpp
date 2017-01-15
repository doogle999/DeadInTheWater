#include <iostream>
#include <chrono>

#include "World.h"
#include "EntityFactory.h"
#include "Game.h"

int main()
{
	World world = EntityFactory::createWorld("EntitiesData.xml");
	
	Game::init(1000, 500, (Game::ms)1, world, 100000);

	Game::loop();

	Game::exit();

	return 0;
}