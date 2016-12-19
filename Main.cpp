#include <iostream>
#include <chrono>

#include <SFML\Window.hpp>

#include "World.h"
#include "EntityFactory.h"
#include "Game.h"

int main()
{
	typedef std::chrono::duration<double, std::ratio<1, 1000>> ms;

	ms tickRate(20);

	std::chrono::steady_clock::time_point previous = std::chrono::steady_clock::now();
	ms lag(0);

	sf::Joystick::update();

	while(sf::Joystick::isConnected(0))
	{
		std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
		ms elapsed = std::chrono::duration_cast<ms>(current - previous);
		previous = current;
		lag += elapsed;

		while(lag >= tickRate)
		{
			sf::Vector2i newMousePosition(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));
			sf::Mouse::setPosition(sf::Mouse::getPosition() + newMousePosition);

			lag -= tickRate;
		}
		std::cout << sf::Joystick::isConnected(0);

		sf::Joystick::update();
	}

	/*
	World::registerFields();
	World::registerBehaviors();

	World world = EntityFactory::createWorld("EntitiesData.xml");

	Game::init(500, 500, (Game::ms)10, world);

	Game::loop();

	Game::exit();
	*/
	return 0;
}