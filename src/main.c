#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SDL_FLAGS SDL_INIT_VIDEO

#define WINDOW_TITLE "Game"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} Game;

// declaring all the functions cause compiler is stupid
bool init_sdl(Game *g);
void game_free(Game *g);
void run(Game *g);

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
void game_free(Game *g) {
  if (g->renderer) {
    SDL_DestroyRenderer(g->renderer);
    g->renderer = NULL;
  }
  if (g->window) {
    SDL_DestroyWindow(g->window);
    g->window = NULL;
  }

  SDL_Quit();
}

void run(Game *g) {
  SDL_Event event;
  bool running = true;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
      if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
        running = false;
      }
    }

    SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255);
    SDL_RenderClear(g->renderer);
    SDL_RenderPresent(g->renderer);
  }
}

int main() {
  bool exit_status = EXIT_FAILURE;

  Game game = {0};

  if (init_sdl(&game)) {
    run(&game);

    exit_status = EXIT_SUCCESS;
  }

  game_free(&game);

  return exit_status;
}
