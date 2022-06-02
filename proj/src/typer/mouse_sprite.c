#include "mouse_sprite.h"

void mouse_sprite_create(mouse_sprite* mouse) {
  mouse->x_pos = MOUSE_START;
  mouse->y_pos = MOUSE_START;
  mouse->clicked = 0;
}

void mouse_sprite_handle_event(mouse_sprite* mouse, Event event) {
  if (event.type != MOUSE) return;
  mouse->x_pos += event.info.mouse.x_delta;
  mouse->y_pos -= event.info.mouse.y_delta;
  mouse->clicked = event.info.mouse.clicked;
}

void mouse_sprite_draw(mouse_sprite* mouse) {
  vg_draw_rectangle(mouse->x_pos, mouse->y_pos, 10, 10, 0xffffff);
}

void mouse_sprite_step(mouse_sprite* mouse, Event event) {
  if (event.type == MOUSE)
    mouse_sprite_handle_event(mouse, event);
  mouse_sprite_draw(mouse);
}
