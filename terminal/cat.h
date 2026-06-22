#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <stdio.h>
#include <stdbool.h>
static inline bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }
    return false;
}
static inline bool cat_file(const char *filename) {
    if (!file_exists(filename)) {
        fprintf(stderr, "cat: %s: Нет такого файла или каталога\n", filename);
        return false;
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("cat: Ошибка открытия файла");
        return false;
    }
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
    return true;
}
#endif