#include "menu.h"

void menu_draw() {
  //TODO add buttons
  vg_draw_rectangle(200, 200, 100, 100, 0x123456);
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
  menu_handle_event(event);
  menu_draw();
}
