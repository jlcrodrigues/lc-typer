#ifndef BUTTON_H
#define BUTTON_H

typedef struct Button {
  int pos_x, pos_y;
  char* text;
  int hover;
  int clicked;
  int width;
} Button;

#include <lcom/lcf.h>
#include "proj.h"
#include "driver.h"
#include "mouse_sprite.h"


Button button_create(int pos_x, int pos_y, char* text);

void button_draw(Button* button);

void button_handle_event(Button* button);

void button_step(Button* button);

#endif
