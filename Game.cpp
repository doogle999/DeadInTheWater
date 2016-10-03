#include "Game.h"

Game::Game()
{

}

void Game::init(int wW, int wH, ms tR)
{
	windowWidth = wW;
	windowHeight = wH;
	
	tickRate = tR;

	window.create(sf::VideoMode(windowWidth, windowHeight), "Game");
}

void Game::loop()
{
	std::chrono::steady_clock::time_point previous = std::chrono::steady_clock::now();
	ms lag(0);

	while(window.isOpen())
	{
		std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
		ms elapsed = std::chrono::duration_cast<ms>(current - previous);
		previous = current;
		lag += elapsed;

		sf::Event event;
		while(window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				this->exit();
				break;

			}
		}

		while(lag >= tickRate)
		{
			lag -= tickRate;
		}

		window.clear();

		window.display();
	}
}

void Game::exit()
{
	window.close();
}

Game::~Game()
{

}
