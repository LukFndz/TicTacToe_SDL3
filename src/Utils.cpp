#include "Utils.h"

float getDeltaTime()
{
    Uint64 now = SDL_GetTicks();
    static Uint64 last = now;
    float deltaTime = (now - last) / 1000.0f;
    last = now;
    return deltaTime;
}