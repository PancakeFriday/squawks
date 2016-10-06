#include "Squawks.h"
logger Log(LOGFILE);
Globals globals;

Squawks::Squawks() : mRunning(true)
{

}

Squawks::~Squawks()
{

}

void test()
{
	cout << "test" << endl;
}

void test2()
{
	cout << "test2" << endl;
}

int Squawks::init()
{
	Log(Level::Info) << "Starting Engine";

	globals.getWindow()->setFramerateLimit(60);

	mGameState = make_shared<GameState>("Menu");

	mMainMenu.load("lua/MainMenu.lua");
	Log() << int(mMainMenu.getState()[0]["Button1"]);

	return EXIT_SUCCESS;
}

void Squawks::run()
{
	while(mRunning)
	{
		if (globals.getWindow()->hasFocus())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				mRunning = false;
			}
		}

		update();
		render();
	}
}

void Squawks::close()
{
	Log(Level::Info) << "Stopping Engine";
}

void Squawks::update()
{
	globals.pollEvents();
	int dt = mDeltaClock.restart().asMilliseconds();
	mGameState->update(dt);
}

void Squawks::render()
{
		// Clear screen
		globals.getWindow()->clear();

		// Update the window
		globals.getWindow()->display();
}
