#include <map>
#include <string>

#include "SpriteWrapper.h"

using namespace std;

class Animator : public SpriteWrapper
{
	public:
		enum Options {
			Repeat = 1,		// Repeat the animation
			Mirror = 2,		// Mirror the sprite
			Harmonic = 4	// The animation will go back and forth
		};
		Animator();
		Animator(string imgfile);
		~Animator();

		void createAnimation(string name, sf::IntRect frameRect, uint startCol, uint startRow,
				uint endCol, uint endRow, uint delay, int options);
		void setFrameRect(string name, sf::IntRect frameRect);
		void setStart(string name, uint startCol, uint startRow);
		void setEnd(string name, uint endCol, uint endRow);
		void setGlobalDelay(string name, uint delay);
		void setSingleDelay(string name, uint delay, uint Col, uint Row);
		void setOptions(string name, int options);

		void animate(string name);

	private:
		struct AnimObject
		{
			friend class Animator;
			sf::IntRect frameRect;
			uint startRow;
			uint startCol;
			uint endRow;
			uint endCol;
			int options;
			uint delay;

			private:
				uint curRow = -1;
				uint curCol = -1;
				char dir = 1;
				map<pair<uint, uint>, uint> singleDelay;
		};

		sf::Texture* m_texture;
		string mCurrentAnimation;
		map<string, AnimObject> mAnimations;
		sf::Clock mDelayClock;

		void nextFrame(string name);
};
