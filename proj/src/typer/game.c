#include "game.h"

void game_create(Game* game) {
  game->player_position = 0;
  game->text = "hello world"; //TODO issue #3 generate sentences 
  game->text_size = 11;
  game->time_elapsed = 0;
}

void game_draw(Game* game) {
  //TODO issue #8 draw sentences
  for (int i = 0; i < game->text_size; i++) {
    if (vg_draw_rectangle(10 * i, 100, 10, 10, 0xffffff)) return;
    if (i < game->player_position) {
      if (vg_draw_rectangle(10 * i, 110, 10, 10, 0xff)) return;
    }
  }
  //TODO display live wpm
}

void game_handle_event(Game* game, Event event) {
  if (event.type == KEYBOARD) {
    if (event.info.keyboard.buff == 0x81) proj_set_state(MENU);
    if (game->text[game->player_position] == event.info.keyboard.character) {
      if (game->player_position == 1) game->time_elapsed = 0;
      game->player_position++;
      if (game->player_position == game->text_size) {
        printf("wpm: %d\n", (int)(((double)(game->player_position) / 5) / ((double)(game->time_elapsed) / 60)));
        proj_set_state(GAME);
      }
    }
  }
  if (event.type == TIMER) {
    if (!(event.info.timer.count_interrupts % timer_get_freq())) {
      game->time_elapsed++;
    }
  }
}

void game_step(Game* game, Event event) {
  game_handle_event(game, event);
  game_draw(game);
}

