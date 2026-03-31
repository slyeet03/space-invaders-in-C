#ifndef MAIN_H
#define MAIN_H

#include "../includes/game.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SDL_FLAGS SDL_INIT_VIDEO

#define WINDOW_TITLE "Game"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FONT_SIZE 20
#define RED_COLOR (SDL_Color){255, 0, 0}

bool init_sdl(Game *g);
void game_free(Game **game);

#endif
