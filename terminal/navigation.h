#ifndef NAVIGATION_H
#define NAVIGATION_H
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#define MAX_PATH_SIZE 1024
static inline void print_help(void) {
    printf("\n--- Доступные команды терминала ---\n");
    printf("  ls             - Показать список файлов в текущей папке\n");
    printf("  cat <файл>     - Вывести содержимое файла на экран\n");
    printf("  cd <папка>     - Перейти в другую папку\n");
    printf("  help           - Показать это справочное сообщение\n");
    printf("  exit           - Выйти из терминала\n");
    printf("-----------------------------------\n\n");
}
static inline bool change_dir(const char *path) {
    if (path == NULL || path[0] == '\0') {
        fprintf(stderr, "cd: пропущен аргумент\n");
        return false;
    }
    if (chdir(path) != 0) {
        perror("cd: Ошибка перехода");
        return false;
    }
    return true;
}
static inline void print_prompt(void) {
    char cwd[MAX_PATH_SIZE];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s> ", cwd);
    } else {
        printf("terminal> ");
    }
    fflush(stdout);
}
#endif 
