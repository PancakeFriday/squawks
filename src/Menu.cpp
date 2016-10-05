#include "Menu.h"

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::create(int options)
{
	mOptions = options;
}

void Menu::setBackground(string file)
{
	mBackgroundTexture.loadFromFile(file);
	mBackgroundSprite.setTexture(mBackgroundTexture);
}

void Menu::update(int dt)
{

}

void Menu::render()
{
	if(mBackgroundSprite.getTexture() != NULL)
	{
		globals.getWindow()->draw(mBackgroundSprite);
	}
}
