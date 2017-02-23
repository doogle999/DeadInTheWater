#include <iostream>
#include <chrono>
#include <vector>

#include "World.h"
#include "EntityFactory.h"
#include "Game.h"

#include "IslandMaker.h"
#include "Polygon.h"
#include "Point.h"

int main()
{
	World world = EntityFactory::createWorld("EntitiesData.xml");
	
	Game::init(1000, 500, (Game::ms)40, world, 1);

	IslandMaker im;

	std::vector<Polygon> polys = im.generateIsland(4, 0.2);

	for(unsigned int k = 0; k < polys.size(); k++)
	{
		for(unsigned int i = 0; i < 16 * 6 + 1; i++)
		{
			for(unsigned int j = 0; j < 16 * 6 + 1; j++)
			{
			
			}
			std::cout << std::endl;
		}
	}

	std::cin.get();

	Game::loop();

	Game::exit();

	return 0;
}