#include "Game.h"
#include <iostream>

int main()
{	
	Game g;

	Game::ms tR(40);

	g.init(1600, 900, tR);

	g.loop();

	g.exit();

	return 0;
}