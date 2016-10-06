#include "LuaWrapper.h"

LuaWrapper::LuaWrapper()
{

}

LuaWrapper::~LuaWrapper()
{

}

void LuaWrapper::load(string file)
{
	mState.Load(file);
	Log() << int(mState["Button1"]);
	mState["init"]();
	Log() << int(mState["Button1"]);
}

// call the state with yourluawrapper.getState()[0]["stuff"]
sel::State* LuaWrapper::getState()
{
	return &mState;
}
