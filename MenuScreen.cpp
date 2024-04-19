// MenuScreen.cpp
//   
// (c) eg technology ltd, 2024. All rights reserved. 
//  
// This software is the property of eg technology ltd. and may not be copied or 
// reproduced otherwise than on to a single hard disk for backup or archival 
// purposes. The source code is confidential information and must not be disclosed to third 
// parties or used without the express written permission of eg technology ltd.

#include "MenuScreen.h"
#include "GameEngine.h"

MenuScreen::MenuScreen(GameEngine* gameEngine)
	: mGameEngine(gameEngine)
	, mBeginButton(mGameEngine, Button::Config{ 45, 12, "Begin", {57, 70}, {3, 2}, olc::WHITE, olc::DARK_BLUE, olc::DARK_GREEN })
	, mExitButton(mGameEngine, Button::Config{ 45, 12, "Exit", {57, 90}, {5, 2}, olc::WHITE, olc::DARK_BLUE, olc::DARK_GREEN })
{
	mButtons.push_back(&mBeginButton);
	mButtons.push_back(&mExitButton);
}

void MenuScreen::update()
{
	for (const auto& button : mButtons)
	{
		button->UpdateActive();
	}

	if (mGameEngine->GetMouse(olc::Mouse::LEFT).bPressed || mGameEngine->GetMouse(olc::Mouse::LEFT).bHeld)
	{
		if (mBeginButton.GetActive())
		{
			mGameEngine->ChangeState(GameEngine::State::Setup);
		}
	}
}

void MenuScreen::render()
{
	mGameEngine->DrawString({ (mGameEngine->ScreenWidth() - 100) / 2, (mGameEngine->ScreenHeight() - 30) / 6 }, "  Conway's\nGame of Life");

	for (const auto& button : mButtons)
	{
		button->draw();
	}

}
