#include <iostream>
#include <chrono>

#include "World.h"
#include "EntityFactory.h"
#include "Game.h"

#include "Polygon.h"
#include "IslandMaker.h"

int main()
{
	IslandMaker im;
	/*
	Polygon<double> poly
	({
		PVector<double, 2>({ 0.0, 0.0 }), PVector<double, 2>({ 10.0, 0.0 }), PVector<double, 2>({ 10.0, 10.0 }), PVector<double, 2>({ 0.0, 10.0 }),
		PVector<double, 2>({ 0.0, 0.0 }), PVector<double, 2>({ 10.0, 0.0 }), PVector<double, 2>({ 10.0, 10.0 }), PVector<double, 2>({ 0.0, 10.0 })
	});
	*/

	Polygon<unsigned int> polyUnsignedInt = im.generateIsland(1, 0)[0];
	Polygon<double> poly;
	poly.points.resize(polyUnsignedInt.points.size());
	for(unsigned int i = 0; i < polyUnsignedInt.points.size(); i++)
	{
		poly.points[i] = polyUnsignedInt.points[i].convert<double>();
	}

	std::vector<Polygon<double>> triangles = poly.triangulate();

	World world = EntityFactory::createWorld("EntitiesData.xml");
	
	Game::init(1000, 500, (Game::ms)20, world, 1);

	Game::loop();

	Game::exit();

	return 0;
}