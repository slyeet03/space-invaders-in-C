#ifndef SCORE_H
#define SCORE_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  TTF_Font *font;
  SDL_Texture *image;
  SDL_FRect rect;
  int value;
} Score;

struct Game;

bool score_new(struct Game *g);
bool score_load(struct Game *g);

#endif
