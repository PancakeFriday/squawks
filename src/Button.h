#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Globals.h"
#include "Collider.h"

using namespace std;

class Button
{
	public:
		Button(string imgfile);
		~Button();

		void update(int dt);
		void render();

		//void setPosition(sf::Vector2f pos);
		void setPosition(float x, float y);
		void setAction(function<void()> action);

	private:
		enum States{
			IDLE,
			HOVER,
			PRESS
		};

		sf::Texture mTexture;
		sf::Sprite mSprite;

		int mState;

		function<void()> mOnPress;
};
