#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ui.h"
#include "wrapper/AssetControls.h"
#include "wrapper/SDL_Controls.h"
#include "wrapper/vartypes.h"

SDL_Texture* updateScore(u16 score, TTF_Font* font, SDL_Rect* rect, SDL_Renderer* renderer) {
  int scoreTextW, scoreTextH;
  char scoreStr[5] = "\0";
  sprintf(scoreStr, "%d", score);

  SDL_Texture* scoreTexture = renderText(scoreStr, font, SCORE_COLOR, renderer);
  TTF_SizeText(font, scoreStr, &scoreTextW, &scoreTextH);

  *rect = (SDL_Rect){15, 15, scoreTextW, scoreTextH};

  return scoreTexture;
}

void gameOver(TTF_Font* font, SDL_Renderer* renderer, u16 windowsWidth, u16 windowHeight) {
  int textW, textH;
  SDL_Texture* gameOverTexture = renderText("GAME OVER", font, GAME_OVER_COLOR, renderer);
  TTF_SizeText(font, "GAME OVER", &textW, &textH);
  SDL_Rect gameOverRect = {(windowsWidth - textW) / 2, (windowHeight - textH) / 2, textW, textH};
  SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);

  SDL_RenderPresent(renderer);
  SDL_Delay(2000);
  SDL_Shutdown();
  exit(0);
}