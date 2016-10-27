#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <ratio>
#include <vector>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.h"

#include "InputComponent.h"
#include "ArrowVelocityIC.h"
#include "TowardsMouseIC.h"

#include "UpdateComponent.h"
#include "BasicVelocityUC.h"

#include "RenderComponent.h"
#include "PrintPositionRC.h"
#include "DrawCircleRC.h"

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

		std::vector<InputComponent*> inputComponents;
		std::vector<UpdateComponent*> updateComponents;
		std::vector<RenderComponent*> renderComponents;

		std::vector<Entity> entities;
};