#include "Game.hpp"
#include <iostream>
int main() {

	try
	{
		Game game;
		while (!game.GetWindow()->IsDone()) {
			game.HandleInput();
			game.Update();
			game.Render();
			game.RestartClock();
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

}