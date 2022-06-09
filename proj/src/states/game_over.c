#include "game_over.h"

void game_over_draw(Game* game) {
  draw_sentence("hello", 100, 200, 0xff);
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
