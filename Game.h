#pragma once

#include <fstream>
#include <iostream>
#include <chrono>
#include <ratio>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "UpdateComponent.h"
#include "ConstantVelocityUC.h"
#include "RenderComponent.h"
#include "PrintPositionRC.h"

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
		Entity attachEntityComponents(std::vector<int> u, std::vector<int> r);

		int windowWidth;
		int windowHeight;

		ms tickRate;

		sf::RenderWindow window;

		std::vector<UpdateComponent*> updateComponents;

		std::vector<RenderComponent*> renderComponents;

		std::vector<Entity> entities;
};