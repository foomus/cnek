#pragma once

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "wrapper/LinkedList.h"
#include "wrapper/vartypes.h"

enum Direction {
  LEFT,
  RIGHT,
  UP,
  DOWN,
};

typedef struct {
  s16 posX, posY;
  s8 velX, velY;
  u16 currentLen, availableLen;
  enum Direction direction;
  SDL_Color color;
  node_rect* neck;
} Snek;

// typedef struct {
//   s8 velX, velY;
// } Move;

void setSnekDirection(Snek* snek, enum Direction direction, u8 speed);

void moveSnek(Snek* snek, SDL_Renderer* renderer, u8 gridCellSize);

bool checkSnekSelfCollision(Snek snek);

// node_RECT growSnek(Snek* snek, Move move, u8 gridCellSize);