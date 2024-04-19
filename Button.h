// Button.h
//   
// (c) eg technology ltd, 2024. All rights reserved. 
//  
// This software is the property of eg technology ltd. and may not be copied or 
// reproduced otherwise than on to a single hard disk for backup or archival 
// purposes. The source code is confidential information and must not be disclosed to third 
// parties or used without the express written permission of eg technology ltd.

#pragma once
#include <cstdint>
#include "olcPixelGameEngine/olcPixelGameEngine.h"

class Button
{
public:
	struct Config
	{
		uint16_t width;
		uint16_t height;
		std::string text;
		olc::vi2d position;
		olc::vi2d textOffset;
		olc::Pixel textColour;
		olc::Pixel bgColour;
		olc::Pixel highlightColour;
	};

	Button(olc::PixelGameEngine* gameEngine, const Config& config);
	~Button() = default;

	void CheckActive();
	void draw() const;

private:
	olc::PixelGameEngine* mGameEngine;
	bool mActive;
	const Config mConfig;

	bool mMouseXContained(const uint32_t& mouseX) const;
	bool mMouseYContained(const uint32_t& mouseY) const;
};

