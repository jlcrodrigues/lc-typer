#include "digits.h"

static xpm_row_t *digits_xpm[] = {zero, one, two, three, four, five, six, seven, eight, nine};

int drawDigit(int digit, int pos_x, int pos_y) {
  if (digit < 0 || digit > 9)
    return 1;
  Sprite sprite = create_sprite(digits_xpm[digit]);
  draw_sprite(sprite, pos_x, pos_y);
  return 0;
}
