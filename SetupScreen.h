// SetupScreen.h
//   
// (c) eg technology ltd, 2024. All rights reserved. 
//  
// This software is the property of eg technology ltd. and may not be copied or 
// reproduced otherwise than on to a single hard disk for backup or archival 
// purposes. The source code is confidential information and must not be disclosed to third 
// parties or used without the express written permission of eg technology ltd.

#pragma once
#include "IScreen.h"
#include "Button.h"
#include <vector>
#include "Cell.h"

class GameEngine;
typedef std::vector<std::vector<Cell>> CellBoard;

class SetupScreen : public IScreen
{
public:
	SetupScreen(GameEngine* gameEngine, CellBoard cells);

	void update() override;
	void render() override;

	CellBoard GetCellBoard() const { return mCells; }
private:
	GameEngine* mGameEngine;
	bool mClickable;

	Button mRowMinus;
	Button mRowPlus;
	Button mColumnMinus;
	Button mColumnPlus;
	Button mGo;

	uint8_t mRows;
	uint8_t mColumns;

	std::vector<Button*> mButtons;

	CellBoard mCells;

	void RemoveRow();
	void AddRow();
	void RemoveColumn();
	void AddColumn();

};

