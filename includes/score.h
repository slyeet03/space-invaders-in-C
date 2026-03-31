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

typedef struct Game Game;

bool score_new(Game *g);
bool score_load(Game *g);
void score_render(Game *g, SDL_Renderer *r);
void score_free(Game *g);
void score_update(Game *g);

#endif
