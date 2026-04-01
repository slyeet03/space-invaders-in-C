#include "../includes/game.h"
#include "../includes/enemy.h"
#include "../includes/main.h"
#include "../includes/player.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum state game_state;

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

  if (!load_media(g)) {
    return false;
  }

  enemies_new(g);

  g->enemy_direction = 1;
  g->is_running = true;

  game_state = MENU;

  return true;
}

void game_reset(Game *g) {
  // score reset
  g->score->value = 0;
  score_update(g);

  // player reset
  g->player->rect.x = (WINDOW_WIDTH / 2.0f) - (g->player->rect.w / 2.0f);
  g->player->rect.y = WINDOW_HEIGHT - 80;

  g->player->displacement = 45;

  g->player->move_left = false;
  g->player->move_right = false;

  // bullet reset
  for (int i = 0; i < MAX_BULLETS; i++) {
    g->player->bullets[i].active = false;
    g->player->bullets[i].rect.w = 5.0f;
    g->player->bullets[i].rect.h = 15.0f;
    g->player->bullets[i].speed = 10.0f;
    g->player->bullets[i].rect.x = 0.0f;
    g->player->bullets[i].rect.y = 0.0f;
  }

  // enemy reset
  float enemy_w = g->enemies[0][0].rect.w;
  float enemy_h = g->enemies[0][0].rect.h;
  float total_width = COLS * enemy_w + (COLS - 1) * ENEMY_SPACING;
  float start_x = (WINDOW_WIDTH - total_width) / 2.0f;

  g->enemy_alive_count = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      g->enemies[i][j].alive = true;
      g->enemy_alive_count++;
      g->enemies[i][j].rect.x = start_x + j * (enemy_w + ENEMY_SPACING);
      g->enemies[i][j].rect.y = START_Y + i * (enemy_h + ENEMY_SPACING);
      g->enemies[i][j].speed = 1.5f;

      if (i == 0) {
        g->enemies[i][j].health = 3;
      } else if (i == 1) {
        g->enemies[i][j].health = 2;
      } else {
        g->enemies[i][j].health = 1;
      }
    }
  }
  g->enemy_direction = 1;
}

void events(Game *g) {
  if (game_state == MENU) {
    menu_events(g);
  }
  if (game_state == PLAYING) {
    game_events(g);
  }
  if (game_state == GAME_OVER) {
    gameover_events(g);
  }
}

void game_events(Game *g) {
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

void menu_events(Game *g) {
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
      case SDL_SCANCODE_RETURN:
        game_state = PLAYING;
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

void gameover_events(Game *g) {
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
      case SDL_SCANCODE_R:
        game_state = PLAYING;
        game_reset(g);
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
          game_state = GAME_OVER;
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

void render_text(Game *g, const char *text, float x, float y) {
  // cheating and using score text system and making it generalised
  SDL_Surface *surface =
      TTF_RenderText_Blended(g->score->font, text, 0, RED_COLOR);
  if (!surface)
    return;

  SDL_Texture *texture = SDL_CreateTextureFromSurface(g->renderer, surface);

  SDL_FRect rect = {x, y, (float)surface->w, (float)surface->h};

  SDL_DestroySurface(surface);

  if (!texture)
    return;

  SDL_RenderTexture(g->renderer, texture, NULL, &rect);
  SDL_DestroyTexture(texture);
}

void render_menu(Game *g) {
  render_text(g, "SPACE INVADERS", 250, 200);
  render_text(g, "Press Enter to Start", 230, 300);
}

void render_game(Game *g) {
  score_render(g, g->renderer);
  player_render(g->player, g->renderer);
  bullet_render(g->player, g->renderer);
  enemies_render(g, g->renderer);
}

void render_gameover(Game *g) {
  char score_text[50];
  sprintf(score_text, "Score: %d", g->score->value);

  render_text(g, "GAME OVER", 300, 200);
  render_text(g, score_text, 300, 260);
  render_text(g, "Press R to Restart", 250, 320);
}

void draw(Game *g) {
  SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255);
  SDL_RenderClear(g->renderer);

  if (game_state == PLAYING) {
    render_game(g);
  }
  if (game_state == MENU) {
    render_menu(g);
  }
  if (game_state == GAME_OVER) {
    render_gameover(g);
  }

  SDL_RenderPresent(g->renderer);
}

void run(Game *g) {
  while (g->is_running) {
    events(g);

    if (game_state == PLAYING) {
      update(g);
    }

    draw(g);

    SDL_Delay(16);
  }
}
