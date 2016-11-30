#include <iostream>
#include <chrono>

#include "World.h"
#include "EntityFactory.h"
#include "Game.h"

int main()
{
	World::registerFields();
	World::registerBehaviors();

	EntityFactory ef;

	World world = ef.createWorld("EntitiesData.xml");

	Game::init(500, 500, (Game::ms)10, world);

	Game::loop();

	Game::exit();

	return 0;
}