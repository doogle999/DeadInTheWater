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
/*
	IslandMaker im;

	sf::RenderWindow window(sf::VideoMode(960, 960), "Game");
	
	sf::RectangleShape rect;
	rect.setPosition(0, 0);
	rect.setSize(sf::Vector2f(960, 960));
	rect.setFillColor(sf::Color(0, 102, 204));
	window.draw(rect);

	std::array<std::vector<Polygon<double>>, 4> polys = im.generateIslandsWithHeights(4, -0.5, 0, 0.2, 0.6);

	sf::VertexArray renderStuff(sf::Triangles);

	for(unsigned int j = 0; j < polys.size(); j++)
	{
		for(unsigned int k = 0; k < polys[j].size(); k++)
		{
			polys[j][k].smooth();
			std::vector<Polygon<double>> triangles = polys[j][k].triangulate();
			sf::VertexArray renderTriangles(sf::Triangles, 3 * triangles.size());

			for(unsigned int i = 0; i < triangles.size(); i++)
			{
				renderTriangles[3 * i].position = (triangles[i].points[0] * 30).convert<float>().toVector2();
				renderTriangles[3 * i + 1].position = (triangles[i].points[1] * 30).convert<float>().toVector2();
				renderTriangles[3 * i + 2].position = (triangles[i].points[2] * 30).convert<float>().toVector2();

				switch(j)
				{
					case 0:
					{
						renderTriangles[3 * i].color = sf::Color(102, 204, 255);
						renderTriangles[3 * i + 1].color = sf::Color(102, 204, 255);
						renderTriangles[3 * i + 2].color = sf::Color(102, 204, 255);
						break;
					}
					case 1:
					{
						renderTriangles[3 * i].color = sf::Color(255, 255, 153);
						renderTriangles[3 * i + 1].color = sf::Color(255, 255, 153);
						renderTriangles[3 * i + 2].color = sf::Color(255, 255, 153);
						break;
					}
					case 2:
					{
						renderTriangles[3 * i].color = sf::Color(102, 255, 102);
						renderTriangles[3 * i + 1].color = sf::Color(102, 255, 102);
						renderTriangles[3 * i + 2].color = sf::Color(102, 255, 102);
						break;
					}
					case 3:
					{
						renderTriangles[3 * i].color = sf::Color(0, 153, 51);
						renderTriangles[3 * i + 1].color = sf::Color(0, 153, 51);
						renderTriangles[3 * i + 2].color = sf::Color(0, 153, 51);
						break;
					}
				}
				renderStuff.append(renderTriangles[3 * i]);
				renderStuff.append(renderTriangles[3 * i + 1]);
				renderStuff.append(renderTriangles[3 * i + 2]);
			}
			window.draw(renderTriangles);
			renderTriangles.clear();
		}
	}
	std::cout << sizeof(renderStuff) + sizeof(sf::Vertex) * renderStuff.getVertexCount();*/
	Game::loop();

	Game::exit();

	return 0;
}