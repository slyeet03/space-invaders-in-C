#include "../includes/game.h"
#include "../includes/main.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// constructor of the game
bool new(Game **game) {
  *game = calloc(1, sizeof(Game));
  if (*game == NULL) {
    fprintf(stderr, "Error in calloc of new game.\n");
    return false;
  }
  Game *g = *game;

  if (!init_sdl(g)) {
    return false;
  }

  if (!load_media(g)) {
    return false;
  }

  g->is_running = true;

  return true;
}

void events(Game *g) {
  while (SDL_PollEvent(&g->event)) {
    switch (g->event.type) {
    case SDL_EVENT_QUIT:
      g->is_running = false;
      break;
    case SDL_EVENT_KEY_DOWN:
      switch (g->event.key.scancode) {
      case SDL_SCANCODE_ESCAPE:
        g->is_running = false;
        break;
      default:
        break;
      }
      break;
    default:
      break;
    }
  }
}

bool load_media(Game *g) {
  g->font = TTF_OpenFont("../assets/fonts/FiraCode-Bold.ttf", FONT_SIZE);
  if (!g->font) {
    fprintf(stderr, "Error opening font: %s\n", SDL_GetError());
    return false;
  }

  SDL_Surface *surface =
      TTF_RenderText_Blended(g->font, SCORE_TXT, 0, RED_COLOR);
  if (!surface) {
    fprintf(stderr, "Error rendering score: %s\n", SDL_GetError());
    return false;
  }

  // getting the dimensions for the rectangle from the surface struct directly
  g->score_rect.w = (float)surface->w;
  g->score_rect.h = (float)surface->h;
  // changing x and y of the rectangle
  g->score_rect.x = 10;
  g->score_rect.y = 10;

  // converting the font surface to texture
  g->score_image = SDL_CreateTextureFromSurface(g->renderer, surface);
  SDL_DestroySurface(surface);
  surface = NULL;
  if (!g->score_image) {
    fprintf(stderr, "Error creating texture from surface: %s\n",
            SDL_GetError());
    return false;
  }
  // when scaling an image it try to not get that much blury
  if (!SDL_SetTextureScaleMode(g->score_image, SDL_SCALEMODE_NEAREST)) {
    fprintf(stderr, "Error setting texture scale mode: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

void draw(Game *g) {
  SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255);
  SDL_RenderClear(g->renderer);

  SDL_RenderTexture(g->renderer, g->score_image, NULL, &g->score_rect);

  SDL_RenderPresent(g->renderer);
}

void run(Game *g) {
  while (g->is_running) {
    events(g);
    draw(g);

    SDL_Delay(16);
  }
}
