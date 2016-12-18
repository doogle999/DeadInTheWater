#include "Game.h"

void Game::init(int wW, int wH, ms tR, World w)
{
	windowWidth = wW;
	windowHeight = wH;

	tickRate = tR;

	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Game");

	world = w;
}

void Game::loop()
{
	std::chrono::steady_clock::time_point previous = std::chrono::steady_clock::now();
	ms lag(0);

	bool exiting = false;

	while(window->isOpen())
	{
		std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
		ms elapsed = std::chrono::duration_cast<ms>(current - previous);
		previous = current;
		lag += elapsed;

		// Inputing
		Game::world.input();

		sf::Event event;
		while(window->pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					exiting = true;
					break;
				default:
					break;
			}
		}

		// Updating
		while(lag >= tickRate)
		{
			// Components to get updated in the order of the entities
			Game::world.update();

			// Components to get updated after all entities have been updated

			lag -= tickRate;
		}

		// Rendering
		window->clear();

		Game::world.render();

		window->display();

		if(exiting)
		{
			break;
		}
	}
}

void Game::exit()
{
	window->close();

	delete window;
}

sf::RenderWindow* Game::window;

World Game::world;

int Game::windowWidth;
int Game::windowHeight;

Game::ms Game::tickRate;