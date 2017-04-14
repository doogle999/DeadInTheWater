#include <iostream>
#include <chrono>

#include "SFML\Graphics.hpp"

#include "World.h"
#include "EntityFactory.h"
#include "Game.h"

#include "Polygon.h"
#include "IslandMaker.h"

int main()
{
	World world = EntityFactory::createWorld("EntitiesData.xml");
	
	Game::init(1000, 500, (Game::ms)20, world, 1);

	IslandMaker im;

	Polygon<unsigned int> polyUnsignedInt = im.generateIsland(3, 0)[0];
	Polygon<double> poly;
	poly.points.resize(polyUnsignedInt.points.size());

	sf::RenderWindow window(sf::VideoMode(750, 750), "Game");
	for(unsigned int i = 0; i < polyUnsignedInt.points.size(); i++)
	{
		poly.points[i] = polyUnsignedInt.points[i].convert<double>();
	}

	for(unsigned int i = 0; i < poly.points.size(); i++)
	{
		sf::Vertex line[] =
		{
			sf::Vertex((poly.points[i] * 10).convert<float>().toVector2()),
			sf::Vertex((poly.points[(i + 1) % poly.points.size()] * 10).convert<float>().toVector2())
		};

		window.draw(line, 2, sf::Lines);
	}

	window.display();

	std::vector<Polygon<double>> triangles = poly.triangulate();

	window.clear();

	for(unsigned int i = 0; i < triangles.size(); i++)
	{
		sf::ConvexShape triangle;
		triangle.setPointCount(3);

		triangle.setPoint(0, (triangles[i].points[0] * 10).convert<float>().toVector2());
		triangle.setPoint(1, (triangles[i].points[1] * 10).convert<float>().toVector2());
		triangle.setPoint(2, (triangles[i].points[2] * 10).convert<float>().toVector2());

		//triangle.setOutlineThickness(1);
		//triangle.setOutlineColor(sf::Color(255, 0, 0));

		window.draw(triangle);
	}

	window.display();

	Game::loop();

	Game::exit();

	return 0;
}