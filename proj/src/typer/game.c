#include "game.h"

void game_create(Game* game) {
  game->player_position = 0;
  game->text = "the quick brown fox jumps over the lazy dog"; //TODO issue #3 generate sentences 
  game->text_size = strlen(game->text);
  game->time_elapsed = 0;
}

void game_draw(Game* game) {
  //TODO issue #8 draw sentences
  draw_text(game);
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

void draw_text(Game* game) {
  int x_pos = PADDING;
  int y_pos = 100;
  for (int i = 0; i < game->text_size; i++) {
    if (i < game->player_position) {
    }
    else {
      drawLetter(game->text[i], x_pos, y_pos);
    }
    x_pos += PADDING + FONT_WIDTH;
    if (x_pos > video_get_h_res()) {
      x_pos = PADDING;
      y_pos += FONT_HEIGHT + PADDING;
    }
  }
}

