#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <lcom/lcf.h>
#include <stdint.h>

#include "i8042.h"
#include <minix/syslib.h>

void (kbc_ih)();

int (keyboard_subscribe_int)(uint8_t *bit_no);

int (keyboard_unsubscribe_int)();

#endif
