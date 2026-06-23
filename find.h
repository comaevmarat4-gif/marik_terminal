#ifndef FIND_H
#define FIND_H
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
static inline void my_find(const char *dir_path, const char *target_name) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        return;
    }
    struct dirent *entry;
    struct stat statbuf;
    char path[1024];
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);
        if (stat(path, &statbuf) == -1) {
            continue;
        }
        if (strstr(entry->d_name, target_name) != NULL) {
            printf("%s\n", path);
        }
        if (S_ISDIR(statbuf.st_mode)) {
            my_find(path, target_name);
        }
    }
    closedir(dir);
}
#endif