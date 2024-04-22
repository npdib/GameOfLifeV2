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
#include "Cell.h"
#include "GameEngine.h"

#include <cstdio>

SetupScreen::SetupScreen(GameEngine* gameEngine, CellBoard cells)
	: mGameEngine(gameEngine)
	, mClickable(true)
	, mRowMinus(mGameEngine, Button::Config{ 10, 10, "-", {10, 145}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mRowPlus(mGameEngine, Button::Config{ 10, 10, "+", {50, 145}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mColumnMinus(mGameEngine, Button::Config{10, 10, "-", {100, 145}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN})
	, mColumnPlus(mGameEngine, Button::Config{ 10, 10, "+", {140, 145}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mGo(mGameEngine, Button::Config{ 30, 10, "Go", {65, 145}, {7, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN})
	, mRows(10)
	, mColumns(10)
	, mCells(std::move(cells))
{
	mButtons.push_back(&mRowPlus);
	mButtons.push_back(&mRowMinus);
	mButtons.push_back(&mColumnPlus);
	mButtons.push_back(&mColumnMinus);
	mButtons.push_back(&mGo);

	mCells.resize(mRows);

	for (auto& cellRow : mCells) // initialise cellboard
	{
		cellRow.resize(mColumns, Cell());
	}
}

void SetupScreen::update()
{
	for (const auto& button : mButtons)
	{
		button->UpdateActive();
	}

	if (mGameEngine->GetMouse(olc::Mouse::LEFT).bPressed || mGameEngine->GetMouse(olc::Mouse::LEFT).bHeld)
	{
		if (mClickable)
		{
			if (mRowMinus.GetActive())
			{
				if (mRows > 1)
				{
					RemoveRow();
					mClickable = false;
				}
			}

			if (mRowPlus.GetActive())
			{
				if (mRows < 30)
				{
					AddRow();
					mClickable = false;
				}
			}

			if (mColumnMinus.GetActive())
			{
				if (mColumns > 1)
				{
					RemoveColumn();
					mClickable = false;
				}
			}

			if (mColumnPlus.GetActive())
			{
				if (mColumns < 30)
				{
					AddColumn();
					mClickable = false;
				}
			}

			if (mGo.GetActive())
			{
				mGameEngine->ChangeState(GameEngine::State::Running);
				mClickable = false;
			}
		}
	}

	if (mGameEngine->GetMouse(olc::Mouse::LEFT).bReleased)
	{
		mClickable = true;
	}
}

void SetupScreen::render()
{
	mGameEngine->DrawString({ (mGameEngine->ScreenWidth() - 40) / 2, 5 }, "Setup");
	mGameEngine->DrawString({ 113, 147 }, "Row");
	mGameEngine->DrawString({ 24, 147 }, "Col");

	for (const auto& button : mButtons)
	{
		button->draw();
	}

	static char buff[32];

	int len = std::snprintf(buff, 32, "%d:\t%llu", mRows, mCells.size());

	mGameEngine->DrawString({ 25, 50 }, buff);


	len = std::snprintf(buff, 32, "%d:\t%llu", mColumns, mCells.begin()->size());

	mGameEngine->DrawString({ 25, 75 }, buff);

}

void SetupScreen::RemoveRow()
{
	mCells.erase(mCells.end() - 1);
	--mRows;
}

void SetupScreen::AddRow()
{
	std::vector<Cell> tempRow;
	tempRow.resize(mColumns);
	for (auto& cell : tempRow) { cell = Cell();	}

	mCells.push_back(tempRow);

	++mRows;
}

void SetupScreen::RemoveColumn()
{
	for (auto& row : mCells)
	{
		row.erase(row.end() - 1);
	}
	--mColumns;
}

void SetupScreen::AddColumn()
{
	for (auto& row : mCells)
	{
		row.push_back(Cell());
	}
	++mColumns;
}
