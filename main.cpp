// main.cpp
//   
// (c) eg technology ltd, 2024. All rights reserved. 
//  
// This software is the property of eg technology ltd. and may not be copied or 
// reproduced otherwise than on to a single hard disk for backup or archival 
// purposes. The source code is confidential information and must not be disclosed to third 
// parties or used without the express written permission of eg technology ltd.

#define OLC_PGE_APPLICATION

#include <iostream>

#include "GameEngine.h"

int main()
{
	GameEngine game_engine;

	if (game_engine.Construct(160, 160, 4, 4))
	{
		game_engine.Start();
	}

	std::cout << "Game Exited...\n";
	return 0;
}
