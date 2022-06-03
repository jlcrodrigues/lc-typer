#include "sprite.h"

Sprite (create_sprite)(xpm_map_t xpm) {
  Sprite sprite;
  enum xpm_image_type type = XPM_INDEXED;
  sprite.pix_map = xpm_load(xpm, type, &(sprite.img));
  return sprite;
}
