#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Logger.h"
#include "GameState.h"
#include "Button.h"
#include "Menu.h"
#include "LuaWrapper.h"

using namespace std;

class Squawks
{
	public:
		Squawks();
		~Squawks();

		int init();
		void run();
		void close();

		void update();
		void render();

	private:
		sf::Clock mDeltaClock;

		shared_ptr<GameState> mGameState;

		/* Here goes the menus and eventually the game */
    map<string, shared_ptr<LuaWrapper>> mLuaStates;
};
