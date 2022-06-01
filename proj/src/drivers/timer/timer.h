#ifndef TIMER_H
#define TIMER_H

/** @defgroup timer timer
 * @{
 *
 * Functions related to the i8254 Timer.
 */

#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include <minix/syslib.h>

#include "i8254.h"
#include "event.h"

/**
 * @brief Handle timer interrupts.
 * 
 */
void (timer_ih)(void);

/**
 * @brief Get an event from a timer interrupt.
 * 
 * @return Event struct with proper data for a timer interrupt.
 */
Event (timer_get_event)();

/**
 * @brief Reset timer interrupt count.
 * 
 */
void (reset_interrupts)(void);

/**@}*/

#endif
