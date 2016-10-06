#include <string>

#include "include/selene.h"
#include "Logger.h"

using namespace std;

class LuaWrapper
{
	public:
		LuaWrapper();
		~LuaWrapper();

		void load(string file);
		sel::State* getState();
	private:
		sel::State mState;
};
