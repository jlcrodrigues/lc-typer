#ifndef EVENT_H
#define EVENT_H

typedef enum {KEYBOARD, MOUSE, TIMER, BLANK} EventType;

typedef struct Event {
  EventType type;
  union {
    struct timer { // timer
      int count_interrupts;
    } timer;
    struct keyboard { //keyboard
      uint8_t size;
      char character;
    } keyboard;
    struct mouse { // mouse
      uint16_t x_delta;
      uint16_t y_delta;
      int clicked;
    } mouse;
  } info;
} Event;

#endif
