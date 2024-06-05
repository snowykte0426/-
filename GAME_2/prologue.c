#include "superclass.h"
#include "superclass.h"
#include "db_event.h"

#pragma comment(lib, "libmariadb.lib")

void new_game_reconfirm(char id[]) {
    system("cls");
    gotoxy(42, 12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    printf("���� ������ ���� �����Ͻðڽ��ϱ�?");
    gotoxy(39, 13);
    printf("[������ ���̺������� �ִٸ� �����˴ϴ�]");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    int x = 45, y = 15;
    gotoxy(45, 15);
    printf("> ��");
    gotoxy(64, 15);
    printf("�ƴϿ�");
    while (true) {
        int n = KeyControl();
        switch (n) {
        case RIGHT: {
            gotoxy(x, y);
            printf(" ");
            if (x >= 45 && x < 62) {
                x = 62;
            }
            else {
                x = 45;
            }
            gotoxy(x, y);
            printf(">");
            break;
        }
        case LEFT: {
            gotoxy(x, y);
            printf(" ");
            if (x == 62) {
                x = 45;
            }
            else {
                x = 62;
            }
            gotoxy(x, y);
            printf(">");
            break;
        }
        case SUBMIT: {
            system("cls");
            if (x == 45) {
                gender_select(id);
                return;
            }
            else if (x == 62) {
                Gamemenu(id);
                return;
            }
        }
        default:
            break;
        }
    }

    exit(1);
}

void gender_select(char id[]) {
    MYSQL db;
    mysql_init(&db);
    if (!mysql_real_connect(&db, "localhost", "root", "123456", "gwangju_sword_master", 0, NULL, 0)) {
        gotoxy(42, 12);
        db_connect_error(&db);
        exit(0);
    }
    system("cls");
    gotoxy(45, 12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    printf("���ΰ��� ������ �����ּ���");
    gotoxy(39, 13);
    printf("[������ ���� ���丮�� �ٲ� �� �ֽ��ϴ�]");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    int x = 45, y = 15;
    gotoxy(45, 15);
    printf("> ��");
    gotoxy(66, 15);
    printf("��");
    char query[255];
    while (true) {
        int n = KeyControl();
        switch (n) {
        case RIGHT: {
            gotoxy(x, y);
            printf(" ");
            if (x >= 45 && x < 63) {
                x = 64;
            }
            else {
                x = 45;
            }
            gotoxy(x, y);
            printf(">");
            break;
        }
        case LEFT: {
            gotoxy(x, y);
            printf(" ");
            if (x == 64) {
                x = 45;
            }
            else {
                x = 64;
            }
            gotoxy(x, y);
            printf(">");
            break;
        }
        case SUBMIT: {
            system("cls");
            if (x == 45) {
                sprintf(query, "UPDATE gwangju_sword_master.account SET gender = 'male' WHERE id = '%s'", id);
                if (mysql_query(&db, query)) {
                    db_query_error(&db);
                }
                prologue(1, id, &db);
                mysql_close(&db);
                return;
            }
            else if (x == 64) {
                sprintf(query, "UPDATE gwangju_sword_master.account SET gender = 'female' WHERE id = '%s'", id);
                if (mysql_query(&db, query)) {
                    db_query_error(&db);
                }
                prologue(2, id, &db);
                mysql_close(&db);
                return;
            }
        }
        default:
            break;
        }
    }
    mysql_close(&db);
    exit(1);
}

void save_check(char id[]) {
    MYSQL db;
    mysql_init(&db);
    if (!mysql_real_connect(&db, "localhost", "root", "123456", "board", 0, NULL, 0)) {
        db_connect_error(&db);
        exit(0);
    }
    char q[255];
    sprintf(q, "SELECT save_file FROM gwangju_sword_master.account WHERE id = '%s'", id);
    if (mysql_query(&db, q)) {
        db_query_error(&db);
        exit(0);
    }
    MYSQL_RES* result = mysql_store_result(&db);
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == 0 || row == '0' || strcmp(row, "false")) {
        gotoxy(45, 15);
        printf("���� ������ ���̺������� �����ϴ�!");
        Sleep(3000);
        system("cls");
        Program_config();
    }
    else if (row == 1 || row == '1' || row == "true") {
        //���� �̾��ϱ� ��� ����
    }
    return;
}

int get_console_width(void) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width = 0;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return width;
}

void prologue(short gender, char id[], MYSQL* conn) {
    char query[255];
    memset(query, 0, sizeof(query));
    sprintf(query, "UPDATE gwangju_sword_master.account SET stage = 0 WHERE id = '%s'", id);
    if (mysql_ping(conn) != 0) {
        if (!mysql_real_connect(conn, "localhost", "root", "123456", "gwangju_sword_master", 0, NULL, 0)) {
            db_connect_error(conn);
            exit(0);
        }
    }
    if (mysql_query(conn, query)) {
        db_query_error(conn);
        exit(0);
    }
    char* prologue_text = NULL;
    unsigned int line = 0, final_y = 10;
    if (gender == 1) {
        const char* text = "����� ��׽ý��ձ��� ����Դϴ�.\n"
            "��ȭ�Ӵ� �ձ��� �׶��𽺶�� �Ǹ��� ã�ƿ� ���ָ�\n"
            "��ġ�� �����ϴ�. ����� ������ �θ��� �޾� ���ָ� ã���� ������ ã�ƿԽ��ϴ�.\n"
            "�� ���� ��ſ��� ��û�� �ɷ��� ����µ�.....";

        prologue_text = (char*)malloc(strlen(text) + 1);
        if (prologue_text == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        strcpy(prologue_text, text);
    }
    else if (gender == 2) {
        const char* text = "����� ��׽ý��ձ��� ����Դϴ�.\n"
            "��ȭ�Ӵ� �ձ��� �׶��𽺶�� �Ǹ��� ã�ƿ� ���ڸ�\n"
            "��ġ�� �����ϴ�. ����� ������ �θ��� �޾� ���ڸ� ã���� ������ ã�ƿԽ��ϴ�.\n"
            "�� ���� ��ſ��� ��û�� �ɷ��� ����µ�.....";

        prologue_text = (char*)malloc(strlen(text) + 1);
        if (prologue_text == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            Sleep(3000);
            exit(1);
        }
        strcpy(prologue_text, text);
    }
    if (prologue_text) {
        int console_width = get_console_width();
        int current_x;
        gotoxy(0, 10);
        for (unsigned int i = 0; i < strlen(prologue_text); i++) {
            if (prologue_text[i] == '\n') {
                line++;
                gotoxy(0, 10 + line);
            }
            else {
                if (i == 0 || prologue_text[i - 1] == '\n') {
                    int line_length = 0;
                    unsigned int j = i;
                    while (j < strlen(prologue_text) && prologue_text[j] != '\n') {
                        line_length++;
                        j++;
                    }
                    current_x = (console_width - line_length) / 2;
                    gotoxy(current_x, 10 + line);
                }
                printf("%c", prologue_text[i]);
            }
            Sleep(50);
        }
        final_y += line;
        free(prologue_text);
    }
    gotoxy(45, final_y + 2);
    Sleep(1975);
    printf("����Ϸ��� Enter�� ��������");
    CursorView(0);
    while (true) {
        int n = KeyControl();
        if (n == SUBMIT) {
            system("cls");
            outline(id);
            break;
        }
        else {
            continue;
        }
    }
    system("cls");
}