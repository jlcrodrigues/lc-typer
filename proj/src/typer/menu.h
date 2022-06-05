#ifndef MENU_H
#define MENU_H

/** @defgroup state menu
 * @{
 *
 * Functions related to the menu state.
 */

#include <lcom/lcf.h>
#include "driver.h"
#include "proj.h"

/**
 * @brief Draws the menu to the screen.
 * 
 */
void menu_draw();

/**
 * @brief Handle an event.
 * 
 * @param event Event struct.
 */
void menu_handle_event(Event event);

/**
 * @brief Handles events and draws the menu.
 * 
 * @param event Last event that occurred.
 */
void menu_step(Event event);

/**@}*/

#endif
