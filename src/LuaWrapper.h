#include <string>

#include "include/sol.hpp"
#include "Logger.h"
#include "Button.h"

using namespace std;

class LuaWrapper
{
	public:
		LuaWrapper();
		~LuaWrapper();

		void load(string file);
		sol::state* getState();

		void update(int dt);
		void render();
	private:
		sol::state mState;
};
