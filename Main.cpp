#include <stdio.h>
#include <chrono>
#include <ratio>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Ship.h"
#include "PVector.h"
#include "InputHandler.h"

typedef std::chrono::duration<double, std::ratio<1, 1000>> ms;
const ms MS_PER_UPDATE(10);

const int WINDOW_HEIGHT = 900;
const int WINDOW_WIDTH = 1600;

int main()
{	
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gravity Well");

	InputHandler handler;
	/*
	Ship testShip;

	testShip.setPose(800, 450, 50, 50, 0, 0);
	testShip.setMass(10000);
	testShip.setCrossSectionalArea(1000);
	testShip.setDragCoefficient(0.1);
	*/

	std::chrono::steady_clock::time_point previous = std::chrono::steady_clock::now();
	ms lag(0);

	while(window.isOpen()) // Game loop
	{
		std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
		ms elapsed = std::chrono::duration_cast<ms>(current - previous);
		previous = current;
		lag += elapsed;
		
		printf("%i \n", handler.handleInput()[sf::Keyboard::Key::A]); 

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				deafult:
					break;
			}
		}

		while(lag >= MS_PER_UPDATE)
		{
			// testShip.update(MS_PER_UPDATE.count());
			lag -= MS_PER_UPDATE;
		}

		window.clear();

		/*
		sf::CircleShape shipShape(50);
		shipShape.setPosition(testShip.getPosition().getX(), testShip.getPosition().getY());
		shipShape.setOrigin(50, 50);

		window.draw(shipShape);

		printf("%f \n", testShip.getVelocity().getX());
		*/

		window.display();
	}
	return 0;
}