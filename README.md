# TicTacToe SDL3

Tic-Tac-Toe game built with **SDL3** and **SDL_image**. The project renders a textured board, handles mouse clicks to place pieces, and shows animations plus victory lines.

## What is this for?

This repository is a small example of how to:

- Initialize an SDL3 window and renderer.
- Draw background and piece textures.
- Handle mouse input and basic game logic.
- Display animations and game results.

## Requirements

- **SDL3**
- **SDL3_image**
- A C++ compiler (Visual Studio on Windows, or another SDL3-compatible toolchain).

Textures are loaded from the `assets/` folder:

- `assets/background.png`
- `assets/star.png`
- `assets/circle.png`

## How to run

### Windows (Visual Studio)

1. Install SDL3 and SDL3_image.
2. Open `TicTacToe_SDL.sln`.
3. Configure the SDL3 and SDL3_image include/lib paths in the project.
4. Build and run from Visual Studio.

### Other environments

If you use another IDE or toolchain, make sure to:

- Link against SDL3 and SDL3_image.
- Include the `src/` directory in your build.
- Keep the `assets/` folder available in the working directory when running.

## Game “API” overview

This project does not expose a network or HTTP API. The “API” here refers to the public functions and structures that coordinate gameplay and rendering.

### Board logic (`src/Game.h`)

- `Board::init()` clears all cells.
- `Board::setCell(row, col, state)` places a piece and triggers the cell animation.
- `Board::checkWinner()` returns a `WinInfo` with the winner and line type.
- `Board::isFull()` detects a draw.
- `Board::updateAnims(deltaTime)` advances per-cell animations.

### Rendering (`src/Renderer.h` / `src/Renderer.cpp`)

- `initSDL(...)` creates the window and renderer.
- `loadTextures(...)` loads the background and piece textures.
- `drawBoard(...)` renders the board and current pieces.
- `drawWinLine(...)` draws the green victory line.
- `cleanup(...)` releases SDL resources.

### Main loop (`src/main.cpp`)

- Handles SDL events (clicks and window close).
- Converts mouse position to board cell coordinates.
- Alternates the current player (X/O) after each move.
- Runs victory phases: piece animation → win line → popup.

## Gameplay flow

1. The player clicks an empty cell.
2. `X` or `O` is placed and animated.
3. The game checks for a winner or draw.
4. If there is a winner, the line and popup are shown, then the board resets.

## Repository structure

- `src/`: game logic, rendering, and utilities.
- `assets/`: board and piece images.
- `TicTacToe_SDL.sln`: Visual Studio solution.

## Notes

- The game assumes a 3x3 grid and scales sprites with the window.
- The victory message is shown with `SDL_ShowSimpleMessageBox`.
