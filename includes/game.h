#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} Game;

void run(Game *g);

#endif
