#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "enemy.h"
#include "player.h"
#include "score.h"

#define ROWS 3
#define COLS 8

typedef struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  Score *score;
  Player *player;
  Enemy enemies[ROWS][COLS];
  int enemy_direction;
  int enemy_alive_count;
  bool is_running;
  int state;
} Game;

enum state { MENU, PLAYING, GAME_OVER };

bool new (Game **game);
void run(Game *g);
bool load_media(Game *g);
void update(Game *g);
void game_over(Game *g);
void game_events(Game *g);
void menu_events(Game *g);
void gameover_events(Game *g);
void events(Game *g);
void game_reset(Game *g);
void render_menu(Game *g);
void render_gameover(Game *g);
void render_game(Game *g);

#endif
