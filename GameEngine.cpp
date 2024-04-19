// GameEngine.cpp
//   
// (c) eg technology ltd, 2024. All rights reserved. 
//  
// This software is the property of eg technology ltd. and may not be copied or 
// reproduced otherwise than on to a single hard disk for backup or archival 
// purposes. The source code is confidential information and must not be disclosed to third 
// parties or used without the express written permission of eg technology ltd.

#include "GameEngine.h"

GameEngine::GameEngine()
	: mMenu(this)
	, mCurrentScreen(&mMenu)
{
	sAppName = "Game of Life";
}

bool GameEngine::OnUserCreate()
{
	return true;
}

bool GameEngine::OnUserUpdate(float fElapsedTime)
{
	mCurrentScreen->update();
	mCurrentScreen->render();
	return true;
}

bool GameEngine::OnUserDestroy()
{
	return true;
}

void GameEngine::ChangeState(State newState)
{
	if (newState != mState)
	{
		mState = newState;
		switch (mState)
		{
		case State::Menu: 
			mCurrentScreen = &mMenu;
			break;
		case State::Setup: break;
		case State::Running: break;
		case State::Finished: break;
		default: ;
		}
	}
}
