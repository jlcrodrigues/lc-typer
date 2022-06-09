#include "game.h"

static uint32_t primary_color = PRIMARY_COLOR;
static uint32_t secondary_color = SECONDARY_COLOR;
static uint32_t accent_color = ACCENT_COLOR;

static int base_y;
static int next_y;
static int last_line;

static char phrases[LINESIZE];

void game_create(Game* game) {
  char * phrase = phrase_select("/home/lcom/labs/proj/src/assets/phrases/lower_phrases.txt");
  game->player_position = 0;
  game->text = phrase;
  game->text_size = strlen(phrase)-2;
  game->time_elapsed = 0;
  game->typo_offset = 0;
  game->typo_count = 0;
  base_y = TEXT_Y_START;
  last_line = 0;
}

void game_draw(Game* game) {
  draw_text(game);
  if (game->time_elapsed)
    draw_wpm(game);
  /*char str[4]; //Debugging: see seconds count
  sprintf(str, "%d", game->time_elapsed);
  draw_sentence(str, 200, 400, 0xffffff);*/
}

void game_handle_event(Game* game, Event event) {
  if (event.type == KEYBOARD) {
    if (event.info.keyboard.buff == 0x81) proj_set_state(MENU);
    if (game->text[game->player_position] == event.info.keyboard.character
        && !(game->typo_offset)) {
      if (game->player_position == 1) {
        game->time_elapsed = 0;
      }
      game->player_position++;
      if (game->player_position == game->text_size) {
        proj_set_state(GAME_OVER);
      }
    }
    else if (test_letter(event.info.keyboard.character)) {
      game->typo_offset++;
      game->typo_count++;
    }
    else if (event.info.keyboard.buff == MAKECODE_BACKSPACE) {
      game->typo_offset--;
      game->typo_offset = (game->typo_offset < 0) ? 0 : game->typo_offset;
    }
  }
  if (event.type == TIMER) {
    if (!(event.info.timer.count_interrupts % timer_get_freq())) {
      if (game->player_position || game->typo_count) {
        game->time_elapsed++;
      }
    }
  }
}

void game_step(Game* game, Event event) {
  game_handle_event(game, event);
  game_draw(game);
}

void draw_text(Game* game) {
  int x_pos = MARGIN;
  if (game->player_position > next_y && !last_line)
    base_y -= LINE_HEIGHT;
  int y_pos = base_y;
  char* text_copy = malloc(game->text_size * sizeof(char));
  for (int i = 0; i < game->text_size; i++) {
    if (y_pos >= TEXT_Y_START && y_pos < TEXT_Y_MAX) {
      if (i < game->player_position) {
        draw_char(game->text[i], x_pos, y_pos, primary_color);
      }
      else if (i < game->player_position + game->typo_offset) {
        draw_char(game->text[i], x_pos, y_pos, accent_color);
      }
      else {
        draw_char(game->text[i], x_pos, y_pos, secondary_color);
      }
    }
    x_pos += PADDING + FONT_WIDTH;
    if (game->text[i] == ' ') {
      strcpy(text_copy, game->text);
      char* next = strtok(text_copy + i, " ");
      if (x_pos + MARGIN + get_sentence_width(next) > video_get_h_res()) {
        x_pos = MARGIN;
        y_pos += LINE_HEIGHT;
        if (y_pos == TEXT_Y_START + 2 * (LINE_HEIGHT))
          next_y = i;
      }
    }
  }
  if (y_pos == TEXT_Y_MAX - LINE_HEIGHT) last_line = 1;
}

void draw_wpm(Game* game) {
  if (game->time_elapsed == 0) return;
  int wpm = (int)(
    ((double)(game->player_position) / 5)
     / ((double)(game->time_elapsed) / 60) //TODO fix time count
    );
  char wpm_str[4];
  sprintf(wpm_str, "%d", wpm);
  strcat(wpm_str, " wpm");
  draw_sentence(wpm_str, MARGIN, MARGIN, PRIMARY_COLOR);
}

char* phrase_select(char* infile){
    FILE *file;
    if((file = fopen(infile,"r"))== NULL){
        perror("cannot open file");
        return NULL;
    }
    int n = rand() % NUMBER_OF_STRINGS;
    size_t str_size = 0;
    char* str = NULL;
    int i = 0;
    while(getline(&str, &str_size, file)> 0){
        if(i==n){
            for (size_t j=0;j<str_size;j++){
                phrases[j] = str[j];
            }
            break;
        }
        i++;
    }
    fclose(file);
    return phrases;
}