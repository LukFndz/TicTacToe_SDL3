#pragma once
#include "SDL3/SDL.h"
#include "Animations.h"
#include "Utils.h"
#include "Renderer.h"

enum CellState { Empty, X, O };

struct Cell {
	CellState state = CellState::Empty;
	CellAnimation animation;
};

enum class WinType { None, Row, Column, DiagonalMain, DiagonalAnti };

struct WinInfo {
	CellState winner = CellState::Empty;
	WinType type = WinType::None;
	int index = -1; // Para filas o columnas
};

class Board
{
private:
	Cell cells[3][3];

public:
    const Cell& getCell(int row, int col) const {
        return cells[row][col];
    }

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

    WinInfo checkWinner()
    {
        for (int i = 0; i < 3; ++i) {
            if (cells[i][0].state != CellState::Empty &&
                cells[i][0].state == cells[i][1].state &&
                cells[i][1].state == cells[i][2].state)
                return { cells[i][0].state, WinType::Row, i };

            if (cells[0][i].state != CellState::Empty &&
                cells[0][i].state == cells[1][i].state &&
                cells[1][i].state == cells[2][i].state)
                return { cells[0][i].state, WinType::Column, i };
        }

        if (cells[0][0].state != CellState::Empty &&
            cells[0][0].state == cells[1][1].state &&
            cells[1][1].state == cells[2][2].state)
            return { cells[0][0].state, WinType::DiagonalMain, -1 };

        if (cells[0][2].state != CellState::Empty &&
            cells[0][2].state == cells[1][1].state &&
            cells[1][1].state == cells[2][0].state)
            return { cells[0][2].state, WinType::DiagonalAnti, -1 };

        return {};
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
