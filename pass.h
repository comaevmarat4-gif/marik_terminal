#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
void pass() {
    int length;
    printf("password length: ");
    scanf("%d", &length);
    char* password = malloc(length + 1);-
    if (password == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    char* upper = "QWERTYUIOPASDFGHJKLZXCVBNM";
    char* lower = "qwertyuiopasdfghjklzxcvbnm";
    char* num = "0123456789";
    char* symbol = "<>?/,.~`()_+!@#$%^&*=-|"; 
    int upper_length = strlen(upper);
    int lower_length = strlen(lower);
    int num_length = strlen(num);
    int symbol_length = strlen(symbol);
    srand(time(NULL) * getpid());
    for (int i = 0; i < length; i++) {
        int c_type = rand() % 4;
        if (c_type == 0) {
            password[i] = num[rand() % num_length];
        } else if (c_type == 1) {
            password[i] = lower[rand() % lower_length];
        } else if (c_type == 2) {
            password[i] = upper[rand() % upper_length];
        } else {
            password[i] = symbol[rand() % symbol_length];
        }
    }
    password[length] = '\0'; 
    printf("%s\n", password);
    free(password);
}