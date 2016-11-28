#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <chrono>

#include "World.h"

class World;

class Game
{
	public:
		typedef std::chrono::duration<double, std::ratio<1, 1000>> ms;

		static void init(int windowHeight, int windowWidth, ms msPerUpdate, World w);

		static void loop();

		static void exit();

		static sf::RenderWindow* window;

	private:
		static World world;

		static int windowWidth;
		static int windowHeight;

		static ms tickRate;
};