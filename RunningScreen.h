// RunningScreen.h
//   
// (c) eg technology ltd, 2024. All rights reserved. 
//  
// This software is the property of eg technology ltd. and may not be copied or 
// reproduced otherwise than on to a single hard disk for backup or archival 
// purposes. The source code is confidential information and must not be disclosed to third 
// parties or used without the express written permission of eg technology ltd.

#pragma once
#include <vector>
#include "IScreen.h"
#include "Cell.h"
#include <chrono>

class GameEngine;
typedef std::vector<std::vector<Cell>> CellBoard;

class RunningScreen : public IScreen
{
public:
    RunningScreen(GameEngine* gameEngine);

    void update() override;
    void render() override;

    void UpdateBoard(CellBoard board) { mCells = std::move(board); }

private:
    static constexpr uint8_t kBoardWidth = 140;
    static constexpr uint8_t kBoardHeight = 140;

    GameEngine* mGameEngine;
    CellBoard mCells;

    bool mRunning;

    std::chrono::time_point<std::chrono::system_clock> mTimer;
    

    void DrawBoard() const;
    void Tick();

    static uint8_t GetNumOfNeighbours(const CellBoard& board, uint8_t col, uint8_t row);
};