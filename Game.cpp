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

	ArrowVelocityIC* avic = new ArrowVelocityIC();
	inputComponents.push_back(avic);
	TowardsMouseIC* tmic = new TowardsMouseIC();
	inputComponents.push_back(tmic);

	BasicVelocityUC* bvuc = new BasicVelocityUC();
	updateComponents.push_back(bvuc);
	
	PrintPositionRC* pprc = new PrintPositionRC();
	renderComponents.push_back(pprc);
	DrawCircleRC* dcrc = new DrawCircleRC();
	renderComponents.push_back(dcrc);

	Entity e(avic, bvuc, dcrc);
	entities.push_back(e);

	Entity e2(tmic, bvuc, dcrc );
	entities.push_back(e2);
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
			entities[i].getInputComponent()->input(entities[i], &window);
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
			// Components to get updated in the order of the entities
			for(unsigned int i = 0; i < entities.size(); i++)
			{
				entities[i].getUpdateComponent()->update(entities[i], tickRate.count());
			}

			// Components to get updated after all entities have been updated

			lag -= tickRate;
		}

		// Rendering
		window.clear();
		for(unsigned int i = 0; i < entities.size(); i++)
		{
			entities[i].getRenderComponent()->render(entities[i], &window);
		}
		window.display();
	}
}

void Game::exit()
{
	// Delete all the input components still on the heap
	for (unsigned int i = 0; i < inputComponents.size(); i++)
	{
		delete inputComponents[i];
		inputComponents[i] = NULL;
	}
	inputComponents.clear();

	// Delete all the update components still on the heap
	for(unsigned int i = 0; i < updateComponents.size(); i++)
	{
		delete updateComponents[i];
		updateComponents[i] = NULL;
	}
	updateComponents.clear();

	// Delete all the render components still on the heap
	for(unsigned int i = 0; i < renderComponents.size(); i++)
	{
		delete renderComponents[i];
		renderComponents[i] = NULL;
	}
	renderComponents.clear();

	entities.clear();

	window.close();
}

Game::~Game()
{

}

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