#include <string>

#include "include/sol.hpp"
#include "Logger.h"
#include "Button.h"
#include "SpriteWrapper.h"
#include "Animator.h"
#include "Transition.h"

using namespace std;

class LuaWrapper
{
	public:
		enum Mode {
			RUNNING = 1,
			PAUSE = 2,
			STOPPED = 4,
		};

		LuaWrapper();
		~LuaWrapper();

		void load(string file);
		sol::state* getState();

		void update(int dt);
		void render();
		int getMode();
	private:
		sol::state mState;
		int mMode;
};
