#ifndef GAME_H
#define GAME_H

#include <lcom/lcf.h>
#include "driver.h"

typedef struct Game {
  size_t player_position;
  char* text;
  size_t text_size;
  int time_elapsed;
} Game;

int game_create(Game* game);

void game_draw(Game* game);

void game_handle_event(Game* game, Event event);

void game_step(Game* game, Event event);

#endif
