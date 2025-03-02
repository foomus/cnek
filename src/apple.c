#include <stdbool.h>

#include <SDL2/SDL.h>

#include "snek.h"
#include "wrapper/LinkedList.h"
#include "wrapper/vartypes.h"

SDL_Rect generateApple(s16 windowWidth, s16 windowHeight, s8 gridCellSize, Snek snek) {
  // u8 generated = 0;
  bool success = true;
  SDL_Rect apple;
  do {
    success = true;
    apple = (SDL_Rect){(rand() % windowWidth / gridCellSize) * gridCellSize,
                       (rand() % windowHeight / gridCellSize) * gridCellSize, gridCellSize,
                       gridCellSize};

    node_rect* bodyPart = snek.neck;
    if (snek.posX == apple.x && snek.posY == apple.y) {
      success = false;
    }
    while (bodyPart != NULL) {
      if (bodyPart->rect.x == apple.x && bodyPart->rect.y == apple.y) {
        success = false;
      }
      bodyPart = bodyPart->pointer;
    }
    // generated++;
  } while (!success);
  return apple;
}

void renderApple(SDL_Rect apple, SDL_Renderer* renderer, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &apple);
}