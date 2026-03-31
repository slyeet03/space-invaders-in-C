#include "../includes/score.h"
#include "../includes/game.h"
#include "../includes/main.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool score_new(Game *g) {
  g->score = calloc(1, sizeof(Score)); // allocate the struct
  if (!g->score) {
    fprintf(stderr, "Error allocating score\n");
    return false;
  }

  g->score->font = TTF_OpenFont("../assets/fonts/FiraCode-Bold.ttf", FONT_SIZE);
  if (!g->score->font) {
    fprintf(stderr, "Error opening font: %s\n", SDL_GetError());
    return false;
  }

  g->score->value = 0;

  return true;
}

bool score_load(Game *g) {
  char scoreValue[20];
  sprintf(scoreValue, "%d", g->score->value);

  SDL_Surface *surface =
      TTF_RenderText_Blended(g->score->font, scoreValue, 0, RED_COLOR);
  if (!surface) {
    fprintf(stderr, "Error rendering score: %s\n", SDL_GetError());
    return false;
  }

  // getting the dimensions for the rectangle from the surface struct directly
  g->score->rect.w = (float)surface->w;
  g->score->rect.h = (float)surface->h;
  // changing x and y of the rectangle
  g->score->rect.x = 10;
  g->score->rect.y = 10;

  // converting the font surface to texture
  g->score->image = SDL_CreateTextureFromSurface(g->renderer, surface);
  SDL_DestroySurface(surface);
  surface = NULL;
  if (!g->score->image) {
    fprintf(stderr, "Error creating texture from surface: %s\n",
            SDL_GetError());
    return false;
  }
  // when scaling an image it try to not get that much blury
  if (!SDL_SetTextureScaleMode(g->score->image, SDL_SCALEMODE_NEAREST)) {
    fprintf(stderr, "Error setting texture scale mode: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

void score_update(Game *g) {
  char buf[32];
  snprintf(buf, sizeof(buf), "%d", g->score->value);

  if (g->score->image) {
    SDL_DestroyTexture(g->score->image);
    g->score->image = NULL;
  }

  SDL_Surface *surface =
      TTF_RenderText_Blended(g->score->font, buf, 0, RED_COLOR);
  if (!surface)
    return;

  g->score->rect.w = (float)surface->w;
  g->score->rect.h = (float)surface->h;
  g->score->image = SDL_CreateTextureFromSurface(g->renderer, surface);
  SDL_DestroySurface(surface);
}

void score_render(Game *g, SDL_Renderer *r) {
  SDL_RenderTexture(r, g->score->image, NULL, &g->score->rect);
}

void score_free(Game *g) {
  if (g->score) {
    if (g->score->image) {
      SDL_DestroyTexture(g->score->image);
      g->score->image = NULL;
    }
    if (g->score->font) {
      TTF_CloseFont(g->score->font);
      g->score->font = NULL;
    }
    free(g->score);
    g->score = NULL;
  }
}
