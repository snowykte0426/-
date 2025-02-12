﻿#include "superclass.h"
#include "superclass.h"
#include "db_event.h"

#pragma comment(lib, "libmariadb.lib")

void new_game_reconfirm(char id[]) {
    system("cls");
    gotoxy(46, 12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    printf("정말 게임을 새로 시작하시겠습니까?");
    gotoxy(43, 13);
    printf("[기존의 세이브파일이 있다면 삭제됩니다]");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    int x = 49, y = 15;
    gotoxy(49, 15);
    printf("> 예");
    gotoxy(68, 15);
    printf("아니요");
    while (true) {
        int n = KeyControl();
        switch (n) {
        case RIGHT: {
            gotoxy(x, y);
            printf(" ");
            if (x >= 49 && x < 66) {
                x = 66;
            }
            else {
                x = 49;
            }
            gotoxy(x, y);
            printf(">");
            break;
        }
        case LEFT: {
            gotoxy(x, y);
            printf(" ");
            if (x == 66) {
                x = 49;
            }
            else {
                x = 66;
            }
            gotoxy(x, y);
            printf(">");
            break;
        }
        case SUBMIT: {
            system("cls");
            if (x == 49) {
                gender_select(id);
                return;
            }
            else if (x == 66) {
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
    gotoxy(49, 12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    printf("주인공의 성별을 정해주세요");
    gotoxy(43, 13);
    printf("[성별에 따라 스토리가 바뀔 수 있습니다]");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    int x = 49, y = 15;
    gotoxy(49, 15);
    printf("> 남");
    gotoxy(70, 15);
    printf("여");
    char query[255];
    while (true) {
        int n = KeyControl();
        switch (n) {
        case RIGHT: {
            gotoxy(x, y);
            printf(" ");
            if (x == 49) {
                x = 68;
            }
            else {
                x = 49;
            }
            gotoxy(x, y);
            printf(">");
            break;
        }
        case LEFT: {
            gotoxy(x, y);
            printf(" ");
            if (x == 68) {
                x = 49;
            }
            else {
                x = 68;
            }
            gotoxy(x, y);
            printf(">");
            break;
        }
        case SUBMIT: {
            system("cls");
            if (x == 49) {
                sprintf(query, "UPDATE gwangju_sword_master.account SET gender = 'male' WHERE id = '%s'", id);
                if (mysql_query(&db, query)) {
                    db_query_error(&db);
                }
                else {
                    prologue(1, id, &db);
                }
                mysql_close(&db);
                return;
            }
            else if (x == 68) {
                sprintf(query, "UPDATE gwangju_sword_master.account SET gender = 'female' WHERE id = '%s'", id);
                if (mysql_query(&db, query)) {
                    db_query_error(&db);
                }
                else {
                    prologue(2, id, &db);
                }
                mysql_close(&db);
                return;
            }
            else {
                setRGBColor(255, 0, 0);
                printf("Gender Select Error\n");
                resetColor();
                mysql_close(&db);
                exit(1);
            }
            break;
        }
        default:
            break;
        }
    }
    mysql_close(&db);
    exit(1);
}

void BufferingEffect(int x, int y) {
    const char* symbols[] = { "|", "/", "-", "\\", "|" };
    int symbol_count = sizeof(symbols) / sizeof(symbols[0]);
    short random = rand() % 5;
    int total_steps = 5 + random;
    for (int i = 0; i < total_steps; i++) {
        gotoxy(x, y);
        printf("%s", symbols[i % symbol_count]);
        Sleep(200);
    }
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
    if (!row || !row[0] || (strcmp(row[0], "0") == 0 || strcmp(row[0], "false") == 0)) {
        gotoxy(45, 13);
        printf("현재 계정에 세이브파일이 없습니다!");
        Sleep(3000);
        system("cls");
        Program_config();
        return;
    }
    else if (row && row[0] && (strcmp(row[0], "1") == 0 || strcmp(row[0], "true") == 0)) {
        unsigned int line = 0;
        const char* text = "세이브파일이 조회되었습니다\n불러오는 중... |";
        int console_width = get_console_width();
        gotoxy(0, 10);
        int buffer_x = -1, buffer_y = -1;
        for (unsigned int i = 0; i < strlen(text); i++) {
            if (text[i] == '\n') {
                line++;
                gotoxy(0, 10 + line);
            }
            else {
                if (i == 0 || text[i - 1] == '\n') {
                    int line_length = 0;
                    unsigned int j = i;
                    while (j < strlen(text) && text[j] != '\n') {
                        line_length++;
                        j++;
                    }
                    int current_x = (console_width - line_length) / 2;
                    gotoxy(current_x, 10 + line);
                }
                printf("%c", text[i]);
                if (text[i] == '|') {
                    int line_length = 0;
                    for (int k = i - 1; k >= 0 && text[k] != '\n'; k--) {
                        line_length++;
                    }
                    buffer_x = (console_width - line_length) / 2 + line_length;
                    buffer_y = 10 + line;
                }
            }
        }
        if (buffer_x != -1 && buffer_y != -1) {
            BufferingEffect(buffer_x, buffer_y);
        }
        memset(q, 0, sizeof(q));
        sprintf(q, "SELECT stage, mop_num FROM gwangju_sword_master.account WHERE id = '%s'", id);
        if (mysql_query(&db, q)) {
            db_query_error(&db);
            exit(0);
        }
        result = mysql_store_result(&db);
        row = mysql_fetch_row(result);
        if (row && row[0] && row[1]) {
            int stage = atoi(row[0]);
            int mop_num = atoi(row[1]);
            mop_num--;
            if (mop_num == 0) {
                mop_num = 1;
            }
            if (mop_num > 0) {
                mop_num = abs(mop_num);
            }
            if (stage < 22) {
                system("cls");
                Reline();
                Resetcount_Print(id);
                if (stage == 1) {
                    stage_1(id, mop_num);
                }
                else if (stage == 2) {
                    stage_2(id, mop_num);
                }
                else if (stage == 3) {
                    stage_3(id, mop_num);
                }
                else if (stage == 4) {
                    stage_4(id, mop_num);
                }
                else if (stage == 5) {
                    final_stage(id, mop_num);
                }
                else {
                    setRGBColor(255, 0, 0);
                    printf("Stage is NULL\n");
                    resetColor();
                    exit(1);
                }
            }
        }
        else {
            gotoxy(45, 13);
            printf("세이브파일을 불러오는 중 오류가 발생했습니다!");
            Sleep(3000);
            system("cls");
            Program_config();
        }
        mysql_free_result(result);
        mysql_close(&db);
        Sleep(3000);
        return;
    }
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
    bool sync = false;
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
        const char* text = "당신은 헤네시스왕국의 기사입니다.\n"
            "평화롭던 왕국에 그란디스라는 악마가 찾아와 공주를\n"
            "납치해 갔습니다. 당신은 나라의 부름을 받아 공주를 찾으러 던전에 찾아왔습니다.\n"
            "그 순간 당신에게 엄청난 능력이 생기는데.....";

        prologue_text = (char*)malloc(strlen(text) + 1);
        if (prologue_text == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        strcpy(prologue_text, text);
    }
    else if (gender == 2) {
        const char* text = "당신은 헤네시스왕국의 기사입니다.\n"
            "평화롭던 왕국에 그란디스라는 악마가 찾아와 왕자를\n"
            "납치해 갔습니다. 당신은 나라의 부름을 받아 왕자를 찾으러 던전에 찾아왔습니다.\n"
            "그 순간 당신에게 엄청난 능력이 생기는데.....";

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
            if (_kbhit()) {
                int key = KeyControl();
                if (key == Key_S) {
                    sync = true;
                    break;
                }
            }
            if (!sync) {
                Sleep(50);
            }
        }
        if (sync) {
            system("cls");
            line = 0;
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
            }
        }
    }
    final_y += line;
    free(prologue_text);
    gotoxy(45, final_y + 2);
    Sleep(1975);
    printf("계속하려면 Enter를 누르세요");
    CursorView(0);
    while (true) {
        int n = KeyControl();
        if (n == SUBMIT) {
            system("cls");
            memset(query, 0, sizeof(query));
            Remover_File();
            MYSQL db;
            mysql_init(&db);
            if (!mysql_real_connect(&db, "localhost", "root", "123456", "gwangju_sword_master", 0, NULL, 0)) {
                gotoxy(42, 12);
                db_connect_error(&db);
                exit(0);
            }
            sprintf(query, "UPDATE gwangju_sword_master.account SET save_file = 1 WHERE id = '%s'", id);
            if (mysql_query(&db, query)) {
                db_query_error(&db);
                exit(0);
            }
            memset(query, 0, sizeof(query));
            sprintf(query, "UPDATE gwangju_sword_master.user_state SET level=1,hp=100,max_hp=100,mp=100,max_mp=100,speed=10,attack=5,defense=5,cri_chance=5,good_and_evil=0,levelup_requirement=150,levelup_point=0 WHERE id = '%s'", id);
            if (mysql_query(&db, query)) {
                db_query_error(&db);
                exit(0);
            }
            memset(query, 0, sizeof(query));
            sprintf(query, "DELETE FROM gwangju_sword_master.effect WHERE id = '%s'", id);
            if (mysql_query(&db, query)) {
                db_query_error(&db);
                exit(0);
            }
            memset(query, 0, sizeof(query));
            sprintf(query, "UPDATE gwangju_sword_master.account SET reset_count = 0 WHERE id = '%s'", id);
            if (mysql_query(&db, query)) {
                db_query_error(&db);
                exit(0);
            }
            mysql_close(&db);
            outline(id);
            break;
        }
        else {
            continue;
        }
    }
    system("cls");
}