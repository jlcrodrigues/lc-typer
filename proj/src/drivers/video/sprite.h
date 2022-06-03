#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>

/** @defgroup sprite
 * @{
 * 
 *  Drawable screen image
 */

/**
 * @brief Structure that holds drawable images.
 * Use "::"<create_sprite> to load an image.
 * 
 */
typedef struct Sprite
{
  /** @brief xpm_image_t img Loaded from the xpm. */
  xpm_image_t img;
  /** @brief uint8_t* pix_map Map of the image colors. */
  uint8_t* pix_map;
} Sprite;


/**
 * @brief Create a sprite from from a xpm.
 * @param xpm XPM map.
 * @return sprite Sprite struct with sprite info.
 */
Sprite (create_sprite)(xpm_map_t xpm);

/**@}*/

#endif
