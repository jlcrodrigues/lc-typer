#include "alphabet.h"

static xpm_row_t *letters_xpm[] = {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z};

int drawLetter(char letter, int pos_x, int pos_y) {
  if (letter < 'a' || letter > 'z')
    return 1;
  Sprite sprite = create_sprite(letters_xpm[(int) (letter - 'a')]);
  draw_sprite(sprite, pos_x, pos_y);
  return 0;
}
