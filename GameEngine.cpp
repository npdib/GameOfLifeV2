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
{
	sAppName = "Game of Life";
}

bool GameEngine::OnUserCreate()
{
	return true;
}

bool GameEngine::OnUserUpdate(float fElapsedTime)
{
	return true;
}

bool GameEngine::OnUserDestroy()
{
	return true;
}
