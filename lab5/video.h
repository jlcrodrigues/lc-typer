#include <lcom/lcf.h>

#define RED(n) ((n >> 16) & 0xff)
#define BLUE(n) ((n >> 8) & 0xff)
#define GREEN(n) (n & 0xff)

int (map_memory)();

void* (set_mode)(uint16_t mode);

int (draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (draw_pattern)(uint8_t no_rectangles, uint32_t first, uint8_t step);
