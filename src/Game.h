#pragma once
#include "SDL3/SDL.h"
#include "Animations.h"
#include "Utils.h"

enum CellState { Empty, X, O };

struct Cell {
	CellState state = CellState::Empty;
	CellAnimation animation;
};

struct Board
{
	Cell cells[3][3];

    void init()
    {
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
                cells[row][col].state = CellState::Empty;
    }

	void updateAnims(float deltaTime)
	{
		for (int row = 0; row < 3; ++row)
			for (int col = 0; col < 3; ++col)
				cells[row][col].animation.update(deltaTime);
	}

    bool isCellEmpty(int row, int col)
    {
        return cells[row][col].state == CellState::Empty;
    }

    CellState checkWinner()
	{		// Check rows and columns
		for (int i = 0; i < 3; ++i) {
			if (cells[i][0].state != CellState::Empty && cells[i][0].state == cells[i][1].state && cells[i][1].state == cells[i][2].state)
				return cells[i][0].state;
			if (cells[0][i].state != CellState::Empty && cells[0][i].state == cells[1][i].state && cells[1][i].state == cells[2][i].state)
				return cells[0][i].state;
		}

		// Check diagonals
		if (cells[0][0].state != CellState::Empty && cells[0][0].state == cells[1][1].state && cells[1][1].state == cells[2][2].state)
			return cells[0][0].state;
		if (cells[0][2].state != CellState::Empty && cells[0][2].state == cells[1][1].state && cells[1][1].state == cells[2][0].state)
			return cells[0][2].state;

		return CellState::Empty; // No winner   
    }

    bool isFull()
	{
		for (int row = 0; row < 3; ++row)
			for (int col = 0; col < 3; ++col)
				if (cells[row][col].state == CellState::Empty)
					return false;
		return true;
    }

    void setCell(int row, int col, CellState state)
    {
        cells[row][col].state = state;
		cells[row][col].animation.start();
    }
};
