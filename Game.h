#pragma once

//#include <fstream>
//#include <string>
//#include <sstream>
#include <iostream>
#include <chrono>
#include <ratio>
#include <vector>


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Behavior.h"

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
		//void load(std::string path);

		int windowWidth;
		int windowHeight;

		ms tickRate;

		sf::RenderWindow window;

		std::vector<Behavior> inputBehaviors;
		std::vector<Behavior> updateBehaviors;
		std::vector<Behavior> renderBehaviors;

		std::vector<Entity> entities;
};