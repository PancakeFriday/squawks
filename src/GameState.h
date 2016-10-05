#include <string>
#include <SFML/System.hpp>

using namespace std;

class GameState
{
	public:
		GameState(string state);
		~GameState();

		void update(float dt);
		void render();

		float set(string state);

	private:
		sf::Clock mTransitionTimer;

		string mCurrentState;
		string mNextState;
};
