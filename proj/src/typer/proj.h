#ifndef PROJ_H
#define PROJ_H

#define VIDEO_MODE 0x115

typedef enum {MENU, GAME} State;

#include <lcom/lcf.h>
#include "driver.h"
#include "game.h"
#include "mouse_sprite.h"

void proj_set_state(State new_state);

#endif
