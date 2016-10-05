#include <string>
#include <SFML/Graphics.hpp>

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
		Options mOptions;

		//sf::Texture mBackgroundTexture;
		//sf::Sprite mBackgroundSprite;

};
