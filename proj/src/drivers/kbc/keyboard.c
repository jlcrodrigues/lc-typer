#include "keyboard.h"

static uint8_t buff = 0;
static uint8_t size = 0;
static uint8_t bytes[4];
static bool read_ok = 0;

void(kbc_ih)() {
  if (read_ok) {
    read_ok = 0;
    size = 0;
  }
  uint8_t value = 0;
  if (util_sys_inb(KBC_STATUS, &value))
    return;

  if (util_sys_inb(KBC_OUT_BUFF, &buff))
    return;

  if (value & KBC_READ_MASK)
    return;

  if (!(value & OUT_BUFFER_FULL))
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

int (keyboard_is_complete)() {
  return read_ok;
}

Event (keyboard_get_event)(void) {
  Event event;
  event.type = KEYBOARD;
  event.info.keyboard.size = size;
  event.info.keyboard.character = '\0'; //TODO convert make code
  return event;
}
