#include "game.h"

int game_create(Game* game) {
  game->player_position = 0;
  game->text = "hello world"; //TODO issue #3 generate sentences 
  game->text_size = 11;
  game->time_elapsed = 0;
  return 0;
}

void game_draw(Game* game) {
  //TODO issue #8 draw sentences
  for (size_t i = 0; i < game->text_size; i++) {
    if (vg_draw_rectangle(10 * i, 100, 10, 10, 0xffffff)) return;
    if (i < game->player_position) {
      if (vg_draw_rectangle(10 * i, 110, 10, 10, 0xff)) return;
    }
  }
}

void game_handle_event(Game* game, Event event) {
  if (event.type == KEYBOARD) {
    if (game->text[game->player_position] == event.info.keyboard.character) {
      game->player_position++;
    }
  }
}

void game_step(Game* game, Event event) {
  game_handle_event(game, event);
  game_draw(game);
}

