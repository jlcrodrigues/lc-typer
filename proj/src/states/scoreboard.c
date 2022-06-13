#include "scoreboard.h"

static char* title = "leaderboard";
static char* sub_title =   "score   date     time";
static char* line_format = "000 00000000 00000000";
// static int n_scores = 5;

int init = 0;
static char score_board[LINESIZE];

void score_board_draw() {
    int middle = video_get_h_res() / 2;
    draw_sentence(title, middle - (get_sentence_width(title) >> 1), 100, PRIMARY_COLOR);
    draw_sentence(sub_title, middle - (get_sentence_width(sub_title) >> 1) , 200, ACCENT_COLOR);


    int y_pos = 300;
    draw_sentence(score_board, middle - (get_sentence_width(line_format) >> 1), y_pos, SECONDARY_COLOR);
}

void score_board_handle_event(Event event) {
    if (event.type == KEYBOARD) {
        if (event.info.keyboard.buff == 0x81)  {
            init = 0;
            proj_set_state(MENU);
        }
    }
}

int score_board_update(Game *game) {
    FILE *file;
    if((file = fopen(SCORE_FILE,"r"))== NULL){
        perror("cannot open file");
        return 1;
    }

    // populate scores array
    char scores[N_SCORES+1][LINE_SIZE];
    int row = 0;
    size_t str_size = 0;
    char* line = malloc(50);
    while(getline(&line, &str_size, file) > 0) {
        strcpy(scores[row], line);
        row++;
    }

    // adding new score to scores array
    char new_score[LINESIZE];
    sprintf(new_score, "%03d %s %s\n", game->wpm, rtc_get_date_str(), rtc_get_hour_str());
    strcpy(scores[row], new_score);

    // insertion sort
    char temp[LINESIZE];
    int j = 0;
    for (int i = 1; i <= row; i++) {
        strcpy(temp, scores[i]);
        j = i - 1;
        while((strncmp(temp,scores[j], 3) > 0) && (j >= 0)) {
            strcpy(scores[j+1], scores[j]);
            j = j-1;
        }
        strcpy(scores[j+1], temp);
    }

    
    fclose(file);
    if((file = fopen(SCORE_FILE,"w")) == NULL){
        perror("cannot open file");
        return 1;
    }
    
    for (int i = 0; i < row; i++) {
            fprintf(file, "%s", scores[i]);
        }
    fclose(file);
    
    return 0;
}

void get_score_board() {
    FILE *file;
    if((file = fopen(SCORE_FILE,"r"))== NULL){
        perror("cannot open file");
        return;
    }

    char c;
    int i = 0;
    while((c = fgetc(file)) != EOF) {
        score_board[i] = c;
        i++;
    }
    fclose(file);
    init = 1;
}

void score_board_step(Event event) {
    score_board_handle_event(event);
    if (init == 0)
        get_score_board();
    score_board_draw();
}
