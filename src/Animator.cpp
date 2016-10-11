#include "Animator.h"

Animator::Animator()
{
	m_texture = new sf::Texture();
}

Animator::Animator(string imgfile)
{
	m_texture = new sf::Texture();
	setImg(imgfile);
}

Animator::~Animator()
{
	m_texture = NULL;
	delete m_texture;
}

// name: the name of the animation
// frameRect: the texture rectangle (i.e. where the very first frame sits + its dimensions)
// startRow, startCol is the number (starting with 0) where the animation starts
// endRow, endCol respectively
// delay: time between frames
void Animator::createAnimation(string name, sf::IntRect frameRect, uint startCol, uint startRow,
		uint endCol, uint endRow, uint delay = 0, int options = Options::Repeat)
{
	auto it = mAnimations.find(name);
	if(it != mAnimations.end())
	{
		Log(Level::Warning) << "Animation " << name << " already found, are you sure you want to recreate it?";
	}
	setFrameRect(name, frameRect);
	setStart(name, startCol, startRow);
	setEnd(name, endCol, endRow);
	setGlobalDelay(name, delay);
	setOptions(name, options);
}

void Animator::setFrameRect(string name, sf::IntRect frameRect)
{
	mAnimations[name].frameRect = frameRect;
}

void Animator::setStart(string name, uint startCol, uint startRow)
{
	mAnimations[name].startCol = startCol;
	mAnimations[name].startRow = startRow;
}

void Animator::setEnd(string name, uint endCol, uint endRow)
{
	mAnimations[name].endCol = endCol;
	mAnimations[name].endRow = endRow;
}

// Use this to create an animation like this buildAnimation("dancing", "wait(10)", "next", "wait")
void Animator::setOptions(string name, int options)
{
	mAnimations[name].options = options;
}

void Animator::setGlobalDelay(string name, uint delay)
{
	mAnimations[name].delay = delay;
}

void Animator::setSingleDelay(string name, uint delay, uint Col, uint Row)
{
	mAnimations[name].singleDelay[make_pair(Col, Row)] = delay;
}

void Animator::animate(string name)
{
	auto it = mAnimations.find(name);
	if(it == mAnimations.end())
	{
		Log(Level::Error) << "Could not find animation " << name << "! Aborting animation.";
	}

	if(mCurrentAnimation != name)
	{
		mCurrentAnimation = name;
		mAnimations[name].curRow = mAnimations[name].startRow;
		mAnimations[name].curCol = mAnimations[name].startCol;
		mDelayClock.restart();

		AnimObject* t = &mAnimations[name];
		sf::IntRect tempRect = t->frameRect;
		tempRect.left = (2*tempRect.left + tempRect.width) * t->curCol;
		tempRect.top = (2*tempRect.top + tempRect.height) * t->curRow;
		this->setTextureRect(tempRect);
	}

	AnimObject* t = &mAnimations[name];
	uint time = mDelayClock.getElapsedTime().asMilliseconds();
	if(time < t->singleDelay[std::make_pair(t->curCol, t->curRow)])
	{
		return;
	}
	else if(time < mAnimations[name].delay)
	{
		return;
	}
	else
	{
		mDelayClock.restart();
	}
	//if(mDelayClock.getElapsedTime().asMilliseconds() < )
	//Log() << get<2>(mAnimations[name].singleDelay);
	nextFrame(name);
}

void Animator::nextFrame(string name)
{
	AnimObject* t = &mAnimations[mCurrentAnimation];
	if(t->curRow == -1 || t->curCol == -1)
	{
	}
	else
	{
		// -1 because we use it like we use the other cols as indexing
		int maxCols = floor(getTexture()->getSize().x / t->frameRect.width)-1;
		if(t->dir == 1)
		{
			if(t->curCol >= maxCols && t->curRow < t->endRow)
			{
				t->curCol = 0;
				t->curRow += 1;
			}
			else if(t->curRow < t->endRow)
			{
				t->curCol += 1;
			}
			else if(t->curCol < t->endCol)
			{
				t->curCol += 1;
			}
			else if(t->options & Options::Repeat)
			{
				t->curCol = t->startRow;
				t->curRow = t->startRow;
			}
			else if(t->options & Options::Harmonic)
			{
				t->dir = -1;
				t->curCol -= 1;
			}
		}
		else
		{
			if(t->curCol <= 0 && t->curRow > t->startRow)
			{
				t->curCol = maxCols;
				t->curRow -= 1;
			}
			else if(t->curRow > t->startRow)
			{
				t->curCol -= 1;
			}
			else if(t->curCol > t->startCol)
			{
				t->curCol -= 1;
			}
			else if(t->options & Options::Repeat)
			{
				t->curCol = t->endCol;
				t->curRow = t->endRow;
			}
			else if(t->options & Options::Harmonic)
			{
				t->dir = 1;
				t->curCol += 1;
			}
		}

		sf::IntRect tempRect = t->frameRect;
		tempRect.left = (2*tempRect.left + tempRect.width) * t->curCol;
		tempRect.top = (2*tempRect.top + tempRect.height) * t->curRow;
		this->setTextureRect(tempRect);
	}
}
