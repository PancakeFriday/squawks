#include "Squawks.h"
logger Log(LOGFILE);
Globals globals;

Squawks::Squawks()
{

}

Squawks::~Squawks()
{

}

int Squawks::init()
{
	Log(Level::Info) << "Starting Engine";

	globals.getWindow()->setFramerateLimit(60);

	mGameState = make_shared<GameState>("Menu");

  mLuaStates["mainmenu"] = make_shared<LuaWrapper>();
  mLuaStates["mainmenu"]->load("lua/MainMenu.lua");

	return EXIT_SUCCESS;
}

void Squawks::run()
{
	while(globals.mRunning)
	{
		//Log() << mLuaStates.size();
		for (auto it = mLuaStates.cbegin(); it != mLuaStates.cend(); )
		{
			if((it->second->getMode() & LuaWrapper::Mode::RUNNING) == 0)
			{
				mLuaStates.erase(it++);
			}
			else
			{
				++it;
			}
		}

		// Close when escape is pressed
		if (globals.getWindow()->hasFocus())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				globals.mRunning = false;
			}
		}

		// Close when there are no lua scripts running
		if(mLuaStates.size() == 0)
			globals.mRunning = false;

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

	for(auto &it : mLuaStates)
		it.second->update(dt);
}

void Squawks::render()
{
	// Clear screen
	globals.getWindow()->clear();

	for(auto &it : mLuaStates)
		it.second->render();

	// Update the window
	globals.getWindow()->display();
}
