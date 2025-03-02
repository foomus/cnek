#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "apple.h"
#include "snek.h"
#include "ui.h"
// #include "stringStorage.h"
#include "wrapper/AssetControls.h"
#include "wrapper/LinkedList.h"
#include "wrapper/SDL_Controls.h"
#include "wrapper/errHandler.h"
#include "wrapper/timer.h"
#include "wrapper/vartypes.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define GRID_CELL_SIZE 25
#define MAX_FPS 64
#define UPDATE_RATE 4  // Was set to 8 originally

static SDL_Window* window;
static SDL_Renderer* renderer;

static SDL_Color snekColor = {0, 200, 0, 255};
static SDL_Color appleColor = {255, 0, 0, 255};

static SDL_Texture* scoreTexture;

static TTF_Font* font;
static Mix_Chunk *rotateSound, *appleSound, *hitSound;

void init() {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  TTF_Init();
  // IMG_Init(IMG_INIT_PNG);
  if (Mix_OpenAudio(44100, AUDIO_F32SYS, 2, 2048) < 0) {
    catchError(false, __FILE__);
    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0) {
      catchError(false, __FILE__);
    }
  }
  Mix_Volume(-1, 32);

  window = SDL_CreateWindow("Cnek", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                            WINDOW_HEIGHT, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (window == NULL || renderer == NULL) {
    catchError(true, __FILE__);
  }

  srand(time(NULL));
}

void loadAssets() {
  font = TTF_OpenFont("./assets/fonts/PressStart.ttf", 32);
  if (font == NULL) {
    catchError(false, __FILE__);
  }
  rotateSound = loadSound("./assets/sounds/rotate.wav");
  appleSound = loadSound("./assets/sounds/apple.wav");
  hitSound = loadSound("./assets/sounds/hit.wav");
}

int main(int argc, char** arg) {
  bool quit = false;
  u8 cooldown = 0;
  u16 score = 0;
  int scoreTextW, scoreTextH;

  node_rect* neck = NULL;
  Snek snek = {GRID_CELL_SIZE * 2, 0, 0, 0, 2, 2, RIGHT, snekColor, neck};
  snek.neck =
      pushNodeToHead_rect(snek.neck, (SDL_Rect){GRID_CELL_SIZE, 0, GRID_CELL_SIZE, GRID_CELL_SIZE});
  snek.neck = pushNodeToHead_rect(snek.neck, (SDL_Rect){0, 0, GRID_CELL_SIZE, GRID_CELL_SIZE});
  SDL_Rect apple;
  SDL_Rect scoreRect;

  SDL_Event e;

  init();

  loadAssets();

  scoreTexture = renderText("0", font, SCORE_COLOR, renderer);
  TTF_SizeText(font, "0", &scoreTextW, &scoreTextH);
  scoreRect = (SDL_Rect){15, 15, scoreTextW, scoreTextH};

  apple = generateApple(WINDOW_WIDTH, WINDOW_HEIGHT, GRID_CELL_SIZE, snek);
  while (!quit) {
    SDL_PollEvent(&e);
    switch (e.type) {
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
          case SDLK_LEFT:
            if (snek.direction != RIGHT) {
              setSnekDirection(&snek, LEFT, GRID_CELL_SIZE);
              Mix_PlayChannel(-1, rotateSound, 0);
            }
            break;
          case SDLK_RIGHT:
            if (snek.direction != LEFT) {
              setSnekDirection(&snek, RIGHT, GRID_CELL_SIZE);
              Mix_PlayChannel(-1, rotateSound, 0);
            }
            break;
          case SDLK_UP:
            if (snek.direction != DOWN) {
              setSnekDirection(&snek, UP, GRID_CELL_SIZE);
              Mix_PlayChannel(-1, rotateSound, 0);
            }
            break;
          case SDLK_DOWN:
            if (snek.direction != UP) {
              setSnekDirection(&snek, DOWN, GRID_CELL_SIZE);
              Mix_PlayChannel(-1, rotateSound, 0);
            }
            break;
          default:
            break;
        }
        break;
      case SDL_QUIT:
        quit = true;
        break;
      default:
        break;
    }

    if (cooldown == UPDATE_RATE) {
      // Detect if snek left the window borders
      if (snek.posX < 0 || snek.posX > WINDOW_WIDTH - GRID_CELL_SIZE || snek.posY < 0 ||
          snek.posY > WINDOW_HEIGHT - GRID_CELL_SIZE) {
        Mix_PlayChannel(-1, hitSound, 0);
        gameOver(font, renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
      }
      if (checkSnekSelfCollision(snek)) {
        Mix_PlayChannel(-1, hitSound, 0);
        gameOver(font, renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
      }
      // Detect is snek moving
      if (snek.velX != 0 || snek.velY != 0) {
        snek.neck = pushNodeToHead_rect(
            snek.neck, (SDL_Rect){snek.posX, snek.posY, GRID_CELL_SIZE, GRID_CELL_SIZE});
        snek.currentLen++;
      }
      // Detect is snek eating apple
      if (snek.posX == apple.x && snek.posY == apple.y) {
        apple = generateApple(WINDOW_WIDTH, WINDOW_HEIGHT, GRID_CELL_SIZE, snek);
        snek.availableLen++;

        score++;
        scoreTexture = updateScore(score, font, &scoreRect, renderer);
        Mix_PlayChannel(-1, appleSound, 0);
      }
      // Cut last position entry if snek is too short to hold it
      if (snek.currentLen > snek.availableLen) {
        popNodeFromTail_rect(snek.neck, snek.currentLen);
        snek.currentLen--;
      }

      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);  // Render score

      renderApple(apple, renderer, appleColor);
      moveSnek(&snek, renderer, GRID_CELL_SIZE);

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      cooldown = 0;
    } else {
      cooldown++;
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / MAX_FPS);
  }

  // TTF_CloseFont(font);
  SDL_Shutdown();
  exit(EXIT_SUCCESS);
}