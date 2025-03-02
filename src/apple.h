#pragma once

#include <SDL2/SDL.h>

#include "snek.h"
#include "wrapper/vartypes.h"

SDL_Rect generateApple(s16 windowWidth, s16 windowHeight, s8 gridCellSize, Snek snek);

void renderApple(SDL_Rect apple, SDL_Renderer* renderer, SDL_Color color);