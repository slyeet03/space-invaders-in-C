#include "../includes/main.h"
#include "../includes/game.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// to initialize sdl
bool init_sdl(Game *g) {
  if (!SDL_Init(SDL_FLAGS)) {
    fprintf(stderr, "Error intializing SDL: %s\n", SDL_GetError());
    return false;
  }

  g->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (!g->window) {
    fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
    return false;
  }

  g->renderer = SDL_CreateRenderer(g->window, NULL);
  if (!g->renderer) {
    fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

// to free all the memory
void game_free(Game **game) {
  if (*game) {
    Game *g = *game;
    if (g->renderer) {
      SDL_DestroyRenderer(g->renderer);
      g->renderer = NULL;
    }
    if (g->window) {
      SDL_DestroyWindow(g->window);
      g->window = NULL;
    }

    SDL_Quit();
    free(g);
    g = NULL;
    *game = NULL;
  }
}

int main() {
  bool exit_status = EXIT_FAILURE;

  Game *game = NULL;

  if (new(&game)) {
    run(game);

    exit_status = EXIT_SUCCESS;
  }

  game_free(&game);

  return exit_status;
}
