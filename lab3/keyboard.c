#include "keyboard.h"

uint8_t buff = 0;
uint8_t size = 0;
uint8_t bytes[8];
bool read_ok = 0;

void(kbc_ih)() {
  if (read_ok) {
    read_ok = 0;
    size = 0;
  }
  uint8_t value = 0;
  if (util_sys_inb(KEYBOARD_STATUS, &value))
    return;

  if (util_sys_inb(KEYBOARD_OUT_BUFF, &buff))
    return;

  if (value & KBC_READ_MASK)
    return;

  if (!(value & BUFFER_FULL))
    return;

  bytes[size] = buff;
  size++;

  if (buff != FIRST_BYTE) {
    read_ok = 1;
  }
}

static int hook_keyboard = KEYBOARD_IRQ;

int(keyboard_subscribe_int)(uint8_t *bit_no) {
  hook_keyboard = KEYBOARD_IRQ;
  *bit_no = hook_keyboard;
  return sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_keyboard);
}

int(keyboard_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_keyboard);
}
