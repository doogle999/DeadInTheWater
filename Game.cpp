#include "Game.h"

Game::Game() {}

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

		// Inputing
		for(unsigned int i = 0; i < entities.size(); i++)
		{
			entities[i].input();
		}

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

		// Updating
		while(lag >= tickRate)
		{
			for(unsigned int i = 0; i < entities.size(); i++)
			{
				entities[i].update();
			}

			lag -= tickRate;
		}

		// Rendering
		window.clear();
		for(unsigned int i = 0; i < entities.size(); i++)
		{
			entities[i].render();
		}
		window.display();
	}
}

void Game::exit()
{
	/*
	// Delete all the input components still on the heap
	for(unsigned int i = 0; i < inputBehaviors.size(); i++)
	{
		delete inputBehaviors[i];
		inputBehaviors[i] = NULL;
	}
	inputBehaviors.clear();

	// Delete all the update components still on the heap
	for(unsigned int i = 0; i < updateBehaviors.size(); i++)
	{
		delete updateBehaviors[i];
		updateBehaviors[i] = NULL;
	}
	updateBehaviors.clear();

	// Delete all the render components still on the heap
	for(unsigned int i = 0; i < renderBehaviors.size(); i++)
	{
		delete renderBehaviors[i];
		renderBehaviors[i] = NULL;
	}
	renderBehaviors.clear();
	*/

	window.close();
}

Game::~Game() {}

// Load entity data
/*
void Game::load(std::string path)
{
	std::ifstream loader;

	loader.open(path);

	std::stringstream updaterStringStream;
	std::vector<int> updaters;

	std::stringstream rendererStringStream;
	std::vector<int> renderers;

	std::string data;
	while(std::getline(loader, data)) 
	{
		updaterStringStream.str(data.substr(0, data.find(":")));
		rendererStringStream.str(data.substr(updaterStringStream.str().length() + 1));

		std::string temp;
		while(std::getline(updaterStringStream, temp, ','))
		{
			updaters.push_back(temp[0] - '0');
		}
		while(std::getline(rendererStringStream, temp, ','))
		{
			renderers.push_back(temp[0] - '0');
		}
		entities.push_back(this->attachEntityComponents(updaters, renderers));
	}
}

// Create entities using the indexes in game's vectors for its components
Entity Game::attachEntityComponents(std::vector<int> u, std::vector<int> r)
{
	std::vector<UpdateComponent<Entity>*> updaters;
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
*/