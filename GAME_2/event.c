#include "superclass.h"

void Health_Club_conn(char id[]) {
    memset(string, 0, sizeof(string));
    unsigned int line = 0;
    unsigned int final_y = 2;
    memset(string, 0, sizeof(string));
    char text[100] = "�ｺ���� �߰��ߴ�!";
    int console_width = 120 - 32 + 1;
    int console_height = 17 - 2 + 1;
    int start_x = 32;
    int start_y = 2;
    unsigned int text_length = strlen(text);
    unsigned int i = 0;
    while (i < text_length) {
        int current_x = start_x;
        int current_y = start_y + line;
        int line_length = 0;
        while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
            line_length++;
        }
        current_x = start_x + (console_width - line_length) / 2;
        gotoxy(current_x, current_y);
        for (int j = 0; j < line_length; j++) {
            printf("%c", text[i + j]);
            fflush(stdout);
            Sleep(50);
        }
        i += line_length;
        if (text[i] == '\n') {
            i++;
        }
        line++;
        if (line >= console_height) {
            break;
        }
    }
    final_y = start_y + line;
    int message_x = start_x + (console_width - 27) / 2;
    gotoxy(message_x - 3, final_y + 4);
    Sleep(775);
    printf("> ������ ���         ���׸ӽ��� ź��");
    CursorView(0);
    int n, x = 60, y = final_y + 4;
    gotoxy(x, y);
    printf(">");

    while (true) {
        n = KeyControl();
        switch (n) {
        case RIGHT: {
            gotoxy(x, y);
            printf(" ");
            x = (x == 60) ? 80 : 60;
            gotoxy(x, y);
            printf(">");
            break;
        }
        case LEFT: {
            gotoxy(x, y);
            printf(" ");
            x = (x == 80) ? 60 : 81;
            gotoxy(x, y);
            printf(">");
            break;
        }
        case SUBMIT: {
            Clear_Gamelog();
            if (x == 60) {
                MYSQL db;
                connect_to_db(&db);
                char q[255];
                Clear_Gamelog();
                line = 0;
                final_y = 2;
                line = 0;
                final_y = 2;
                memset(text, 0, sizeof(text));
                int compare = rand() % 100;
                int cap = rand() % 30;
                if (cap > compare) {
                    char text[100] = "������ ����������!!!";
                    console_width = 120 - 32 + 1;
                    console_height = 17 - 2 + 1;
                    start_x = 32;
                    start_y = 2;
                    text_length = strlen(text);
                    i = 0;
                    while (i < text_length) {
                        int current_x = start_x;
                        int current_y = start_y + line;
                        int line_length = 0;
                        while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
                            line_length++;
                        }
                        current_x = start_x + (console_width - line_length) / 2;
                        gotoxy(current_x, current_y);
                        for (int j = 0; j < line_length; j++) {
                            printf("%c", text[i + j]);
                            fflush(stdout);
                            Sleep(50);
                        }
                        i += line_length;
                        if (text[i] == '\n') {
                            i++;
                        }
                        line++;
                        if (line >= console_height) {
                            break;
                        }
                        Sleep(48);
                    }
                    sprintf(q, "UPDATE gwangju_sword_master.user_state SET attack=attack+10,defense=defense+5 WHERE id = '%s'", id);
                    if (mysql_query(&db, q)) {
                        db_query_error(&db);
                        mysql_close(&db);
                        exit(0);
                    }
                    final_y = start_y + line;
                    int message_x = start_x + (console_width - 27) / 2;
                    gotoxy(message_x + 3, final_y + 4);
                    Sleep(575);
                    setRGBColor(0, 255, 0);
                    printf("[���ݷ��� 10 �����ߴ�]");
                    resetColor();
                    Sleep(48);
                    mysql_close(&db);
                    Sleep(2000);
                    return;
                }
                else {
                    char text[100] = "�������� �ｺ���� �ΰ����� ��������...";
                    console_width = 120 - 32 + 1;
                    console_height = 17 - 2 + 1;
                    start_x = 32;
                    start_y = 2;
                    text_length = strlen(text);
                    i = 0;
                    while (i < text_length) {
                        int current_x = start_x;
                        int current_y = start_y + line;
                        int line_length = 0;
                        while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
                            line_length++;
                        }
                        current_x = start_x + (console_width - line_length) / 2;
                        gotoxy(current_x, current_y + 3);
                        for (int j = 0; j < line_length; j++) {
                            printf("%c", text[i + j]);
                            fflush(stdout);
                            Sleep(50);
                        }
                        i += line_length;
                        if (text[i] == '\n') {
                            i++;
                        }
                        line++;
                        if (line >= console_height) {
                            break;
                        }
                    }
                    final_y = start_y + line;
                    int message_x = start_x + (console_width - 27) / 2;
                    gotoxy(message_x + 1, final_y + 4);
                    Sleep(575);
                    sprintf(q, "UPDATE gwangju_sword_master.user_state SET attack = attack - 5 WHERE id = '%s'", id);
                    connect_to_db(&db);
                    if (mysql_query(&db, q)) {
                        db_query_error(&db);
                        mysql_close(&db);
                        exit(0);
                    }
                    setRGBColor(255, 0, 0);
                    printf("[���ݷ��� 5 �����ߴ�]");
                    resetColor();
                    Sleep(1988);
                    memset(q, 0, sizeof(q));
                    mysql_close(&db);
                    return;
                }
            }
            else {
                MYSQL db;
                connect_to_db(&db);
                char q[255];
                Clear_Gamelog();
                line = 0;
                final_y = 2;
                line = 0;
                final_y = 2;
                memset(text, 0, sizeof(text));
                int compare = rand() % 100;
                int cap = rand() % 30;
                if (cap > compare) {
                    char text[100] = "���� �� ���ذ� �޸� �� �ִ�!";
                    console_width = 120 - 32 + 1;
                    console_height = 17 - 2 + 1;
                    start_x = 32;
                    start_y = 2;
                    text_length = strlen(text);
                    i = 0;
                    while (i < text_length) {
                        int current_x = start_x;
                        int current_y = start_y + line;
                        int line_length = 0;
                        while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
                            line_length++;
                        }
                        current_x = start_x + (console_width - line_length) / 2;
                        gotoxy(current_x, current_y);
                        for (int j = 0; j < line_length; j++) {
                            printf("%c", text[i + j]);
                            fflush(stdout);
                            Sleep(50);
                        }
                        i += line_length;
                        if (text[i] == '\n') {
                            i++;
                        }
                        line++;
                        if (line >= console_height) {
                            break;
                        }
                        Sleep(48);
                    }
                    sprintf(q, "UPDATE gwangju_sword_master.user_state SET speed=speed+10,defense=defense+5 WHERE id = '%s'", id);
                    if (mysql_query(&db, q)) {
                        db_query_error(&db);
                        mysql_close(&db);
                        exit(0);
                    }
                    final_y = start_y + line;
                    int message_x = start_x + (console_width - 27) / 2;
                    gotoxy(message_x + 1, final_y + 4);
                    Sleep(575);
                    setRGBColor(0, 255, 0);
                    printf("[ȸ�Ƿ��� 10%% �����ߴ�]");
                    resetColor();
                    Sleep(48);
                    mysql_close(&db);
                    Sleep(2000);
                    return;
                }
                else {
                    char text[100] = "�������� �ｺ���� �ΰ����� ��������...";
                    console_width = 120 - 32 + 1;
                    console_height = 17 - 2 + 1;
                    start_x = 32;
                    start_y = 2;
                    text_length = strlen(text);
                    i = 0;
                    while (i < text_length) {
                        int current_x = start_x;
                        int current_y = start_y + line;
                        int line_length = 0;
                        while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
                            line_length++;
                        }
                        current_x = start_x + (console_width - line_length) / 2;
                        gotoxy(current_x, current_y + 3);
                        for (int j = 0; j < line_length; j++) {
                            printf("%c", text[i + j]);
                            fflush(stdout);
                            Sleep(50);
                        }
                        i += line_length;
                        if (text[i] == '\n') {
                            i++;
                        }
                        line++;
                        if (line >= console_height) {
                            break;
                        }
                    }
                    final_y = start_y + line;
                    int message_x = start_x + (console_width - 27) / 2;
                    sprintf(q,"SELECT speed FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
                    if (mysql_query(&db, q)) {
						db_query_error(&db);
						mysql_close(&db);
						exit(0);
					}
                    MYSQL_RES* result = mysql_store_result(&db);
                    MYSQL_ROW row = mysql_fetch_row(result);
                    int speed = atoi(row[0]);
                    memset(q, 0, sizeof(q));
                    if (speed - 5 < 0) {
						sprintf(q, "UPDATE gwangju_sword_master.user_state SET speed = 0 WHERE id = '%s'", id);
					}
                    else {
                        sprintf(q, "UPDATE gwangju_sword_master.user_state SET speed = speed - 5 WHERE id = '%s'", id);
                    }
                    gotoxy(message_x + 2, final_y + 4);
                    Sleep(575);
                    if (mysql_query(&db, q)) {
                        db_query_error(&db);
                        mysql_close(&db);
                        exit(0);
                    }
                    setRGBColor(255, 0, 0);
                    printf("[ȸ�Ƿ��� 5%% �����ߴ�]");
                    resetColor();
                    Sleep(1988);
                    memset(q, 0, sizeof(q));
                    mysql_free_result(result);
                    mysql_close(&db);
                    return;
                }
                }
        }
        default: {
            continue;
        }
        }
    }
    return;
}

void Whisper_conn(char id[]) {
    memset(string, 0, sizeof(string));
    unsigned int line = 0;
    unsigned int final_y = 2;
    memset(string, 0, sizeof(string));
    char text[100] = "��� �޽��� ���ϴ� �� ����� �Ӱ��� �� �� ���� �Ҹ��� ����ɴϴ�...";
    int console_width = 120 - 32 + 1;
    int console_height = 17 - 2 + 1;
    int start_x = 32;
    int start_y = 2;
    unsigned int text_length = strlen(text);
    unsigned int i = 0;
    while (i < text_length) {
        int current_x = start_x;
        int current_y = start_y + line;
        int line_length = 0;
        while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
            line_length++;
        }
        current_x = start_x + (console_width - line_length) / 2;
        gotoxy(current_x, current_y);
        for (int j = 0; j < line_length; j++) {
            printf("%c", text[i + j]);
            fflush(stdout);
            Sleep(50);
        }
        i += line_length;
        if (text[i] == '\n') {
            i++;
        }
        line++;
        if (line >= console_height) {
            break;
        }
    }
    final_y = start_y + line;
    int message_x = start_x + (console_width - 27) / 2;
    gotoxy(message_x - 10, final_y + 4);
    Sleep(775);
    printf("> �͸� ����δ�         �����ϰ� �ῡ ���");
    CursorView(0);
    int n, x = 53, y = final_y + 4;
    gotoxy(x, y);
    printf(">");

    while (true) {
        n = KeyControl();
        switch (n) {
        case RIGHT: {
            gotoxy(x, y);
            printf(" ");
            x = (x == 53) ? 75 : 53;
            gotoxy(x, y);
            printf(">");
            break;
        }
        case LEFT: {
            gotoxy(x, y);
            printf(" ");
            x = (x == 75) ? 53 : 75;
            gotoxy(x, y);
            printf(">");
            break;
        }
        case SUBMIT: {
            Clear_Gamelog();
            if (x == 53) {
                MYSQL db;
                connect_to_db(&db);
                char q[255];
                Clear_Gamelog();
                line = 0;
                final_y = 2;
                line = 0;
                final_y = 2;
                memset(text, 0, sizeof(text));
                char text[100] = "���� ���ư��� ���� ��ġ����.....";
                console_width = 120 - 32 + 1;
                console_height = 17 - 2 + 1;
                start_x = 32;
                start_y = 2;
                text_length = strlen(text);
                i = 0;
                while (i < text_length) {
                    int current_x = start_x;
                    int current_y = start_y + line;
                    int line_length = 0;
                    while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
                        line_length++;
                    }
                    current_x = start_x + (console_width - line_length) / 2;
                    gotoxy(current_x, current_y);
                    for (int j = 0; j < line_length; j++) {
                        printf("%c", text[i + j]);
                        fflush(stdout);
                        Sleep(50);
                    }
                    i += line_length;
                    if (text[i] == '\n') {
                        i++;
                    }
                    line++;
                    if (line >= console_height) {
                        break;
                    }
                    Sleep(48);
                }
                sprintf(q, "UPDATE gwangju_sword_master.user_state SET good_and_evil = 1 WHERE id = '%s'", id);
                if (mysql_query(&db, q)) {
                    db_query_error(&db);
                    mysql_close(&db);
                    exit(0);
                }
                mysql_close(&db);
                Sleep(2000);
                return;
            }
            else {
                MYSQL db;
                char q[255];
                line = 0;
                final_y = 2;
                line = 0;
                final_y = 2;
                memset(text, 0, sizeof(text));
                char text[100] = "���� ���� ���";
                console_width = 120 - 32 + 1;
                console_height = 17 - 2 + 1;
                start_x = 32;
                start_y = 2;
                text_length = strlen(text);
                i = 0;
                while (i < text_length) {
                    int current_x = start_x;
                    int current_y = start_y + line;
                    int line_length = 0;
                    while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
                        line_length++;
                    }
                    current_x = start_x + (console_width - line_length) / 2;
                    gotoxy(current_x, current_y + 3);
                    for (int j = 0; j < line_length; j++) {
                        printf("%c", text[i + j]);
                        fflush(stdout);
                        Sleep(50);
                    }
                    i += line_length;
                    if (text[i] == '\n') {
                        i++;
                    }
                    line++;
                    if (line >= console_height) {
                        break;
                    }
                }
                final_y = start_y + line;
                int message_x = start_x + (console_width - 27) / 2;
                gotoxy(message_x + 5, final_y + 4);
                Sleep(575);
                sprintf(q, "SELECT hp, max_hp FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
                connect_to_db(&db);
                if (mysql_query(&db, q)) {
                    db_query_error(&db);
                    mysql_close(&db);
                    exit(0);
                }
                MYSQL_RES* result = mysql_store_result(&db);
                MYSQL_ROW row = mysql_fetch_row(result);
                int max_hp = atoi(row[1]);
                int hp = atoi(row[0]);
                if (hp + 25 > max_hp) {
                    hp = max_hp;
                }
                else {
                    hp += 25;
                }
                setRGBColor(0, 212, 0);
                printf("[HP�� ȸ���Ǿ���]");
                resetColor();
                Sleep(48);
                memset(q, 0, sizeof(q));
                sprintf(q, "UPDATE gwangju_sword_master.user_state SET good_and_evil = -1, hp = %d WHERE id = '%d'", hp, id);
                if (mysql_query(&db, q)) {
                    db_query_error(&db);
                    mysql_close(&db);
                    exit(0);
                }
                mysql_free_result(result);
                mysql_close(&db);
                Sleep(2000);
                return;
            }
        }
        default: {
            continue;
        }
        }
    }
    return;
}

void Heavy_Maichgun_conn(char id[]) {
    memset(string, 0, sizeof(string));
    unsigned int line = 0;
    unsigned int final_y = 2;
    memset(string, 0, sizeof(string));
    char text[100] = "�Ҿƹ����� ��տ� �����ִ�!";
    int console_width = 120 - 32 + 1;
    int console_height = 17 - 2 + 1;
    int start_x = 32;
    int start_y = 2;
    unsigned int text_length = strlen(text);
    unsigned int i = 0;
    while (i < text_length) {
        int current_x = start_x;
        int current_y = start_y + line;
        int line_length = 0;
        while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
            line_length++;
        }
        current_x = start_x + (console_width - line_length) / 2;
        gotoxy(current_x, current_y);
        for (int j = 0; j < line_length; j++) {
            printf("%c", text[i + j]);
            fflush(stdout);
            Sleep(50);
        }
        i += line_length;
        if (text[i] == '\n') {
            i++;
        }
        line++;
        if (line >= console_height) {
            break;
        }
    }
    final_y = start_y + line;
    int message_x = start_x + (console_width - 27) / 2;
    gotoxy(message_x - 6, final_y + 4);
    Sleep(775);
    printf("> Ǯ���ش�         �����ϰ� ����ģ��");
    CursorView(0);
    int n, x = 57, y = final_y + 4;
    gotoxy(x, y);
    printf(">");

    while (true) {
        n = KeyControl();
        switch (n) {
        case RIGHT: {
            gotoxy(x, y);
            printf(" ");
            x = (x == 57) ? 74 : 57;
            gotoxy(x, y);
            printf(">");
            break;
        }
        case LEFT: {
            gotoxy(x, y);
            printf(" ");
            x = (x == 74) ? 57 : 74;
            gotoxy(x, y);
            printf(">");
            break;
        }
        case SUBMIT: {
            Clear_Gamelog();
            if (x == 57) {
                MYSQL db;
                connect_to_db(&db);
                char q[255];
                Clear_Gamelog();
                line = 0;
                final_y = 2;
                line = 0;
                final_y = 2;
                memset(text, 0, sizeof(text));
                char text[100] = "'Heavy Machinegun'�̶�� ���� ���� ������ �ְ� ��������...";
                console_width = 120 - 32 + 1;
                console_height = 17 - 2 + 1;
                start_x = 32;
                start_y = 2;
                text_length = strlen(text);
                i = 0;
                while (i < text_length) {
                    int current_x = start_x;
                    int current_y = start_y + line;
                    int line_length = 0;
                    while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
                        line_length++;
                    }
                    current_x = start_x + (console_width - line_length) / 2;
                    gotoxy(current_x, current_y);
                    for (int j = 0; j < line_length; j++) {
                        printf("%c", text[i + j]);
                        fflush(stdout);
                        Sleep(50);
                    }
                    i += line_length;
                    if (text[i] == '\n') {
                        i++;
                    }
                    line++;
                    if (line >= console_height) {
                        break;
                    }
                    Sleep(48);
                }
                final_y = start_y + line;
                memset(q, 0, sizeof(q));
                sprintf(q,"SELECT attack FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
                if (mysql_query(&db, q)) {
                    db_query_error(&db);
                    mysql_close(&db);
                    sleep(2000);
                    exit(0);
                }
                MYSQL_RES* result = mysql_store_result(&db);
                MYSQL_ROW row = mysql_fetch_row(result);
                int attack = atoi(row[0]);
                int gangshin_ack = 3 * attack / 100;
                int message_x = start_x + (console_width - 27) / 2;
                gotoxy(message_x + 3, final_y + 4);
                Sleep(575);
                setRGBColor(0, 212, 0);
                printf("[���ݷ��� 3%% �����ߴ�]");
                resetColor();
                Sleep(48);
                memset(q, 0, sizeof(q));
                sprintf(q, "UPDATE gwangju_sword_master.user_state SET good_and_evil=good_and_evil+1,attack=attack+%d WHERE id = '%s'", gangshin_ack, id);
                if (mysql_query(&db, q)) {
                    db_query_error(&db);
                    mysql_free_result(result);
                    mysql_close(&db);
                    exit(0);
                }
                mysql_free_result(result);
                mysql_close(&db);
                Sleep(3000);
                return;
            }
            else {
                MYSQL db;
                char q[255];
                line = 0;
                final_y = 2;
                line = 0;
                final_y = 2;
                memset(text, 0, sizeof(text));
                char text[100] = "�ڿ��� �Ѽ��� ���...�´�?\n"
                    "�Ѿ��� ���ƿ� ������ ������ߴ�...";
                console_width = 120 - 32 + 1;
                console_height = 17 - 2 + 1;
                start_x = 32;
                start_y = 2;
                text_length = strlen(text);
                i = 0;
                while (i < text_length) {
                    int current_x = start_x;
                    int current_y = start_y + line;
                    int line_length = 0;
                    while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
                        line_length++;
                    }
                    current_x = start_x + (console_width - line_length) / 2;
                    gotoxy(current_x, current_y + 3);
                    for (int j = 0; j < line_length; j++) {
                        printf("%c", text[i + j]);
                        fflush(stdout);
                        Sleep(50);
                    }
                    i += line_length;
                    if (text[i] == '\n') {
                        i++;
                    }
                    line++;
                    if (line >= console_height) {
                        break;
                    }
                }
                final_y = start_y + line;
                int message_x = start_x + (console_width - 27) / 2;
                gotoxy(message_x + 5, final_y + 4);
                Sleep(575);
                sprintf(q, "SELECT hp, max_hp FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
                connect_to_db(&db);
                if (mysql_query(&db, q)) {
                    db_query_error(&db);
                    mysql_close(&db);
                    exit(0);
                }
                MYSQL_RES* result = mysql_store_result(&db);
                MYSQL_ROW row = mysql_fetch_row(result);
                int max_hp = atoi(row[1]);
                int hp = atoi(row[0]);
                if (hp + 25 > max_hp) {
                    hp = max_hp;
                }
                else {
                    hp += 25;
                }
                setRGBColor(249, 0, 0);
                printf("[HP�� 10 �Ҿ���]");
                resetColor();
                Sleep(48);
                memset(q, 0, sizeof(q));
                sprintf(q, "UPDATE gwangju_sword_master.user_state SET good_and_evil = good_and_evil-1, hp = hp-10 WHERE id = '%d'", id);
                if (mysql_query(&db, q)) {
                    db_query_error(&db);
                    mysql_close(&db);
                    exit(0);
                }
                mysql_free_result(result);
                mysql_close(&db);
                Sleep(2000);
                return;
            }
        }
        default: {
            continue;
        }
        }
    }
    return;
}

void Rooting_conn(char id[]) {
    memset(string, 0, sizeof(string));
    unsigned int line = 0;
    unsigned int final_y = 2;
    char text[100] = "�ռ� ���ư��� �Ǵٸ� ����� ��ü�� �ִ�...";
    int console_width = 120 - 32 + 1;
    int console_height = 17 - 2 + 1;
    int start_x = 32;
    int start_y = 2;
    unsigned int text_length = strlen(text);
    unsigned int i = 0;
    while (i < text_length) {
        int current_x = start_x;
        int current_y = start_y + line;
        int line_length = 0;
        while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
            line_length++;
        }
        current_x = start_x + (console_width - line_length) / 2;
        gotoxy(current_x, current_y);
        for (int j = 0; j < line_length; j++) {
            printf("%c", text[i + j]);
            fflush(stdout);
            Sleep(50);
        }
        i += line_length;
        if (text[i] == '\n') {
            i++;
        }
        line++;
        if (line >= console_height) {
            break;
        }
    }
    final_y = start_y + line;
    int message_x = start_x + (console_width - 27) / 2;
    gotoxy(message_x - 8, final_y + 4);
    Sleep(775);
    printf("> ��ü�� ������         ������ ������ش�");
    CursorView(0);
    int n, x = 55, y = final_y + 4;
    gotoxy(x, y);
    printf(">");
    while (true) {
        n = KeyControl();
        if (n == RIGHT || n == LEFT) {
            gotoxy(x, y);
            printf(" ");
            x = (x == 55) ? 77 : 55;
            gotoxy(x, y);
            printf(">");
        }
        else if (n == SUBMIT) {
            Clear_Gamelog();
            if (x == 55) {
                MYSQL db;
                connect_to_db(&db);
                char q[255];
                Clear_Gamelog();
                line = 0;
                final_y = 2;
                memset(text, 0, sizeof(text));
                strcpy(text, "��ü���� �������� ���� ���� ���Ѱ��� ������...");
                console_width = 120 - 32 + 1;
                console_height = 17 - 2 + 1;
                start_x = 32;
                start_y = 2;
                text_length = strlen(text);
                i = 0;
                while (i < text_length) {
                    int current_x = start_x;
                    int current_y = start_y + line;
                    int line_length = 0;
                    while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
                        line_length++;
                    }
                    current_x = start_x + (console_width - line_length) / 2;
                    gotoxy(current_x, current_y);
                    for (int j = 0; j < line_length; j++) {
                        printf("%c", text[i + j]);
                        fflush(stdout);
                        Sleep(50);
                    }
                    i += line_length;
                    if (text[i] == '\n') {
                        i++;
                    }
                    line++;
                    if (line >= console_height) {
                        break;
                    }
                    Sleep(48);
                }
                final_y = start_y + line;
                gotoxy(message_x + 3, final_y + 4);
                Sleep(575);
                setRGBColor(0, 212, 0);
                resetColor();
                Sleep(48);
                sprintf(q, "UPDATE gwangju_sword_master.user_state SET good_and_evil = good_and_evil - 1 WHERE id = '%s'", id);
                if (mysql_query(&db, q)) {
                    db_query_error(&db);
                    mysql_close(&db);
                    exit(0);
                }
                mysql_close(&db);
                Sleep(3000);
                return;
            }
            else {
                MYSQL db;
                char q[255];
                connect_to_db(&db);
                line = 0;
                final_y = 2;
                memset(text, 0, sizeof(text));
                strcpy(text, "����� ���� ǥ�ϸ� ���� �������.");
                console_width = 120 - 32 + 1;
                console_height = 17 - 2 + 1;
                start_x = 32;
                start_y = 2;
                text_length = strlen(text);
                i = 0;
                while (i < text_length) {
                    int current_x = start_x;
                    int current_y = start_y + line;
                    int line_length = 0;
                    while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
                        line_length++;
                    }
                    current_x = start_x + (console_width - line_length) / 2;
                    gotoxy(current_x, current_y + 3);
                    for (int j = 0; j < line_length; j++) {
                        printf("%c", text[i + j]);
                        fflush(stdout);
                        Sleep(50);
                    }
                    i += line_length;
                    if (text[i] == '\n') {
                        i++;
                    }
                    line++;
                    if (line >= console_height) {
                        break;
                    }
                }
                final_y = start_y + line;
                gotoxy(message_x + 5, final_y + 4);
                Sleep(575);
                setRGBColor(249, 0, 0);
                resetColor();
                Sleep(48);
                memset(q, 0, sizeof(q));
                sprintf(q, "UPDATE gwangju_sword_master.user_state SET good_and_evil = good_and_evil + 1 WHERE id = '%s'", id);
                if (mysql_query(&db, q)) {
                    db_query_error(&db);
                    mysql_close(&db);
                    Sleep(1420);
                    exit(0);
                }
                mysql_close(&db);
                Sleep(2000);
                return;
            }
        }
    }
    return;
}

void Mimic_conn(char id[]) {
    memset(string, 0, sizeof(string));
    unsigned int line = 0;
    unsigned int final_y = 2;
    char text[100] = "������ �߰��ߴ�!!";
    int console_width = 120 - 32 + 1;
    int console_height = 17 - 2 + 1;
    int start_x = 32;
    int start_y = 2;
    unsigned int text_length = strlen(text);
    unsigned int i = 0;
    while (i < text_length) {
        int current_x = start_x;
        int current_y = start_y + line;
        int line_length = 0;
        while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
            line_length++;
        }
        current_x = start_x + (console_width - line_length) / 2;
        gotoxy(current_x, current_y);
        for (int j = 0; j < line_length; j++) {
            printf("%c", text[i + j]);
            fflush(stdout);
            Sleep(50);
        }
        i += line_length;
        if (text[i] == '\n') {
            i++;
        }
        line++;
        if (line >= console_height) {
            break;
        }
    }
    final_y = start_y + line;
    int message_x = start_x + (console_width - 27) / 2;
    gotoxy(message_x - 2, final_y + 4);
    Sleep(775);
    printf("> �����         �����ϰ� ��������");
    CursorView(0);
    int n, x = 61, y = final_y + 4;
    gotoxy(x, y);
    printf(">");
    while (true) {
        n = KeyControl();
        if (n == RIGHT || n == LEFT) {
            gotoxy(x, y);
            printf(" ");
            x = (x == 61) ? 78 : 61;
            gotoxy(x, y);
            printf(">");
        }
        else if (n == SUBMIT) {
            Clear_Gamelog();
            if (x == 61) {
                MYSQL db;
                connect_to_db(&db);
                char q[255];
                Clear_Gamelog();
                line = 0;
                final_y = 2;
                memset(text, 0, sizeof(text));
                strcpy(text, "å������ ���� �̹��� Ƣ��Դ�!!!!....");
                console_width = 120 - 32 + 1;
                console_height = 17 - 2 + 1;
                start_x = 32;
                start_y = 2;
                text_length = strlen(text);
                i = 0;
                while (i < text_length) {
                    int current_x = start_x;
                    int current_y = start_y + line;
                    int line_length = 0;
                    while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
                        line_length++;
                    }
                    current_x = start_x + (console_width - line_length) / 2;
                    gotoxy(current_x, current_y);
                    for (int j = 0; j < line_length; j++) {
                        printf("%c", text[i + j]);
                        fflush(stdout);
                        Sleep(50);
                    }
                    i += line_length;
                    if (text[i] == '\n') {
                        i++;
                    }
                    line++;
                    if (line >= console_height) {
                        break;
                    }
                    Sleep(48);
                }
                final_y = start_y + line;
                int message_x = start_x + (console_width - 27) / 2;
                gotoxy(message_x + 4, final_y + 4);
                Sleep(575);
                setRGBColor(249, 0, 0);
                printf("[HP�� 20 �Ҿ���]");
                resetColor();
                Sleep(48);
                final_y = start_y + line;
                gotoxy(message_x + 3, final_y + 4);
                Sleep(575);
                setRGBColor(0, 212, 0);
                resetColor();
                Sleep(48);
                sprintf(q, "UPDATE gwangju_sword_master.user_state SET good_and_evil = hp-10 WHERE id = '%s'", id);
                if (mysql_query(&db, q)) {
                    db_query_error(&db);
                    mysql_close(&db);
                    exit(0);
                }
                mysql_close(&db);
                Sleep(3000);
                return;
            }
            else {
                line = 0;
                final_y = 2;
                memset(text, 0, sizeof(text));
                strcpy(text, "�ƹ��ϵ� ���� ��������...");
                console_width = 120 - 32 + 1;
                console_height = 17 - 2 + 1;
                start_x = 32;
                start_y = 2;
                text_length = strlen(text);
                i = 0;
                while (i < text_length) {
                    int current_x = start_x;
                    int current_y = start_y + line;
                    int line_length = 0;
                    while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
                        line_length++;
                    }
                    current_x = start_x + (console_width - line_length) / 2;
                    gotoxy(current_x, current_y + 3);
                    for (int j = 0; j < line_length; j++) {
                        printf("%c", text[i + j]);
                        fflush(stdout);
                        Sleep(50);
                    }
                    i += line_length;
                    if (text[i] == '\n') {
                        i++;
                    }
                    line++;
                    if (line >= console_height) {
                        break;
                    }
                }
                final_y = start_y + line;
                gotoxy(message_x + 5, final_y + 4);
                Sleep(575);
                setRGBColor(249, 0, 0);
                resetColor();
                Sleep(48);
                Sleep(1000);
                return;
            }
        }
    }
    return;
}