#ifndef LS_H
#define LS_H
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
static inline bool ls_dir(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("ls: Ошибка открытия каталога");
        return false;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.' && (entry->d_name[1] == '\0' || 
           (entry->d_name[1] == '.' && entry->d_name[2] == '\0'))) {
            continue;
        }
        printf("%s  ", entry->d_name);
    }
    printf("\n");
    closedir(dir);
    return true;
}
#endif