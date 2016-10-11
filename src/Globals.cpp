#include "Globals.h"

#define WIN_WIDTH 1024
#define WIN_HEIGHT 640

// IMPLEMENT READING CONFIG

Globals::Globals() : mWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Test")
{

}

Globals::~Globals()
{

}

sf::RenderWindow* Globals::getWindow()
{
	return &mWindow;
}

void Globals::pollEvents()
{
	mEvents.clear();
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		// Request for closing the window
		if (event.type == sf::Event::MouseButtonReleased)
		{
			mEvents.push_back(event.type);
		}
	}
}

vector<int> Globals::getEvents()
{
	return mEvents;
}
