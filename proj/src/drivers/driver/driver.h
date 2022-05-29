#ifndef DRIVER_H
#define DRIVER_H

#include <lcom/lcf.h>
#include "keyboard.h"
#include "mouse.h"
#include "video.h"

typedef enum LoopState {CONTINUE, OVER, ERROR} LoopState;

/**
 * @brief Subscribe interrupts: keyboard, mouse, timer.
 * @return int Returns zero upon success.
 */
int (subscribe_interrupts)(void);

/**
 * @brief Unsubscribe interrupts: keyboard, mouse, timer.
 * @return int Returns zero upon success.
 */
int (unsubscribe_interrupts)(void);

LoopState (interrupt_handler)(void);

#endif
