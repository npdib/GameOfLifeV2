// Button.cpp
//   
// (c) eg technology ltd, 2024. All rights reserved. 
//  
// This software is the property of eg technology ltd. and may not be copied or 
// reproduced otherwise than on to a single hard disk for backup or archival 
// purposes. The source code is confidential information and must not be disclosed to third 
// parties or used without the express written permission of eg technology ltd.

#include "Button.h"

Button::Button(olc::PixelGameEngine* gameEngine, const Config& config)
	: mGameEngine(gameEngine)
	, mActive(false)
	, mConfig(config)
{
}

void Button::UpdateActive()
{
	const olc::vi2d mousePos = mGameEngine->GetMousePos();

	mActive = mMouseXContained(mousePos.x) && mMouseYContained(mousePos.y);
}

void Button::draw() const
{
	mGameEngine->FillRect(mConfig.position, { mConfig.width, mConfig.height }, mActive ? mConfig.highlightColour : mConfig.bgColour);
	mGameEngine->DrawString({mConfig.position.x + mConfig.textOffset.x, mConfig.position.y + mConfig.textOffset.y}, mConfig.text, mConfig.textColour);
}

bool Button::mMouseXContained(const uint32_t& mouseX) const
{
	if (mouseX >= mConfig.position.x && mouseX <= mConfig.position.x + mConfig.width)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Button::mMouseYContained(const uint32_t& mouseY) const
{
	if (mouseY >= mConfig.position.y && mouseY <= mConfig.position.y + mConfig.height)
	{
		return true;
	}
	else
	{
		return false;
	}
}