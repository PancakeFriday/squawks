#include "Transition.h"

Transition::Transition(string effect)
{
	if(effect == "fadeOut")
		mEffect = make_shared<TransitionEffect::FadeOut>();
}

Transition::~Transition()
{

}

void Transition::update(int dt)
{
	mEffect->update(dt);
}

void Transition::render()
{
	mEffect->render();
}

void Transition::setSpeed(float speed)
{
	mEffect->setSpeed(speed);
}

namespace TransitionEffect
{
	FadeOut::FadeOut() : mBlack(255)
	{
		sf::Vector2u windowSize = globals.getWindow()->getSize();
		mBackgroundTex.create(windowSize.x, windowSize.y);
		mBackgroundTex.update(*globals.getWindow());
		mBackground.setTexture(mBackgroundTex);
		sf::Image im = mBackgroundTex.copyToImage();
	}

	FadeOut::~FadeOut()
	{

	}

	void FadeOut::update(int dt)
	{
		Log() << mSpeed;
		if(mBlack-dt > 0)
			mBlack -= mSpeed*dt;
		else
			mBlack = 0;
	}

	void FadeOut::render()
	{
		globals.getWindow()->draw(mBackground);
		mBackground.setColor(sf::Color(mBlack, mBlack, mBlack, 255));
	}
}
