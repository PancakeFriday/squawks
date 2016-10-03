#include "Squawks.h"

#define WIN_WIDTH 1024
#define WIN_HEIGHT 678

Squawks::Squawks()
{

}

Squawks::~Squawks()
{

}

int Squawks::init()
{
	bool running = true;
	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Test");
	window.setFramerateLimit(60);

	while(running)
	{
		if (window.hasFocus())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				running = false;
			}
		}

		// Clear screen
		window.clear();
		// Update the window
		window.display();
	}

}
