#include "Game.h"

int main()
{	
	Game g;

	Game::ms tR(20);

	g.init(1600, 900, tR);

	g.loop();

	return 0;
}