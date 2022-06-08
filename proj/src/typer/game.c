#include "game.h"

static uint32_t primary_color = PRIMARY_COLOR;
static uint32_t secondary_color = SECONDARY_COLOR;

void game_create(Game* game) {
  game->player_position = 0;
  game->text = "the quick brown fox jumps over the lazy dog"; //TODO issue #3 generate sentences 
  game->text_size = strlen(game->text);
  game->time_elapsed = 0;
}

void game_draw(Game* game) {
  draw_text(game);
  if (game->time_elapsed)
    draw_wpm(game);
  /*char str[4]; //Debugging: see seconds count
  sprintf(str, "%d", game->time_elapsed);
  draw_sentence(str, 200, 400, 0xffffff);*/
}

void game_handle_event(Game* game, Event event) {
  if (event.type == KEYBOARD) {
    if (event.info.keyboard.buff == 0x81) proj_set_state(MENU);
    if (game->text[game->player_position] == event.info.keyboard.character) {
      if (game->player_position == 1) {
        game->time_elapsed = 0;
        reset_interrupts();
      }
      game->player_position++;
      if (game->player_position == game->text_size) {
        proj_set_state(GAME);
      }
    }
  }
  if (event.type == TIMER) {
    if (!(event.info.timer.count_interrupts % timer_get_freq())) {
      if (game->player_position) {
        game->time_elapsed++;
        reset_interrupts();
      }
    }
  }
}

void game_step(Game* game, Event event) {
  game_handle_event(game, event);
  game_draw(game);
}

void draw_text(Game* game) {
  int x_pos = MARGIN;
  int y_pos = 100;
  for (int i = 0; i < game->text_size; i++) {
    if (i < game->player_position) {
      draw_char(game->text[i], x_pos, y_pos, primary_color);
    }
    else {
      draw_char(game->text[i], x_pos, y_pos, secondary_color);
    }
    x_pos += PADDING + FONT_WIDTH;
    if (x_pos + MARGIN > video_get_h_res()) {
      x_pos = MARGIN;
      y_pos += FONT_HEIGHT + PADDING;
    }
  }
}

void draw_wpm(Game* game) {
  if (game->time_elapsed == 0) return;
  int wpm = (int)(
    ((double)(game->player_position) / 5)
     / ((double)(game->time_elapsed) / 60) //TODO fix time count
    );
  char wpm_str[4];
  sprintf(wpm_str, "%d", wpm);
  strcat(wpm_str, " wpm");
  draw_sentence(wpm_str, MARGIN, MARGIN, PRIMARY_COLOR);
}

