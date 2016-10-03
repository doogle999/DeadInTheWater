#pragma once

#include <chrono>
#include <ratio>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game
{
	public:
		typedef std::chrono::duration<double, std::ratio<1, 1000>> ms;

		Game();

		void init(int windowHeight, int windowWidth, ms msPerUpdate);

		void loop();

		void exit();

		~Game();
	
	private:
		int windowWidth;
		int windowHeight;

		ms tickRate;

		sf::RenderWindow window;
};

