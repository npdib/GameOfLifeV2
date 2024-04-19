// MenuScreen.h
//   
// (c) eg technology ltd, 2024. All rights reserved. 
//  
// This software is the property of eg technology ltd. and may not be copied or 
// reproduced otherwise than on to a single hard disk for backup or archival 
// purposes. The source code is confidential information and must not be disclosed to third 
// parties or used without the express written permission of eg technology ltd.

#pragma once
#include <vector>
#include "Button.h"
#include "IScreen.h"
#include "olcPixelGameEngine/olcPixelGameEngine.h"

class MenuScreen : public IScreen
{
public:
	MenuScreen(olc::PixelGameEngine* gameEngine);
	~MenuScreen() override = default;

	void update() override;
	void render() override;

private:

	olc::PixelGameEngine* mGameEngine;

	Button mBeginButton;

	std::vector<Button*> mButtons;

};

