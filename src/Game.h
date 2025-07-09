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

    CellState checkWinner()
	{		// Check rows and columns
		for (int i = 0; i < 3; ++i) {
			if (cells[i][0] != CellState::Empty && cells[i][0] == cells[i][1] && cells[i][1] == cells[i][2])
				return cells[i][0];
			if (cells[0][i] != CellState::Empty && cells[0][i] == cells[1][i] && cells[1][i] == cells[2][i])
				return cells[0][i];
		}

		// Check diagonals
		if (cells[0][0] != CellState::Empty && cells[0][0] == cells[1][1] && cells[1][1] == cells[2][2])
			return cells[0][0];
		if (cells[0][2] != CellState::Empty && cells[0][2] == cells[1][1] && cells[1][1] == cells[2][0])
			return cells[0][2];

		return CellState::Empty; // No winner   
    }

    bool isFull()
	{
		for (int row = 0; row < 3; ++row)
			for (int col = 0; col < 3; ++col)
				if (cells[row][col] == CellState::Empty)
					return false;
		return true;

    }

    void setCell(int row, int col, CellState state)
    {
        cells[row][col] = state;
    }
};
