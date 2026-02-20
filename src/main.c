#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SDL_FLAGS SDL_INIT_VIDEO

struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
};

bool game_init_sdl() {
  if (!SDL_Init(SDL_FLAGS)) {
    fprintf(stderr, "Error intializing SDL: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

// to free all the memory
void game_free() { SDL_Quit(); }

int main() {
  bool exit_status = EXIT_FAILURE;

  if (game_init_sdl()) {
    exit_status = EXIT_SUCCESS;
  }

  game_free();

  return exit_status;
}
