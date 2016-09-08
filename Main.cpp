#include <stdio.h>

#include <chrono>
#include <ratio>

#include <SFML/Graphics.hpp>

typedef std::chrono::duration<double, std::ratio<1, 1000>> milliseconds;
const milliseconds MS_PER_UPDATE(5); // Time between updates

const int WINDOW_HEIGHT = 900;
const int WINDOW_WIDTH = 1600;

int main()
{
	std::chrono::steady_clock::time_point previous = std::chrono::steady_clock::now();
	milliseconds lag(0);

	while (true) // Game loop
	{
		std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
		milliseconds elapsed = std::chrono::duration_cast<milliseconds>(current - previous);
		previous = current;
		lag += elapsed;

		// Process input

		while (lag >= MS_PER_UPDATE)
		{
			// Update logic
			lag -= MS_PER_UPDATE;
		}

		// Render output
	}
	return 0;
}