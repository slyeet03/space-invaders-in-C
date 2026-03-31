#include "../includes/enemy.h"
#include "../includes/game.h"
#include "../includes/main.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool hit_edge;

void enemies_new(Game *g) {
  g->enemy_alive_count = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      g->enemies[i][j].alive = true;
      g->enemy_alive_count++;

      int x = START_X + j * (g->enemies[i][j].rect.w + ENEMY_SPACING);
      int y = START_Y + i * (g->enemies[i][j].rect.h + ENEMY_SPACING);

      g->enemies[i][j].rect.x = x;
      g->enemies[i][j].rect.y = y;

      g->enemies[i][j].speed = 1.5f;
    }
  }
}

void enemies_update(Game *g) {
  hit_edge = false;

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (g->enemies[i][j].alive) {
        if (g->enemy_alive_count <= 16) {
          g->enemies[i][j].speed = 2.0f;
        }
        if (g->enemy_alive_count <= 8) {
          g->enemies[i][j].speed = 2.5f;
        }
        int right_boundary = g->enemies[i][j].rect.x + g->enemies[i][j].rect.w;
        int left_boundary = g->enemies[i][j].rect.x;
        if (right_boundary >= (float)WINDOW_WIDTH) {
          hit_edge = true;
        }
        if (left_boundary <= 0.0) {
          hit_edge = true;
        }
      }
    }
  }
  if (hit_edge) {
    g->enemy_direction = -(g->enemy_direction);
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        g->enemies[i][j].rect.y += g->enemies[i][j].speed * 5.0;
      }
    }
  }
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      g->enemies[i][j].rect.x += g->enemies[i][j].speed * g->enemy_direction;
    }
  }
}

bool enemies_load(Game *g) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (g->enemies[i][j].alive) {
        SDL_Surface *surface;
        if (i == 0) {
          surface = IMG_Load("../assets/images/red.png");
          if (!surface) {
            fprintf(stderr, "Error rendering enemy: %s\n", SDL_GetError());
            return false;
          }
        } else if (i == 1) {
          surface = IMG_Load("../assets/images/yellow.png");
          if (!surface) {
            fprintf(stderr, "Error rendering enemy: %s\n", SDL_GetError());
            return false;
          }
        } else {
          surface = IMG_Load("../assets/images/green.png");
          if (!surface) {
            fprintf(stderr, "Error rendering enemy: %s\n", SDL_GetError());
            return false;
          }
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
  }
  return true;
}

void enemies_render(Game *g, SDL_Renderer *r) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (g->enemies[i][j].alive) {
        SDL_RenderTexture(r, g->enemies[i][j].texture, NULL,
                          &g->enemies[i][j].rect);
      }
    }
  }
}
