#include "LuaWrapper.h"

// first argument in constructor of state loads std lua library
LuaWrapper::LuaWrapper()
{

}

LuaWrapper::~LuaWrapper()
{

}

void LuaWrapper::load(string file)
{
	mState.open_libraries(sol::lib::base, sol::lib::package);
	mState.script_file(file);
	mState.new_usertype<Button>("Button",
			sol::constructors<sol::types<string>>(),
			"set_position", &Button::setPosition,
			"set_action", &Button::setAction,
			"update", &Button::update,
			"render", &Button::render);
	mState["init"]();
}

// call the state with yourluawrapper.getState()[0]["stuff"]
sol::state* LuaWrapper::getState()
{
	return &mState;
}
void LuaWrapper::update(int dt)
{
	mState["update"](dt);
}

void LuaWrapper::render()
{
	mState["render"]();
}
