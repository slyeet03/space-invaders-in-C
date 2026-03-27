#include "../includes/main.h"
#include "../includes/game.h"

// to initialize sdl
bool init_sdl(Game *g) {
  if (!SDL_Init(SDL_FLAGS)) {
    fprintf(stderr, "Error intializing SDL: %s\n", SDL_GetError());
    return false;
  }

  if (!TTF_Init()) {
    fprintf(stderr, "Error intializing SDL3_ttf: %s\n", SDL_GetError());
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

    if (g->score_image) {
      SDL_DestroyTexture(g->score_image);
      g->score_image = NULL;
    }
    if (g->font) {
      TTF_CloseFont(g->font);
      g->font = NULL;
    }
    if (g->renderer) {
      SDL_DestroyRenderer(g->renderer);
      g->renderer = NULL;
    }
    if (g->window) {
      SDL_DestroyWindow(g->window);
      g->window = NULL;
    }

    TTF_Quit();
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
