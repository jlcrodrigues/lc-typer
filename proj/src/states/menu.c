#include "menu.h"

static char* title = "lc typer";
static Button start_button;
static Button exit_button;

void menu_init() {
  start_button = button_create(video_get_h_res() / 2, BUTTON_POS_Y, "start");
  exit_button = button_create(video_get_h_res() / 2, BUTTON_POS_Y + LINE_HEIGHT, "exit");
}

void menu_draw() {
  int middle = video_get_h_res() / 2;
  draw_sentence(title, middle - get_sentence_width(title) / 2, TITLE_POS_Y, PRIMARY_COLOR);
}

void menu_handle_event(Event event) {
  if (event.type == KEYBOARD) {
    if (event.info.keyboard.character == ' ') 
      proj_set_state(GAME);
    else if (event.info.keyboard.buff == 0x81) 
      proj_set_state(OVER);
  }
}

void menu_step(Event event) {
  button_step(&start_button);
  button_step(&exit_button);
  menu_handle_event(event);
  menu_draw();
}
