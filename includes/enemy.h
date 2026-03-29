#ifndef ENEMY_H
#define ENEMY_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ENEMY_SPACING 10

typedef struct Enemy {
  SDL_FRect rect;
  bool alive;
} Enemy;

#endif
