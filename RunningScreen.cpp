// RunningScreen.cpp
//   
// (c) eg technology ltd, 2024. All rights reserved. 
//  
// This software is the property of eg technology ltd. and may not be copied or 
// reproduced otherwise than on to a single hard disk for backup or archival 
// purposes. The source code is confidential information and must not be disclosed to third 
// parties or used without the express written permission of eg technology ltd.

#include "RunningScreen.h"
#include "GameEngine.h"

#include <algorithm>
#include <cstdint>

using std::chrono::system_clock;
using namespace std::chrono;

RunningScreen::RunningScreen(GameEngine* gameEngine)
	: mGameEngine(gameEngine)
	, mRunning(false)
	, mClickable(false)
	, mPausePlay(mGameEngine, Button::Config{ 40, 10, "Play", {60, 133}, {2, 1}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mBack(mGameEngine, Button::Config{ 20, 10, "<-", {5, 145}, {2, 2}, olc::WHITE, olc::RED, olc::DARK_GREEN })
	, mSteps(0)
{
	mButtons.push_back(&mPausePlay);
	mTimer = system_clock::now();
}

void RunningScreen::update()
{
	for (const auto& button : mButtons)
	{
		button->UpdateActive();
	}

	if (!mRunning)
	{
		mBack.UpdateActive();
	}


	if (mGameEngine->GetMouse(olc::Mouse::LEFT).bPressed || mGameEngine->GetMouse(olc::Mouse::LEFT).bHeld)
	{
		if (mClickable)
		{
			if (mPausePlay.GetActive())
			{
				mRunning = !mRunning;

				if (mRunning)
				{
					mPausePlay.ChangeText("Stop");
				}
				else
				{
					mPausePlay.ChangeText("Play");
				}

				mClickable = false;
			}

			if (mBack.GetActive())
			{
				mGameEngine->ChangeState(GameEngine::State::Setup);
				mClickable = false;
			}
		}
	}

	if (mGameEngine->GetMouse(olc::Mouse::LEFT).bReleased)
	{
		mClickable = true;
	}

	if (mRunning)
	{
		if (duration_cast<milliseconds>(system_clock::now() - mTimer) > 200ms)
		{
			Tick();
			mTimer = system_clock::now();
			++mSteps;
		}
	}
}

void RunningScreen::render()
{
	static char buff[32];
	snprintf(buff, 32, "Steps: %d", mSteps);
	mGameEngine->DrawString({ 60, 147 }, buff);

	for (const auto& button : mButtons)
	{
		button->draw();
	}

	if (!mRunning)
	{
		mBack.draw();
	}

	DrawBoard();
}

void RunningScreen::DrawBoard() const
{
	const uint8_t mColumns = mCells.begin()->size();
	const uint8_t mRows = mCells.size();

	const uint8_t cellSize = std::min(kBoardWidth / mColumns, kBoardHeight / mRows);

	uint8_t x = (mGameEngine->ScreenWidth() - kBoardWidth) / 2u;
	uint8_t y = (mGameEngine->ScreenHeight() - kBoardHeight) / 3u;
	const uint8_t xStart = x + ((mRows > mColumns) ? ((mRows - mColumns) * cellSize) / 2 : 0);
	y += ((mColumns > mRows) ? ((mColumns - mRows) * cellSize) / 2 : 0);


	for (auto& cellRow : mCells)
	{
		x = xStart;
		for (auto& cell : cellRow)
		{
			mGameEngine->FillRect(x, y, cellSize - 1, cellSize - 1, cell.GetState() ? olc::MAGENTA : olc::VERY_DARK_MAGENTA);
			x += cellSize;
		}
		y += cellSize;
	}
}

void RunningScreen::Tick()
{
	static CellBoard newBoard = mCells;

	for (int x = 0; x < mCells.begin()->size(); ++x)
	{
		for (int y = 0; y < mCells.size(); ++y)
		{
			if (mCells[y][x].GetState()) // alive
			{
				switch (GetNumOfNeighbours(mCells, x, y))
				{
				case 0:
				case 1:
					// dies from underpopulation
					newBoard[y][x].SetDead();
					break;
				case 2:
				case 3:
					// continues to next generation
					break;
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
					// dies from overpopulation
					newBoard[y][x].SetDead();
					break;
				default:
					break;
				}
			}
			else
			{
				if (GetNumOfNeighbours(mCells, x, y) == 3)
				{
					// alive from reproduction
					newBoard[y][x].SetAlive();
				}
			}
		}
	}

	mCells = newBoard;
}

uint8_t RunningScreen::GetNumOfNeighbours(const CellBoard& board, uint8_t col, uint8_t row)
{
	uint8_t numOfNeighbours = 0;

	for (int x = -1; x <= 1; ++x)
	{
		if (col + x < 0 || col + x >= board.begin()->size())
			continue;

		for (int y = -1; y <= 1; ++y)
		{
			if (row + y < 0 || row + y >= board.size())
				continue;

			if (x == 0 && y == 0)
				continue;

			if (board[row + y][col + x].GetState())
			{
				++numOfNeighbours;
			}
		}
	}

	return numOfNeighbours;
}
