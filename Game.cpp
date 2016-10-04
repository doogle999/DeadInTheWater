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
	
	ConstantVelocityUC* uvuc = new ConstantVelocityUC();
	updateComponents.push_back(uvuc);

	PrintPositionRC* pprc = new PrintPositionRC();
	renderComponents.push_back(pprc);

	entities.push_back(this->attachEntityComponents(std::vector<int> {0}, std::vector<int> {0}));
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
			for(unsigned int i = 0; i < entities.size(); i++)
			{
				entities[i].updateAll(tickRate.count());
				entities[i].renderAll();
			}
			lag -= tickRate;
		}

		window.clear();

		window.display();
	}
}

void Game::exit()
{
	for(unsigned int i = 0; i < updateComponents.size(); i++)
	{
		delete updateComponents[i];
		updateComponents[i] = NULL;
	}
	
	for(unsigned int i = 0; i < renderComponents.size(); i++)
	{
		delete renderComponents[i];
		renderComponents[i] = NULL;
	}

	window.close();
}

Game::~Game()
{

}

Entity Game::attachEntityComponents(std::vector<int> u, std::vector<int> r)
{
	std::vector<UpdateComponent*> updaters;
	for(unsigned int i = 0; i < u.size(); i++)
	{
		updaters.push_back(updateComponents[u[i]]);
	}

	std::vector<RenderComponent*> renderers;
	for(unsigned int i = 0; i < r.size(); i++)
	{
		renderers.push_back(renderComponents[r[i]]);
	}

	Entity e(updaters, renderers);

	return e;
}
