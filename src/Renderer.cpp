#include "Renderer.h"
#include <iostream>

// Initialize SDL and create window + renderer
bool initSDL(SDLState& state, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize!\n";
        return false;
    }

    state.window = SDL_CreateWindow("Tic-Tac-Toe", width, height, 0);
    if (!state.window) {
        std::cerr << "Window could not be created!\n";
        return false;
    }

    state.renderer = SDL_CreateRenderer(state.window, nullptr);
    if (!state.renderer) {
        std::cerr << "Renderer could not be created!\n";
        return false;
    }

    return true;
}

// Load all textures once
void loadTextures(SDLState& state)
{
    state.backgroundTex = IMG_LoadTexture(state.renderer, "assets/background.png");
    state.starTex = IMG_LoadTexture(state.renderer, "assets/star.png");
    state.circleTex = IMG_LoadTexture(state.renderer, "assets/circle.png");

    SDL_SetTextureScaleMode(state.backgroundTex, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureScaleMode(state.starTex, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureScaleMode(state.circleTex, SDL_SCALEMODE_NEAREST);
}

// Draw the board and background
void drawBoard(SDLState& state, const Board& board)
{
    int winW, winH;
    SDL_GetWindowSize(state.window, &winW, &winH);

    SDL_FRect bgRect = { 0, 0, winW, winH };

    SDL_RenderClear(state.renderer);
    SDL_RenderTexture(state.renderer, state.backgroundTex, nullptr, &bgRect);

    float cellW = winW / 3.0f;
    float cellH = winH / 3.0f;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {

            const Cell& cell = board.cells[row][col];

            if (cell.state == CellState::Empty)
                continue;

            const CellAnimation& anim = cell.animation;
            float scale = anim.active ? anim.scale : 1.0f;
            float alpha = anim.active ? anim.alpha : 1.0f;

            SDL_Texture* tex = (cell.state == CellState::X) ? state.starTex : state.circleTex;

            // Calcular tamaño
            SDL_FRect dest = {
                col * cellW + cellW * (0.5f - 0.25f * scale),
                row * cellH + cellH * (0.5f - 0.25f * scale),
                cellW * 0.5f * scale,
                cellH * 0.5f * scale
            };

            SDL_SetTextureAlphaMod(tex, static_cast<Uint8>(255 * alpha));
            SDL_RenderTexture(state.renderer, tex, nullptr, &dest);
            SDL_SetTextureAlphaMod(tex, 255); // Reset alpha
        }
    }

    SDL_RenderPresent(state.renderer);
}

// Free all resources
void cleanup(SDLState& state)
{
    SDL_DestroyTexture(state.backgroundTex);
    SDL_DestroyTexture(state.starTex);
    SDL_DestroyTexture(state.circleTex);
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}
