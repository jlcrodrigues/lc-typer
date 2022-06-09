#include "button.h"

static uint32_t border_color = 3;

void create_button(Button* button){
  button->x = x;
  button->y = y;
  button->background_color = background_color;
  button->hover_color = hover_color;
  button->selected_color = selected_color;
  return button;
}

void draw_button(Button* button){
  if (vg_draw_rectangle(button->x, button->y, BUTTON_WIDTH, BUTTON_HEIGHT, border_color)) {
    return;
  }

void button_handle_event(Event event){
  if (event.type == MOUSE){
    if (event.info.mouse.clicked == 1)
  }
}
