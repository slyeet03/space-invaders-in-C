#include "../includes/game.h"
#include "../includes/enemy.h"
#include "../includes/main.h"
#include "../includes/player.h"

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

  if (!player_new(&g->player)) {
    fprintf(stderr, "Error initializing player");
    return false;
  }

  enemies_new(g);

  if (!load_media(g)) {
    return false;
  }

  g->enemy_direction = 1;
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
      case SDL_SCANCODE_LEFT:
        g->player->move_left = true;
        g->player->move_right = false;
        break;
      case SDL_SCANCODE_RIGHT:
        g->player->move_right = true;
        g->player->move_left = false;
        break;
      case SDL_SCANCODE_SPACE:
        player_fire(g->player);
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
  if (!score_new(g)) {
    fprintf(stderr, "Error loading score font");
    return false;
  }

  if (!score_load(g)) {
    fprintf(stderr, "Error loading score");
    return false;
  }

  if (!player_load(g->player, g)) {
    fprintf(stderr, "Error loading player");
    return false;
  }

  if (!enemies_load(g)) {
    fprintf(stderr, "Error loading enemies");
    return false;
  }

  return true;
}

void collision_update(Game *g) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (g->player->bullets[i].active) {
      bool collision = false;
      for (int j = 0; j < ROWS; j++) {
        for (int k = 0; k < COLS; k++) {
          if (collision) {
            break;
          }
          if (g->enemies[j][k].alive) {
            float bullet_left = g->player->bullets[i].rect.x;
            float bullet_right =
                g->player->bullets[i].rect.x + g->player->bullets[i].rect.w;
            float bullet_top = g->player->bullets[i].rect.y;
            float bullet_bottom =
                g->player->bullets[i].rect.y + g->player->bullets[i].rect.h;

            float enemy_left = g->enemies[j][k].rect.x;
            float enemy_right =
                g->enemies[j][k].rect.x + g->enemies[j][k].rect.w;
            float enemy_top = g->enemies[j][k].rect.y;
            float enemy_bottom =
                g->enemies[j][k].rect.y + g->enemies[j][k].rect.h;

            // bullet rectangle and enemy rectangle overlap
            if ((bullet_right > enemy_left) && (bullet_left < enemy_right) &&
                (bullet_bottom > enemy_top) && (bullet_top < enemy_bottom)) {
              g->player->bullets[i].active = false;

              g->enemies[j][k].health--;
              if (g->enemies[j][k].health <= 0) {
                g->enemies[j][k].alive = false;

                if (j == 0) {
                  g->score->value += 30;
                } else if (j == 1) {
                  g->score->value += 20;
                } else {
                  g->score->value += 10;
                }

                g->enemy_alive_count--;
              }

              score_update(g);
              collision = true;
            }
          }
        }
      }
    }
  }
}

void game_over(Game *g) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (g->enemies[i][j].alive) {
        if ((g->enemies[i][j].rect.y + g->enemies[i][j].rect.h) >=
            g->player->rect.y) {
          g->is_running = false;
        }
      }
    }
  }
}

void update(Game *g) {
  player_update(g->player);
  bullet_update(g->player);
  enemies_update(g);
  collision_update(g);
  game_over(g);
}

void draw(Game *g) {
  SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255);
  SDL_RenderClear(g->renderer);

  score_render(g, g->renderer);
  player_render(g->player, g->renderer);
  bullet_render(g->player, g->renderer);
  enemies_render(g, g->renderer);

  SDL_RenderPresent(g->renderer);
}

void run(Game *g) {
  while (g->is_running) {
    events(g);
    update(g);
    draw(g);

    SDL_Delay(16);
  }
}
