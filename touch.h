#include <stdio.h>
void my_touch(const char* fname) {
	FILE* f = fopen(fname, "a");
	if(f) {
		fclose(f);
	} else {
		printf("Не удалось создать файл %s\n", fname);
	}
}