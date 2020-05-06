#include <iostream>
#include "Game.h"

//using namespace sf

int main()
{
	std::cout << "Hello World!" << std::endl;
	std::cout << "This is my first C++ game!" << std::endl;

	//Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	//Init Game engine
	Game game;

	//Game loop
	while (game.running() && !game.getEndGame())
	{
		//Update
		game.update();

		//Render
		game.render();
	}

	//End of application
	return 0;
}

