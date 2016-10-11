#pragma once

#include <math.h>
#include <string>
#include <SFML/Graphics.hpp>

#include "Logger.h"
#include "Globals.h"

using namespace std;

class SpriteWrapper : public sf::Sprite
{
	public:
		SpriteWrapper();
		SpriteWrapper(string imgfile);
		~SpriteWrapper();

		void setImg(string imgfile);
		void render();

		void scaleTo(float width, float height);
		void setupAnimation(int width, int height);
		void nextFrame(int first, int last, bool mirror);
		unsigned int getFrame();

	private:
		sf::Texture* m_texture;

		// Animation stuff
		sf::IntRect m_animRect;
		unsigned int m_curFrame;
		char m_animDir;
};
