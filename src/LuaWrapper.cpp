#include "LuaWrapper.h"

// first argument in constructor of state loads std lua library
LuaWrapper::LuaWrapper() : mMode(Mode::PAUSE)
{

}

LuaWrapper::~LuaWrapper()
{

}

void LuaWrapper::load(string file)
{
	mState.open_libraries(sol::lib::base, sol::lib::package, sol::lib::table);
	mState.script_file(file);

	mState.set_function("exit", [&](){ mMode = Mode::STOPPED; });

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
			sol::constructors<sol::types<string>>(),
			"render", &Transition::render,
			"update", &Transition::update,
			"set_speed", &Transition::setSpeed
			);

	mState["isKeyDown"] = [](string key)
	{
		// See sfml doc for enum types
		static const char* KeyNames[] = {"A", "B", "C",  "D", "E", "F", "G",  "H", "I", "J", "K",  "L", "M", "N", "O",  "P", "Q", "R"," ""S",  "T", "U", "V", "W",  "X", "Y", "Z", "Num0",  "Num1", "Num2", "Num3", "Num4",  "Num5", "Num6", "Num7", "Num8",  "Num9", "Escape", "LControl", "LShift",  "LAlt", "LSystem", "RControl", "RShift",  "RAlt", "RSystem", "Menu", "LBracket",  "RBracket", "SemiColon", "Comma", "Period",  "Quote", "Slash", "BackSlash", "Tilde",  "Equal", "Dash", "Space", "Return",  "BackSpace", "Tab", "PageUp", "PageDown",  "End", "Home", "Insert", "Delete",  "Add", "Subtract", "Multiply", "Divide",  "Left", "Right", "Up", "Down",  "Numpad0", "Numpad1", "Numpad2", "Numpad3",  "Numpad4", "Numpad5", "Numpad6", "Numpad7",  "Numpad8", "Numpad9", "F1", "F2",  "F3", "F4", "F5", "F6",  "F7", "F8", "F9", "F10",  "F11", "F12", "F13", "F14",  "F15", "Pause", "KeyCount"};
		int i=0;
		for(auto & k : KeyNames)
		{
			if(k == key)
				return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
			++i;
		}
		return false;
	};

	// Careful, the function is not yet called in the if statement!
	if(mState["init"] != sol::nil)
	{
		mState["init"]();
		mMode = Mode::RUNNING;
	}
}

// call the state with yourluawrapper.getState()[0]["stuff"]
sol::state* LuaWrapper::getState()
{
	return &mState;
}
void LuaWrapper::update(int dt)
{
	if(mState["update"] != sol::nil && (mMode & Mode::STOPPED) == 0)
	{
		mState["update"](dt);
	}
}

void LuaWrapper::render()
{
	if(mState["render"] != sol::nil && (mMode & Mode::STOPPED) == 0)
	{
		mState["render"]();
	}
}

int LuaWrapper::getMode()
{
	return mMode;
}
