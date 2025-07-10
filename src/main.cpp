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

    enum class GamePhase { Playing, VictoryAnim, VictoryLine, VictoryPopup };
    GamePhase phase = GamePhase::Playing;

    WinInfo winInfo; // guardamos info de la victoria
    float victoryTimer = 0.0f;

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

                if (phase == GamePhase::Playing && board.isCellEmpty(row, col)) {
                    board.setCell(row, col, currentPlayer);
                    currentPlayer = (currentPlayer == CellState::X) ? CellState::O : CellState::X;

                    winInfo = board.checkWinner();

                    if (winInfo.winner != CellState::Empty) {
                        phase = GamePhase::VictoryAnim;
                        victoryTimer = 0.0f;
                    }
                    else if (board.isFull()) {
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                            "Game Over", "It's a draw!", state.window);
                        board.init();
                        currentPlayer = CellState::X;
                    }
                }

            }
        }

        float deltaTime = getDeltaTime();

        board.updateAnims(deltaTime);
        if (phase == GamePhase::VictoryAnim) {
            bool animating = false;
            for (int row = 0; row < 3; ++row)
                for (int col = 0; col < 3; ++col)
                    if (board.getCell(row,col).animation.active)
                        animating = true;

            if (!animating) {
                phase = GamePhase::VictoryLine;
                victoryTimer = 0.0f;
            }
        }

        if (phase == GamePhase::VictoryLine) {
            victoryTimer += deltaTime;
            if (victoryTimer >= 0.8f) { // tiempo para que se vea la línea antes del popup
                phase = GamePhase::VictoryPopup;
            }
        }

        if (phase == GamePhase::VictoryPopup) {
            std::string winnerMsg = "We have a winner: ";
            winnerMsg += (winInfo.winner == CellState::X) ? "Player 1 - X" : "Player 2 - O";

            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                "Game Over", winnerMsg.c_str(), state.window);

            board.init();
            currentPlayer = CellState::X;
            phase = GamePhase::Playing;
        }

        drawBoard(state, board);

        if (phase == GamePhase::VictoryLine || phase == GamePhase::VictoryPopup)
            drawWinLine(state, winInfo);

        SDL_RenderPresent(state.renderer);

        SDL_Delay(16);
    }

    cleanup(state);
    return 0;
}
