#pragma once
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "Game.h"

struct SDLState
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* backgroundTex = nullptr;
    SDL_Texture* starTex = nullptr;
    SDL_Texture* circleTex = nullptr;
};

void drawWinLine(SDLState& state, const WinInfo& winInfo);
bool initSDL(SDLState& state, int width, int height);
void loadTextures(SDLState& state);
void drawBoard(SDLState& state, const Board& board);
void cleanup(SDLState& state);
