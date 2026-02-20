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

  g->is_running = true;

  return true;
}

void draw(Game *g) {
  SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255);
  SDL_RenderClear(g->renderer);
  SDL_RenderPresent(g->renderer);
}

void events(Game *g) {
  while (SDL_PollEvent(&g->event)) {
    switch (g->event.type) {
    case SDL_EVENT_QUIT:
      g->is_running = false;
      break;
    default:
      break;
    }
  }
}

void run(Game *g) {
  while (g->is_running) {
    events(g);
    draw(g);

    SDL_Delay(16);
  }
}
