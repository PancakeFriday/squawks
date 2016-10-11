#include "SpriteWrapper.h"

SpriteWrapper::SpriteWrapper()
{
	m_texture = new sf::Texture();
}

SpriteWrapper::SpriteWrapper(string imgfile)
{
	m_texture = new sf::Texture();
	setImg(imgfile);
}

SpriteWrapper::~SpriteWrapper()
{
	m_texture = NULL;
	delete m_texture;
}

void SpriteWrapper::setImg(string imgfile)
{
	m_texture->loadFromFile(imgfile);
	this->setTexture(*m_texture);
}

void SpriteWrapper::render()
{
	globals.getWindow()->draw(*this);
}

void SpriteWrapper::scaleTo(float width, float height)
{
	float x,y;
	x = width / this->getTextureRect().width;
	y = height / this->getTextureRect().height;
	this->setScale(x,y);
}

void SpriteWrapper::setupAnimation(int width, int height)
{
	m_animRect.left = 0;
	m_animRect.top = 0;
	m_animRect.width = width;
	m_animRect.height = height;
	this->setTextureRect(m_animRect);
	m_curFrame = 0;
	m_animDir = 1;
}

// this code **might** work
void SpriteWrapper::nextFrame(int first, int last, bool mirror)
{
	sf::Vector2u imSize = this->getTexture()->getSize();
	int maxHorFrame = floor(imSize.x/m_animRect.width);
	int maxVertFrame = floor(imSize.y/m_animRect.height);

	m_curFrame += m_animDir;
	if(m_curFrame > last)
	{
		if(mirror)
		{
			m_curFrame = last-1;
			m_animDir *= -1;
		}
		else
		{
			m_curFrame = first;
		}
	}
	else if(m_curFrame < first)
	{
		m_curFrame = first+1;
		m_animDir *= -1;
	}

	m_animRect.left = (m_curFrame % (maxHorFrame+1)) * m_animRect.width;
	m_animRect.top = int(floor(m_curFrame / maxHorFrame)) % maxVertFrame * m_animRect.height;
	this->setTextureRect(m_animRect);
}

unsigned int SpriteWrapper::getFrame()
{
	return m_curFrame;
}
