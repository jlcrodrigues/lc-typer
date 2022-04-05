#include "keyboard.h"

uint8_t buff = 0;
uint8_t size = 0;
uint8_t bytes[8];
int read_error = 0;
bool complete = 0;

void (kbc_ih)() {
  if (complete) {
    complete = 0;
    size = 0;
  }
  uint8_t value = 0;
  util_sys_inb(KEYBOARD_STATUS, &value);

  util_sys_inb(KEYBOARD_OUT_BUFF, &buff);

  if (value & KEYBOARD_PARITY) {
    read_error = 1;
    return;
  }

  if (!(value & BUFFER_FULL)) {
    read_error = 1;
    return;
  }

  if (value & KEYBOARD_TIMEOUT) {
    read_error = 1;
    return;
  }

  bytes[size] = buff;
  size++;

  if (buff != FIRST_BYTE) {
    complete = 1;
  }
  read_error = 0;
}

int hook = 0;

int (keyboard_subscribe_int)() {
  return sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook);
}

int (keyboard_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook);
}
