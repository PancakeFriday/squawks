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
		protected:
			float mSpeed;
	};

	class FadeOut : public Base
	{
		public:
			FadeOut();
			~FadeOut();

		private:
			void update(int dt);
			void render();

			sf::Texture mBackgroundTex;
			sf::Sprite mBackground;
			int mBlack;
	};
};

class Transition
{
	public:
		Transition(string effect);
		~Transition();

		void update(int dt);
		void render();
		void setSpeed(float speed);
	private:
		shared_ptr<TransitionEffect::Base> mEffect;
};
