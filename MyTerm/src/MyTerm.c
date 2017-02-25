//
// Created by jonn on 18.02.17.
//
#include "MyTerm.h"

int mt_clrscr(void) {
    char *clear = "\E[H\E[2J";
    write(STDOUT_FILENO, clear, strlen(clear));
    return OK;
}

int mt_gotoXY(uint16_t x, uint16_t y) {
    char buf[40];
    char *gotoxy = "\E[%d;%dH";
    uint16_t rows, cols;
    mt_getscreensize(&rows, &cols);
    if ((x >= 0) && (y >= 0) && (x < cols) && (y < rows)) {
        if (sprintf(buf, gotoxy, y, x) > 0) {
            if (write(STDOUT_FILENO, buf, strlen(buf)) == -1) {
                return ERR_PRINT;
            }
        }
        else {
            return ERR_PRINT;
        }
    }
    else {
        return ERR_SCREEN_SIZE;
    }
    return OK;
}

int mt_getscreensize(uint16_t *rows, uint16_t *cols) {
    struct winsize window_size;
    if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size)) {
        *rows = window_size.ws_row;
        *cols = window_size.ws_col;
    }
    else {
        return ERR_IO_CONTROL;
    }
    return OK;
}

int mt_setfgcolor(Terminal_colors_t color) {
    if(color < clr_black || color > clr_default){
        return ERR_SCREEN_COLOR;
    }
    char buf[15];
    sprintf(buf, "\E[3%dm", color);
    if (write(STDOUT_FILENO, buf, strlen(buf)) == -1) {
        return ERR_PRINT;
    }
    return OK;
}

int mt_setbgcolor(Terminal_colors_t color) {
    if(color < clr_black || color > clr_default){
        return ERR_SCREEN_COLOR;
    }
    char buf[15];
    sprintf(buf, "\E[4%dm", color);
    if (write(STDOUT_FILENO, buf, strlen(buf)) == -1) {
        return ERR_PRINT;
    }
    return OK;
}
