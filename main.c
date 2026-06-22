#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "cat.h"
#include "ls.h"
#include "navigation.h"
#include "clear.h"
#define MAX_INPUT_SIZE 1024
int main(void) {
    char input[MAX_INPUT_SIZE];
    char command[MAX_INPUT_SIZE];
    char argument[MAX_INPUT_SIZE];
    printf("Добро пожаловать в С-Терминал!\n");
    printf("Введите 'help' для просмотра списка доступных команд.\n\n");
    while (true) {
        print_prompt(); 
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; 
        }
		command[0] = '\0';
        argument[0] = '\0';
        int parsed = sscanf(input, "%s %s", command, argument);
        if (parsed <= 0) {
            continue;
        }
        if (strcmp(command, "exit") == 0) {
            printf("Выход из терминала. До свидания!\n");
            break;
        } 
        else if (strcmp(command, "help") == 0) {
            print_help();
        } 
        else if (strcmp(command, "ls") == 0) {
            
            ls_dir(parsed > 1 ? argument : ".");
        } 
        else if (strcmp(command, "cat") == 0) {
            if (parsed < 2) {
                fprintf(stderr, "Ошибка: укажите имя файла (пример: cat text.txt)\n");
            } else {
                cat_file(argument);
            }
        } 
        else if (strcmp(command, "cd") == 0) {
            if (parsed < 2) {
                fprintf(stderr, "Ошибка: укажите путь (пример: cd папка)\n");
            } else {
                change_dir(argument);
			}
        } 
		else if(strcmp(command, "clear") == 0) {
			clear_screen();
		}
        else {
            fprintf(stderr, "Команда '%s' не найдена. Введите 'help' для справки.\n", command);
        }
    }

    return 0;
}
