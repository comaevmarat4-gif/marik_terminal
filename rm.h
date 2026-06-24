#include <stdio.h>
#include <unistd.h>
void remuv(const char *filename) {
    if (unlink(filename) == 0) {
        printf("Файл %s удален.\n", filename);
    } else {
        perror("Ошибка удаления"); 
    }
}