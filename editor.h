#ifndef EDITOR_H
#define EDITOR_H
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
static void disable_raw_mode(struct termios *orig) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig);
}
static void enable_raw_mode(struct termios *orig) {
    tcgetattr(STDIN_FILENO, orig);
    struct termios raw = *orig;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
static void start_editor(const char *filename) {
    struct termios orig;
    enable_raw_mode(&orig);
    char buf[1024] = {0};
    int pos = 0;
    char c;
    printf("\033[2J\033[H");
    printf("--- Редактор: %s (Ctrl+E - сохранить и выйти) ---\n", filename);
    fflush(stdout);
    while (read(STDIN_FILENO, &c, 1) == 1) {
        if (c == 5) break; // Ctrl+Q

        if (c == 27) { 
            char seq[3];
            if (read(STDIN_FILENO, &seq[0], 1) && read(STDIN_FILENO, &seq[1], 1)) {
                if (seq[0] == '[') {
                    if (seq[1] == 'D' && pos > 0) { 
                        printf("\b"); 
                        pos--; 
                    } else if (seq[1] == 'C' && buf[pos] != 0) { 
                        printf("%c", buf[pos++]); 
                    }
                    fflush(stdout); 
                }
            }
        } else if (c == 127) { 
            if (pos > 0) {
                pos--;
                buf[pos] = 0;
                printf("\b \b"); 
                fflush(stdout); 
            }
        } else if (pos < 1023) {
            buf[pos++] = c;
            printf("%c", c);
            fflush(stdout); 
        }
    }
    FILE *f = fopen(filename, "w");
    if (f) { fprintf(f, "%s", buf); fclose(f); }
    disable_raw_mode(&orig);
    printf("\nФайл сохранен.\n");
}
#endif