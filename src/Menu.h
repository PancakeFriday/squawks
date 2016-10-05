#include <string>
#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Logger.h"

using namespace std;

class Menu
{
	public:
		enum Options {
			FULLSCREEN
		};

		Menu();
		~Menu();

		void update(int dt);
		void render();

		void create(int options);
		void setBackground(string file);

	private:
		int mOptions;

		sf::Texture mBackgroundTexture;
		sf::Sprite mBackgroundSprite;

};
