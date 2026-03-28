#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Player {
  SDL_Texture *texture;
  SDL_FRect rect;
  bool move_left;
  bool move_right;
  int displacement;
} Player;

typedef struct Game Game;

bool player_new(Player **p);
bool player_load(Player *p, Game *g);
void player_render(Player *p, SDL_Renderer *r);
void player_update(Player *p);
void player_free(Player *p);

#endif
