// SetupScreen.cpp
//   
// (c) eg technology ltd, 2024. All rights reserved. 
//  
// This software is the property of eg technology ltd. and may not be copied or 
// reproduced otherwise than on to a single hard disk for backup or archival 
// purposes. The source code is confidential information and must not be disclosed to third 
// parties or used without the express written permission of eg technology ltd.

#include "SetupScreen.h"

#include "Button.h"
#include "GameEngine.h"

SetupScreen::SetupScreen(GameEngine* gameEngine)
	: mGameEngine(gameEngine)
	, mRowMinus(mGameEngine, Button::Config{ 10, 10, "-", {10, 145}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mRowPlus(mGameEngine, Button::Config{ 10, 10, "+", {50, 145}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mColumnMinus(mGameEngine, Button::Config{10, 10, "-", {100, 145}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN})
	, mColumnPlus(mGameEngine, Button::Config{ 10, 10, "+", {140, 145}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mGo(mGameEngine, Button::Config{ 30, 10, "Go", {65, 145}, {7, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN})
	, mRows(10)
	, mColumns(10)
{
	mButtons.push_back(mRowPlus);
	mButtons.push_back(mRowMinus);
	mButtons.push_back(mColumnPlus);
	mButtons.push_back(mColumnMinus);
	mButtons.push_back(mGo);
}

void SetupScreen::update()
{
	for (auto& button : mButtons)
	{
		button.UpdateActive();
	}

	if (mGameEngine->GetMouse(olc::Mouse::LEFT).bPressed || mGameEngine->GetMouse(olc::Mouse::LEFT).bHeld)
	{
		if (mRowMinus.GetActive())
		{
			if (mRows > 1)
			{
				--mRows;
			}
		}

		if (mRowPlus.GetActive())
		{
			if (mRows < 30)
			{
				++mRows;
			}
		}

		if (mColumnMinus.GetActive())
		{
			if (mColumns > 1)
			{
				--mColumns;
			}
		}

		if (mColumnPlus.GetActive())
		{
			if (mColumns < 30)
			{
				++mColumns;
			}
		}

		if (mGo.GetActive())
		{
			mGameEngine->ChangeState(GameEngine::State::Running);
		}
	}
}

void SetupScreen::render()
{
	mGameEngine->DrawString({ (mGameEngine->ScreenWidth() - 40) / 2, 5 }, "Setup");
	mGameEngine->DrawString({ 113, 147 }, "Row");
	mGameEngine->DrawString({ 24, 147 }, "Col");

	for (const auto& button : mButtons)
	{
		button.draw();
	}
}