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
	: mState(State::Menu)
	, mMenu(this)
	, mSetup(this)
	, mRunning(this)
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
	ClearScreen();

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
		switch (newState)
		{
		case State::Menu: 
			mCurrentScreen = &mMenu;
			break;
		case State::Setup:
			if (mState == State::Running)
			{
				mSetup.UpdateBoard(mRunning.GetCellBoard());
			}
			mCurrentScreen = &mSetup;
			break;
		case State::Running:
			mRunning.UpdateBoard(mSetup.GetCellBoard());
			mRunning.ClearSteps();
			mCurrentScreen = &mRunning;
			break;
		case State::Finished: break;
		case State::Exit:
			olc_Terminate();
			break;
		default: 
			break;;
		}

		mState = newState;
	}
}

void GameEngine::ClearScreen()
{
	FillRect({ 0, 0 }, { ScreenWidth(), ScreenHeight() }, olc::BLACK);
}
