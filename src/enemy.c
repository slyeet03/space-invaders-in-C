#include "../includes/enemy.h"
#include "../includes/game.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void enemies_new(Game *g) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      g->enemies[i][j].alive = true;

      int x = START_X + j * (g->enemies[i][j].rect.w + ENEMY_SPACING);
      int y = START_Y + i * (g->enemies[i][j].rect.h + ENEMY_SPACING);

      g->enemies[i][j].rect.x = x;
      g->enemies[i][j].rect.y = y;
    }
  }
}

bool enemies_load(Game *g) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      SDL_Surface *surface = IMG_Load("../assets/images/red.png");
      if (!surface) {
        fprintf(stderr, "Error rendering enemy: %s\n", SDL_GetError());
        return false;
      }

      g->enemies[i][j].rect.w = (float)surface->w;
      g->enemies[i][j].rect.h = (float)surface->h;

      g->enemies[i][j].texture =
          SDL_CreateTextureFromSurface(g->renderer, surface);
      SDL_DestroySurface(surface);
      surface = NULL;
      if (!g->enemies[i][j].texture) {
        fprintf(stderr, "Error creating texture from surface: %s\n",
                SDL_GetError());
        return false;
      }
    }
  }
  return true;
}

void enemies_render(Game *g, SDL_Renderer *r) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      SDL_RenderTexture(r, g->enemies[i][j].texture, NULL,
                        &g->enemies[i][j].rect);
    }
  }
}
