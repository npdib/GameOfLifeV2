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

SetupScreen::SetupScreen(GameEngine* gameEngine)
	: mGameEngine(gameEngine)
	, mClickable(false)
	, mRowMinus(mGameEngine, Button::Config{ 10, 10, "-", {10, 133}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mRowPlus(mGameEngine, Button::Config{ 10, 10, "+", {50, 133}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mColumnMinus(mGameEngine, Button::Config{10, 10, "-", {100, 133}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN})
	, mColumnPlus(mGameEngine, Button::Config{ 10, 10, "+", {140, 133}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mGo(mGameEngine, Button::Config{ 30, 10, "Go", {65, 133}, {7, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mRandom(mGameEngine, Button::Config{ 10, 10, "R", {142, 60}, {1, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mClear(mGameEngine, Button::Config{ 10, 10, "C", {142, 80}, {1, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mBack(mGameEngine, Button::Config{ 20, 10, "<-", {5, 145}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN})
	, mRows(20)
	, mColumns(20)
	, mActiveCell(nullptr)
{
	mButtons.push_back(&mRowPlus);
	mButtons.push_back(&mRowMinus);
	mButtons.push_back(&mColumnPlus);
	mButtons.push_back(&mColumnMinus);
	mButtons.push_back(&mGo);
	mButtons.push_back(&mRandom);
	mButtons.push_back(&mClear);
	mButtons.push_back(&mBack);

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
			if (mActiveCell != nullptr)
			{
				mActiveCell->Toggle();
				mClickable = false;
			}

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

			if (mRandom.GetActive())
			{
				for (auto& row : mCells)
				{
					for (auto& cell : row)
					{
						if ((rand() % 2) == 1)
						{
							cell.SetAlive();
						}
						else
						{
							cell.SetDead();
						}
					}
				}
				mClickable = false;
			}

			if (mClear.GetActive())
			{
				ClearBoard();
				mClickable = false;
			}

			if (mBack.GetActive())
			{
				mGameEngine->ChangeState(GameEngine::State::Menu);
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
	mGameEngine->DrawString({ 113, 135 }, "Row");
	mGameEngine->DrawString({ 24, 135 }, "Col");

	for (const auto& button : mButtons)
	{
		button->draw();
	}

	DrawBoard();
}

void SetupScreen::ClearBoard()
{
	for (auto& cellRow : mCells)
	{
		for (auto& cell : cellRow)
		{
			cell.SetDead();
		}
	}
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

void SetupScreen::DrawBoard()
{
	const uint8_t cellSize = std::min(kBoardWidth / mColumns, kBoardHeight / mRows);

	uint8_t x = (mGameEngine->ScreenWidth() - kBoardWidth) / 2u;
	uint8_t y = (mGameEngine->ScreenHeight() - kBoardHeight) / 2u;
	const uint8_t xStart = x + ((mRows > mColumns) ? ((mRows - mColumns) * cellSize) / 2 : 0);
	y += ((mColumns > mRows) ? ((mColumns - mRows) * cellSize) / 2 : 0);

	mActiveCell = nullptr;

	for (auto& cellRow : mCells)
	{
		x = xStart;
		for (auto& cell : cellRow)
		{
			mGameEngine->FillRect(x, y , cellSize - 1, cellSize - 1, cell.GetState() ? olc::MAGENTA : olc::VERY_DARK_MAGENTA);

			const olc::vi2d mousePos = mGameEngine->GetMousePos();
			if (mousePos.x > x && mousePos.x < x + cellSize)
			{
				if (mousePos.y > y && mousePos.y < y + cellSize)
				{
					mGameEngine->DrawRect(x, y, cellSize - 2, cellSize - 2, olc::WHITE);
					mActiveCell = &cell;
				}				
			}

			x += cellSize;
		}
		y += cellSize;
	}
}
