#include "sprite.h"

static xpm_row_t *letters_xpm[] = {
  a_xpm, b_xpm, c_xpm, d_xpm, e_xpm, f_xpm, g_xpm, h_xpm, i_xpm,
  j_xpm, k_xpm, l_xpm, m_xpm, n_xpm, o_xpm, p_xpm, q_xpm, r_xpm,
  s_xpm, t_xpm, u_xpm, v_xpm, w_xpm, x_xpm, y_xpm, z_xpm};

static xpm_row_t *digits_xpm[] = {zero, one, two, three, four, five, six, seven, eight, nine, percentage};

Sprite (create_sprite)(xpm_map_t xpm) {
  Sprite sprite;
  enum xpm_image_type type = XPM_8_8_8;
  sprite.pix_map = xpm_load(xpm, type, &(sprite.img));
  return sprite;
}

int draw_char(char letter, int pos_x, int pos_y, uint32_t color) {
  Sprite sprite;
  if (letter <= '9' && letter >= '0')
    sprite = create_sprite(digits_xpm[(int) (letter - '0')]);
  else if (letter <= 'z' && letter >= 'a')
    sprite = create_sprite(letters_xpm[(int) (letter - 'a')]);
  else if (letter == '%')  
    sprite = create_sprite(digits_xpm[10]);
  else 
    return 1;
  return draw_letter(sprite, pos_x, pos_y, color);
}

int draw_sentence(char *sentence, int pos_x, int pos_y, uint32_t color) {
  int i = 0;
  while (sentence[i] != '\0') {
    draw_char(sentence[i], pos_x, pos_y, color);
    pos_x += FONT_WIDTH + PADDING;
    i++;
  }
  return 0;
}

int get_sentence_width(char *sentence) {
  int size = 0, i = 0;
  while (sentence[i] != '\0') {
    size += FONT_WIDTH + PADDING;
    i++;
  }
  return (strlen(sentence) * (PADDING + FONT_WIDTH)) - PADDING;
}
