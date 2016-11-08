#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Logger.h"

using namespace std;

namespace TransitionEffect
{
	class Base
	{
		public:
			virtual void update(int dt) = 0;
			virtual void render() = 0;
			virtual void setSpeed(float speed) { mSpeed = speed; }
			virtual bool finished() = 0;
		protected:
			float mSpeed;
	};

	class FadeOut : public Base
	{
		public:
			FadeOut();
			~FadeOut();

			void update(int dt);
			void render();
			bool finished();

		private:
			sf::Texture mBackgroundTex;
			sf::Sprite mBackground;
			int mBlack;
			bool mIsFinished;
	};
};

class Transition
{
	public:
		Transition(string effect);
		~Transition();

		void update(int dt);
		void render();

		bool finished();
		void setSpeed(float speed);

	private:
		shared_ptr<TransitionEffect::Base> mEffect;
};
