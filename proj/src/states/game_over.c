#include "game_over.h"

void game_over_draw(Game* game) {
  int16_t h_res = video_get_h_res();
  int width;
  int wpm = (int)(
    ((double)(game->player_position) / 5)
     / ((double)(game->time_elapsed) / 60) //TODO fix time count
    );
  char wpm_str[4];
  sprintf(wpm_str, "%d", wpm);
  width = get_sentence_width("wpm");
  draw_sentence("wpm", h_res / 4 - width / 2, TEXT_Y_POS, PRIMARY_COLOR);
  width = get_sentence_width(wpm_str);
  draw_sentence(wpm_str, h_res / 4 - width / 2, TEXT_Y_POS + LINE_HEIGHT, PRIMARY_COLOR);
  width = get_sentence_width("acc");
  draw_sentence("acc", 3 * h_res / 4 - width / 2, TEXT_Y_POS, PRIMARY_COLOR);
}

void game_over_handle_event(Game* game, Event event) {
  if (event.type == KEYBOARD) {
    if (event.info.keyboard.character == ' ') {
      proj_set_state(GAME);
    }
    else if (event.info.keyboard.buff == 0x81) {
      proj_set_state(MENU);
    }
  }
}

void game_over_step(Game* game, Event event) {
  game_over_handle_event(game, event);
  game_over_draw(game);
}
