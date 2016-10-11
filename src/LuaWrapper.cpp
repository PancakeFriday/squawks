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
	mState.open_libraries(sol::lib::base, sol::lib::package, sol::lib::table);
	mState.script_file(file);

	/* Bind all relevant classes here */
	mState.new_usertype<Button>("Button",
			sol::constructors<sol::types<string>>(),
			"set_position", &Button::setPosition,
			"set_action", &Button::setAction,
			"update", &Button::update,
			"render", &Button::render);

	mState.new_usertype<SpriteWrapper>("Sprite",
			sol::constructors<sol::types<string>>(),
			"set_img", &SpriteWrapper::setImg,
			"set_position", sol::resolve<void(float, float)>(&SpriteWrapper::setPosition),
			"get_position", &SpriteWrapper::getPosition,
			"render", &SpriteWrapper::render,
			"scale_to", &SpriteWrapper::scaleTo,
			"setup_animation", &SpriteWrapper::setupAnimation,
			"get_frame", &SpriteWrapper::getFrame,
			"move", sol::resolve<void(float, float)>(&SpriteWrapper::move)
			);

	mState.new_usertype<Animator>("Animator",
			sol::constructors<sol::types<string>>(),
			"set_img", &Animator::setImg,
			"create_animation", &Animator::createAnimation,
			"set_frame_rect", &Animator::setFrameRect,
			"set_start", &Animator::setStart,
			"set_end", &Animator::setEnd,
			"set_global_delay", &Animator::setGlobalDelay,
			"set_single_delay", &Animator::setSingleDelay,
			"set_position", sol::resolve<void(float, float)>(&Animator::setPosition),
			"get_position", &Animator::getPosition,
			"animate", &Animator::animate,
			"render", &Animator::render,
			"scale_to", &Animator::scaleTo,
			"setup_animation", &Animator::setupAnimation,
			"get_frame", &Animator::getFrame,
			"move", sol::resolve<void(float, float)>(&Animator::move)
			);

	mState.new_usertype<sf::Vector2f>("Vec2f",
			sol::constructors<sol::types<float, float>>(),
			"x", &sf::Vector2f::x,
			"y", &sf::Vector2f::y
			);

	mState.new_usertype<sf::IntRect>("IntRect",
			sol::constructors<sol::types<int, int, int, int>>(),
			"left", &sf::IntRect::left,
			"top", &sf::IntRect::top,
			"width", &sf::IntRect::width,
			"height", &sf::IntRect::height
			);

	mState.new_usertype<Transition>("Transition",
			sol::constructors<sol::types<>>()
			);

	// Careful, the function is not yet called in the if statement!
	if(mState["init"] != sol::nil)
		mState["init"]();
}

// call the state with yourluawrapper.getState()[0]["stuff"]
sol::state* LuaWrapper::getState()
{
	return &mState;
}
void LuaWrapper::update(int dt)
{
	if(mState["update"] != sol::nil)
		mState["update"](dt);
}

void LuaWrapper::render()
{
	if(mState["render"] != sol::nil)
		mState["render"]();
}
