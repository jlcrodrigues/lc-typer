#include "alphabet.h"

static xpm_row_t *letters_xpm[] = {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z};

int drawLetter(char letter, int pos_x, int pos_y) {
  if (letter < 'a' || letter > 'z')
    return 1;
  Sprite sprite = create_sprite(letters_xpm[(int) (letter - 'a')]);
  return draw_sprite(sprite, pos_x, pos_y);
}

int drawSentence(char *sentence, int pos_x, int pos_y) {
  int i = 0;
  while (sentence[i] != '\0') {
    if (sentence[i] > 'a' && sentence[i] < 'z') {
        if (drawLetter(sentence[i], pos_x, pos_y))
            return 1;
    }
    pos_x += FONT_WIDTH + PADDING;
    i++;
  }
  return 0;
}

int getSentenceWidth(char *sentence) {
  int size = 0, i = 0;
  while (sentence[i] != '\0') {
    size += FONT_WIDTH + PADDING;
    i++;
  }
  return size - PADDING;
}
