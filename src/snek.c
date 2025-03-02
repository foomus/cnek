#include <SDL2/SDL.h>

#include "snek.h"
#include "wrapper/LinkedList.h"
#include "wrapper/vartypes.h"

enum Direction direction = RIGHT;

void setSnekDirection(Snek* snek, enum Direction direction, u8 speed) {
  snek->velX = 0, snek->velY = 0;
  switch (direction) {
    case LEFT:
      snek->velX = -speed;
      snek->direction = LEFT;
      break;
    case RIGHT:
      snek->velX = speed;
      snek->direction = RIGHT;
      break;
    case UP:
      snek->velY = -speed;
      snek->direction = UP;
      break;
    case DOWN:
      snek->velY = speed;
      snek->direction = DOWN;
      break;
    default:
      break;
  }
}

void moveSnek(Snek* snek, SDL_Renderer* renderer, u8 gridCellSize) {
  snek->posX += snek->velX;
  snek->posY += snek->velY;

  SDL_SetRenderDrawColor(renderer, snek->color.r, snek->color.g, snek->color.b, snek->color.a);

  SDL_Rect head = {snek->posX, snek->posY, gridCellSize, gridCellSize};
  SDL_RenderFillRect(renderer, &head);

  node_rect* bodyPart = snek->neck;
  while (bodyPart != NULL) {
    SDL_RenderFillRect(renderer, &bodyPart->rect);
    bodyPart = bodyPart->pointer;
  }
}

bool checkSnekSelfCollision(Snek snek) {
  node_rect* bodyPart = snek.neck;
  while (bodyPart != NULL) {
    if (bodyPart->rect.x == snek.posX && bodyPart->rect.y == snek.posY) {
      return true;
    }
    bodyPart = bodyPart->pointer;
  }
  return false;
}