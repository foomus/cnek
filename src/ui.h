#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "wrapper/vartypes.h"

#define SCORE_COLOR    \
  (SDL_Color) {        \
    225, 225, 225, 255 \
  }
#define GAME_OVER_COLOR \
  (SDL_Color) {         \
    200, 0, 0, 255      \
  }

SDL_Texture* updateScore(u16 score, TTF_Font* font, SDL_Rect* rect, SDL_Renderer* renderer);

void gameOver(TTF_Font* font, SDL_Renderer* renderer, u16 windowsWidth, u16 windowHeight);