#pragma once

#include <memory>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

class Globals;
extern Globals globals;

class Globals
{
	public:
		Globals();
		~Globals();

		sf::RenderWindow* getWindow();
		void pollEvents();
		vector<int> getEvents();

	private:
		sf::RenderWindow mWindow;
		vector<int> mEvents;

};
