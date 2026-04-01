#ifndef ENEMY_H
#define ENEMY_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ENEMY_SPACING 70
#define START_X 120
#define START_Y 50

typedef struct Enemy {
  SDL_Texture *texture;
  SDL_FRect rect;
  bool alive;
  float speed;
  int health;
} Enemy;

typedef struct Game Game;

void enemies_new(Game *g);
bool enemies_load(Game *g);
void enemies_render(Game *g, SDL_Renderer *r);
void enemies_update(Game *g);

#endif
