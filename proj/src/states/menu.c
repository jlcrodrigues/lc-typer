#include "menu.h"

static Button start;

void menu_init(){
  create_button(&start);
}

void menu_draw() {
  //TODO add buttons
  draw_button(&button);
static char* title = "lc typer";

/*void menu_draw() {
  //TODO add buttons
  int middle = video_get_h_res() / 2;
  draw_sentence(title, middle - get_sentence_width(title) / 2, 200, PRIMARY_COLOR);
}*/

void menu_handle_event(Event event) {
  if (event.type == KEYBOARD) {
    if (event.info.keyboard.character == ' ') 
      proj_set_state(GAME);
    else if (event.info.keyboard.buff == 0x81) 
      proj_set_state(OVER);
  }
}

void menu_step(Event event) {
  menu_handle_event(event);
  menu_draw();
}
