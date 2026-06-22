#include <stdio.h>
static inline void clear_screen(void){
    printf("\e[2J\e[H");
    fflush(stdout);
}
