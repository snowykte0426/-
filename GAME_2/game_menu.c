#include "superclass.h"
#include "db_event.h"

void Gamemenu(char id[]) {
    recall:
    while (true) {
        ASCII_Art_print();
        CursorView(0);
        int x = 48, y = 16;
        gotoxy(x, y);
        printf("> ���� �����ϱ�");
        gotoxy(x + 2, y + 1);
        printf("���� �̾��ϱ�");
        gotoxy(x + 4, y + 2);
        printf("�α׾ƿ�");
        gotoxy(x + 6, y + 3);
        printf("����");
        while (true) {
            int n = KeyControl();
            switch (n) {
            case UP:
                gotoxy(x, y);
                printf(" ");
                if (y > 16) {
                    y--;
                }
                else {
                    y = 19;
                }
                gotoxy(x, y);
                printf(">");
                break;
            case DOWN:
                gotoxy(x, y);
                printf(" ");
                if (y < 19) {
                    y++;
                }
                else {
                    y = 16;
                }
                gotoxy(x, y);
                printf(">");
                break;
            case SUBMIT:
                system("cls");
                if (y == 16) {
                    new_game_reconfirm(id);
                    return;
                }
                else if (y == 17) {
                    save_check(id);
                    system("cls");
                    goto recall;
                }
                else if (y == 18) {
                    main();
                    return;
                }
                else if (y == 19) {
                    program_off();
                    system("cls");
                    goto recall;
                }
            default:
                break;
            }
        }
    }
}