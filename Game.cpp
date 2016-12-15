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