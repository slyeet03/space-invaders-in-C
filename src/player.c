#include "../includes/player.h"
#include "../includes/game.h"
#include "../includes/main.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool player_new(Player **p) {
  *p = calloc(1, sizeof(Player));
  if (!(*p)) {
    return false;
  }

  (*p)->texture = NULL;

  // temp data
  (*p)->rect.w = 64;
  (*p)->rect.h = 64;

  // start near bottom center
  (*p)->rect.x = (WINDOW_WIDTH / 2.0f) - ((*p)->rect.w / 2.0f);
  (*p)->rect.y = WINDOW_HEIGHT - 80;

  (*p)->displacement = 45;

  (*p)->move_left = false;
  (*p)->move_right = false;

  return true;
}

bool player_load(Player *p, Game *g) {
  SDL_Surface *surface = IMG_Load("../assets/images/player.png");
  if (!surface) {
    fprintf(stderr, "Error rendering player: %s\n", SDL_GetError());
    return false;
  }

  p->rect.w = (float)surface->w;
  p->rect.h = (float)surface->h;

  p->texture = SDL_CreateTextureFromSurface(g->renderer, surface);
  SDL_DestroySurface(surface);
  surface = NULL;
  if (!p->texture) {
    fprintf(stderr, "Error creating texture from surface: %s\n",
            SDL_GetError());
    return false;
  }

  return true;
}

void player_update(Player *p) {
  if (p->move_right) {
    int boundary = (p->rect.x + (p->rect.w / 2)) + p->displacement;
    if (boundary <= WINDOW_WIDTH) {
      p->rect.x += p->displacement;
    }
    p->move_right = false;
  }
  if (p->move_left) {
    int boundary = p->rect.x - (p->rect.w / 2);
    if (boundary >= 0) {
      p->rect.x -= p->displacement;
    }
    p->move_left = false;
  }
}

void player_render(Player *p, SDL_Renderer *r) {
  SDL_RenderTexture(r, p->texture, NULL, &p->rect);
}

void player_free(Player *p) {
  if (!p) {
    return;
  }

  if (p->texture) {
    SDL_DestroyTexture(p->texture);
  }

  free(p);
}
