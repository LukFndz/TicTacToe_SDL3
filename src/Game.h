#pragma once
#include "SDL3/SDL.h"

enum class CellState { Empty, X, O };

struct Board
{
    CellState cells[3][3];

    void init()
    {
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
                cells[row][col] = CellState::Empty;
    }

    bool isCellEmpty(int row, int col)
    {
        return cells[row][col] == CellState::Empty;
    }

    void setCell(int row, int col, CellState state)
    {
        cells[row][col] = state;
    }
};
