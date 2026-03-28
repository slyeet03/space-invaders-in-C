#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "score.h"

typedef struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  Score *score;
  Player *player;
  bool is_running;
} Game;

bool new (Game **game);
void run(Game *g);
bool load_media(Game *g);
void update(Game *g);

#endif
