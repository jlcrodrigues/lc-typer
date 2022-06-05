#ifndef PROJ_H
#define PROJ_H

#define VIDEO_MODE 0x115

typedef enum {MENU, GAME, OVER} State;

#include <lcom/lcf.h>
#include "driver.h"
#include "game.h"
#include "mouse_sprite.h"

int proj_setup(void);

void proj_step(void);

int proj_cleanup(void);

void proj_step_game(Event event);

void proj_set_state(State new_state);

#endif
