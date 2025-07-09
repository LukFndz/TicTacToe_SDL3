#include "Renderer.h"
#include "Game.h"

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
            }
        }

        drawBoard(state, board);
        SDL_Delay(16); // 
    }

    cleanup(state);
    return 0;
}
