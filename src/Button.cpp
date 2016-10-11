#include "Button.h"

extern Globals globals;

// Will need the imagefile to create the button.
// Set the default function to an empty lambda (to counter segfaults)
Button::Button(string imgfile) : mOnPress([&](){})
{
	mTexture.loadFromFile(imgfile);
	mSprite.setTexture(mTexture);

	// set Texture rectangle
	// since the button has 3 states, we can find them in 3 rows
	// first row: idle, second row: hover, third row: press
	int height = mTexture.getSize().y;
	int width = mTexture.getSize().x;
	mSprite.setTextureRect(sf::IntRect(0,0,width,height/3));

	mState = IDLE;
}

Button::~Button()
{

}

// Some collision code to check if the mouse is in the button
// Then do hover and click actions
void Button::update(int dt)
{
	Collider<sf::FloatRect, sf::Vector2i> buttonCollider(mSprite.getGlobalBounds(), sf::Mouse::getPosition(*globals.getWindow()));

	int height = mTexture.getSize().y;
	int width = mTexture.getSize().x;

	bool mouseReleased = false;
	vector<int> events = globals.getEvents();
	for(auto &v : events)
	{
		if(v == sf::Event::MouseButtonReleased)
			mouseReleased = true;
	}

	if(buttonCollider.collides())
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mState = PRESS;
			mSprite.setTextureRect(sf::IntRect(0,2*height/3,width,height/3));
		}
		else
		{
			mState = HOVER;
			mSprite.setTextureRect(sf::IntRect(0,height/3,width,height/3));
			if(mouseReleased)
				mOnPress();
		}
	}
	else
	{
		mState = IDLE;
		mSprite.setTextureRect(sf::IntRect(0,0,width,height/3));
	}
}

void Button::render()
{
	globals.getWindow()->draw(mSprite);
}

//void Button::setPosition(sf::Vector2f pos)
//{
	//mSprite.setPosition(pos);
//}

void Button::setPosition(float x, float y)
{
	mSprite.setPosition(x,y);
}

void Button::setAction(function<void()> action)
{
	mOnPress = action;
}
