// MenuScreen.cpp
//   
// (c) eg technology ltd, 2024. All rights reserved. 
//  
// This software is the property of eg technology ltd. and may not be copied or 
// reproduced otherwise than on to a single hard disk for backup or archival 
// purposes. The source code is confidential information and must not be disclosed to third 
// parties or used without the express written permission of eg technology ltd.

#include "MenuScreen.h"

#include "Button.h"

MenuScreen::MenuScreen(olc::PixelGameEngine* gameEngine)
	: mGameEngine(gameEngine)
	, mBeginButton(mGameEngine, Button::Config{ 45, 12, "Begin", {57, 70}, {3, 2}, olc::WHITE, olc::DARK_BLUE, olc::DARK_GREEN })
{
	mButtons.push_back(&mBeginButton);
}

void MenuScreen::update()
{
	for (const auto& button : mButtons)
	{
		button->CheckActive();
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
