#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <stdint.h>
#include <lcom/lcf.h>

/** @defgroup button button
 * @{
 *
 * Button
 */

#define BUTTON_WIDTH 48
#define BUTTON_HEIGHT 24
#define BUTTON_BORDER_SIZE 2

typedef struct{
    int16_t x, y;              /**< horizontal and vertical position of the button */
    uint8_t background_color;  /**< button background color */
    uint8_t hover_color;       /**< button color when the mouse is over the button */
    uint8_t selected_color; 
    enum state   /**< button color when the button is selected */
} Button;


void create_button(Button* button);

/**
 * @brief Draws the given button on the screen
 * 
 * @param button pointer to the button to be drawn
 * @return 0 if success, non-zero otherwise
 */
int draw_button(Button* button);

void button_handle_event();

#endif
