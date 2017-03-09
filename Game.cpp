#include "Game.h"

void Game::init(int wW, int wH, ms tR, World w, double sF)
{
	windowWidth = wW;
	windowHeight = wH;

	tickRate = tR;

	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Game");

	world = w;

	speedFactor = sF;

	rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());

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
		exiting = Game::world.input();

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

PVector<unsigned int, 2> Game::getWindowSize()
{
	return PVector<unsigned int, 2>(window->getSize());
}

sf::RenderWindow* Game::window;

World Game::world;

int Game::windowWidth;
int Game::windowHeight;

Game::ms Game::tickRate;

std::mt19937 Game::rng;

double Game::speedFactor;