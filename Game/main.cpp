#include "PESPGame.h"

int main()
{
	try
	{
		PESPGame game;
		game.run();
	}
	catch (const std::exception& e)
	{
		std::string s = "Error: ";
		s += e.what();
	}
}