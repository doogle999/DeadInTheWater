#include "Game.h"

void Game::init(int wW, int wH, ms tR, World w, double sF)
{
	windowWidth = wW;
	windowHeight = wH;

	tickRate = tR;

	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Game");

	world = w;

	speedFactor = sF;

	Textures::load();
}

void Game::loop()
{
	bool exiting = false;

	std::chrono::steady_clock::time_point updatePrevious = std::chrono::steady_clock::now();
	ms updateLag(0);

	while(window->isOpen())
	{
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

		std::chrono::steady_clock::time_point updateCurrent = std::chrono::steady_clock::now();
		ms updateElapsed = std::chrono::duration_cast<ms>(updateCurrent - updatePrevious);
		updatePrevious = updateCurrent;
		updateLag += updateElapsed;

		// Updating
		while(updateLag >= tickRate)
		{
			Game::world.update();

			updateLag -= tickRate;
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

	Textures::unload();
}

double Game::getTick()
{
	return tickRate.count() / 1000 * speedFactor;
}
double Game::getPureTick()
{
	return tickRate.count() / 1000;
}

sf::RenderWindow* Game::window;

World Game::world;

int Game::windowWidth;
int Game::windowHeight;

Game::ms Game::tickRate;

double Game::speedFactor;