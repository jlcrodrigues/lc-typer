#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <lcom/lcf.h>
#include <stdint.h>

#include "i8042.h"
#include <minix/syslib.h>

/**
 * @brief Handle keyboard interrupts. Reads scancodes and sets read_ok when the reading is successful.
 * 
 */
void (kbc_ih)();

/**
 * @brief Subscribe keyboard interrupts and disable Minix default handler.
 * @param bit_no Receives the bit that will be set for keyboard interrupts.
 */
int (keyboard_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribe keyboard interrupts.
 * @return Returns 0 upon success, and 1 otherwise.
 */
int (keyboard_unsubscribe_int)();

#endif
