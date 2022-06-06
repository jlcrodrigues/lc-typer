#include "alphabet.h"

int drawLetter(char letter, int pos_x, int pos_y) {

    switch (letter) {
        case 'a':
            draw_sprite(a, pos_x, pos_y);
            break;
        case 'b':
            draw_sprite(b, pos_x, pos_y);
            break;
        case 'c':
            draw_sprite(c, pos_x, pos_y);
            break;
        case 'd':
            draw_sprite(d, pos_x, pos_y);
            break;
        case 'e':
            draw_sprite(e, pos_x, pos_y);
            break;
        case 'f':
            draw_sprite(f, pos_x, pos_y);
            break;
        case 'g':
            draw_sprite(g, pos_x, pos_y);
            break;
        case 'h':
            draw_sprite(h, pos_x, pos_y);
            break;
        case 'i':
            draw_sprite(i, pos_x, pos_y);
            break;
        case 'j':
            draw_sprite(j, pos_x, pos_y);
            break;
        case 'k':
            draw_sprite(k, pos_x, pos_y);
            break;
        case 'l':
            draw_sprite(l, pos_x, pos_y);
            break;
        case 'm':
            draw_sprite(m, pos_x, pos_y);
            break;
        case 'n':
            draw_sprite(n, pos_x, pos_y);
            break;
        case 'o':
            draw_sprite(o, pos_x, pos_y);
            break;
        case 'p':
            draw_sprite(p, pos_x, pos_y);
            break;
        case 'q':
            draw_sprite(q, pos_x, pos_y);
            break;
        case 'r':
            draw_sprite(r, pos_x, pos_y);
            break;
        case 's':
            draw_sprite(s, pos_x, pos_y);
            break;
        case 't':
            draw_sprite(t, pos_x, pos_y);
            break;
        case 'u':
            draw_sprite(u, pos_x, pos_y);
            break;
        case 'v':
            draw_sprite(v, pos_x, pos_y);
            break;
        case 'w':
            draw_sprite(w, pos_x, pos_y);
            break;
        case 'x':
            draw_sprite(x, pos_x, pos_y);
            break;
        case 'y':
            draw_sprite(y, pos_x, pos_y);
            break;
        case 'z':
            draw_sprite(z, pos_x, pos_y);
            break;

        default: return 1;
    }

    return 0;
}


