#include "GameState.h"

GameState::GameState(string state) : mCurrentState(state), mNextState(state)
{

}

GameState::~GameState()
{

}

void GameState::update(float dt)
{

}

void GameState::render()
{
	if(mNextState == mCurrentState)
		return;

	// Do some transition
	if(mCurrentState == "Menu" && mNextState == "MainGame")
	{
		// Timer for transition
	}
}

float GameState::set(string state)
{
	if(state != mNextState)
	{
		mNextState = state;
		mTransitionTimer.restart();
	}

	return mTransitionTimer.getElapsedTime().asMilliseconds();
}
