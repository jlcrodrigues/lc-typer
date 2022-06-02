#ifndef MOUSE_SPRITE_H
#define MOUSE_SPRITE_H

#include <lcom/lcf.h>

#include "driver.h"

#define MOUSE_START 300

typedef struct mouse_sprite {
  uint16_t x_pos;
  uint16_t y_pos;
  int clicked;
} mouse_sprite;

void mouse_sprite_create(mouse_sprite* mouse);

void mouse_sprite_handle_event(mouse_sprite* mouse, Event event);

void mouse_sprite_draw(mouse_sprite* mouse);

void mouse_sprite_step(mouse_sprite* mouse, Event event);

#endif
