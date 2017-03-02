#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <chrono>
#include <random>

#include "World.h"
#include "Textures.h"
#include "PVector.h"

class World;

class Game
{
	public:
		typedef std::chrono::duration<double, std::ratio<1, 1000>> ms;

		static void init(int wH, int wW, ms tR, World w, double sF);

		static void loop();

		static void exit();

		static double getTick();
		static double getPureTick();

		static PVector<unsigned int, 2> getWindowSize();

		static sf::RenderWindow* window;

		static ms tickRate;

		static std::mt19937 rng;

	private:
		static World world;

		static int windowWidth;
		static int windowHeight;

		static double speedFactor;
};