#include "superclass.h"

void info_area(void);

void outline(char id[]) {
    Program_config();
    for (int i = 0; i < 120; i++) {
        printf("��");
    }
    puts("");
    for (int i = 1; i <= 28; i++) {
        printf("��");
        for (int j = 0; j < 118; j++) {
            printf(" ");
        }
        printf("��\n");
    }
    for (int i = 0; i < 120; i++) {
        printf("��");
    }
    puts("");
    info_area();
    exit(1);
}

void info_area(void) {
    int y = 0;
    for (int i = 0; i < 29; i++) {
        gotoxy(30, y + i);
        printf("��");
    }
    puts("");
}
