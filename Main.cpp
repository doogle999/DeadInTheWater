#include <iostream>
#include <chrono>
#include <vector>

#include "World.h"
#include "EntityFactory.h"
#include "Game.h"

#include "IslandMaker.h"

int main()
{
	World world = EntityFactory::createWorld("EntitiesData.xml");
	
	Game::init(1000, 500, (Game::ms)40, world, 1);

	IslandMaker im;

	std::vector<std::vector<bool>> map = im.generateIslandBoolMap(6, 0.0);

	for(unsigned int i = 0; i < 16 * 6; i++)
	{
		for(unsigned int j = 0; j < 16 * 6; j++)
		{
			if(map[i][j])
			{
				std::cout << "#";
			}
			else
			{
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}

	std::cin.get();

	Game::loop();

	Game::exit();

	return 0;
}