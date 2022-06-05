#ifndef GAME_H
#define GAME_H

/** @defgroup state game
 * @{
 *
 * Functions related to the game state.
 */

#include <lcom/lcf.h>
#include "driver.h"
#include "proj.h"

/**
 * @brief Represents a game. A game consists of a sentence, 
 * a position in the sentence and a value for the time elapsed.
 * 
 */
typedef struct Game {
  /** @brief Player's current position in the game sentence. **/
  int player_position;
  /** @brief The sentence to be completed. **/
  char* text;
  /** @brief The size of the target text. **/
  int text_size;
  /** @brief Amount, in seconds, of time elapsed since the first letter hit. **/
  int time_elapsed;
} Game;

/**
 * @brief Initialize a game struct.
 * 
 * @param game Already created game struct passed by reference.
 */
void game_create(Game* game);

/**
 * @brief Draw a game on the screen.
 * Drawing the game means drawing every necessary element for the 
 * game state.
 * 
 * @param game 
 */
void game_draw(Game* game);

/**
 * @brief Handle the latest event. Updates the game values according to it.
 * 
 * @param game Game struct passed by reference.
 * @param event Latest event that occurred.
 */
void game_handle_event(Game* game, Event event);

/**
 * @brief Draw the game and handle the latest event.
 * This function calls game_draw and game_handle_event
 * 
 * @param game Game struct passed by reference.
 * @param event Latest event that occurred.
 */
void game_step(Game* game, Event event);

/**@}*/

#endif
