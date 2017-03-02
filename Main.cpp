#include <iostream>
#include <chrono>

#include "World.h"
#include "EntityFactory.h"
#include "Game.h"

#include "Polygon.h"

int main()
{
	Polygon<double> poly;

	poly.points.resize(5);

	poly.points[0].c = { -1, 1 };
	poly.points[1].c = { 0, 0 };
	poly.points[2].c = { 1, 1 };
	poly.points[3].c = { 1, -1 };
	poly.points[4].c = { -1, -1 };

	PVector<double, 2> p({-1, -1});

	std::cout << poly.pointInside(p);

	World world = EntityFactory::createWorld("EntitiesData.xml");
	
	Game::init(1000, 500, (Game::ms)20, world, 1);

	Game::loop();

	Game::exit();

	return 0;
}