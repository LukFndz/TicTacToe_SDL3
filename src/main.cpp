#include "Renderer.h"
#include "Game.h"
#include "Animations.h"
#include <string>

int main(int argc, char* argv[])
{
    SDLState state;
    Board board;
    board.init();
    CellState currentPlayer = CellState::X;

    if (!initSDL(state, 800, 600)) {
        return 1;
    }

    loadTextures(state);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                float x, y;
                SDL_GetMouseState(&x, &y);

                int winW, winH;
                SDL_GetWindowSize(state.window, &winW, &winH);

                int col = x / (winW / 3);
                int row = y / (winH / 3);

                if (board.isCellEmpty(row, col)) {
                    board.setCell(row, col, currentPlayer);
                    currentPlayer = (currentPlayer == CellState::X) ? CellState::O : CellState::X;
                }


				CellState winner = board.checkWinner();
                std::string winnerMsg = "We have a winner: ";
                winnerMsg += (winner == CellState::X) ? "Player 1 - X" : "Player 2 - O";

				if (winner != CellState::Empty) {
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                        "Game Over",
                        winnerMsg.c_str(),
                        state.window);
                    board.init();
                    currentPlayer = CellState::X; // Reset to Player X's turn
                }
                else {
                    if (board.isFull())
                    {
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                            "Game Over",
                            "It's a draw!",
                            state.window);

                        board.init();
						currentPlayer = CellState::X; // Reset to Player X's turn
                    }
                }

            }
        }

        float deltaTime = getDeltaTime();

        board.updateAnims(deltaTime);

        drawBoard(state, board);
        SDL_Delay(16);
    }

    cleanup(state);
    return 0;
}
