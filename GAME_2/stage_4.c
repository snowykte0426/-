#include "superclass.h"

void stage_4(char id[], int mop_num) {
    bool mana_recovery = false;
    Clear_Gamelog();
    static int initial_x = 32, initial_y = 17, mop_hp, mop_max_hp;
    int n = 8;
    label:;
    Monster m[10] = { dragon(), Golem(), oak(), wolfman(), wolfman(), dragon(), dragon(), dragon()};
    memset(string, 0, sizeof(string));
    setRGBColor(0, 255, 0);
    strcpy(string, "Stage.4");
    printAt(initial_x, initial_y, string);
    resetColor();
    MYSQL db;
    connect_to_db(&db);
    memset(string, 0, sizeof(string));
    strcpy(string, " ");
    scrollup_motion(initial_x, 17);
    printAt(initial_x, initial_y, string);
    gotoxy(initial_x + strlen(string), initial_y);
    char query[255];
    char event_check[30];
    memset(event_check, 0, sizeof(event_check));
    sprintf(query, "UPDATE gwangju_sword_master.account SET stage = 4, mop_num = %d WHERE id = '%s'", mop_num, id);
    if (mysql_query(&db, query)) {
        db_query_error(&db);
        mysql_close(&db);
        exit(0);
    }
    for (int i = mop_num - 1; i < n; i++) {
        strcpy(event_check, m[i].type);
        if (strcmp(event_check, "Event") == 0) {
            Whisper(id);
            MYSQL db;
            connect_to_db(&db);
            memset(query, 0, sizeof(query));
            sprintf(query, "UPDATE gwangju_sword_master.account SET mop_num = mop_num + 1 WHERE id = '%s'", id);
            if (mysql_query(&db, query)) {
                db_query_error(&db);
                mysql_close(&db);
                exit(0);
            }
            mysql_close(&db);
            continue;
        }
        else {
            unsigned char match_turn = false;
            if (i > 0) {
                scrollup_motion(initial_x, initial_y);
            }
            memset(string, 0, sizeof(string));
            srand(time(NULL));
            if (strcmp(m[i].name, "���") == 0 || strcmp(m[i].name, "������") == 0 || strcmp(m[i].name, "�����ΰ�") == 0 || strcmp(m[i].name, "��") == 0 || strcmp(m[i].name, "�巡��") == 0) {
                short sync = rand() % 2 + 1;
                if (sync == 1) {
                    sprintf(string, "%s�� Ƣ��Դ�!", m[i].name);
                }
                else {
                    sprintf(string, "%s�� ��Ÿ����!", m[i].name);
                }
            }
            else {
                short sync = rand() % 2 + 1;
                if (sync == 1) {
                    sprintf(string, "%s�� Ƣ��Դ�!", m[i].name);
                }
                else {
                    sprintf(string, "%s�� ��Ÿ����!", m[i].name);
                }
            }
            gotoxy(50, 21);
            printf("                                                           ");
            scrollup_motion(initial_x, 17);
            printAt(initial_x, initial_y, string);
            mop_max_hp = mop_hp = m[i].hp;
            while (true) {
                memset(query, 0, sizeof(query));
                sprintf(query, "SELECT number FROM gwangju_sword_master.effect WHERE id = '%s' AND effect = 'burn'", id);
                if (mysql_query(&db, query)) {
					db_query_error(&db);
					mysql_close(&db);
					exit(1);
				}
                MYSQL_RES* res = mysql_store_result(&db);
                if (res != NULL) {
                    MYSQL_ROW row = mysql_fetch_row(res);
                    if (row != NULL && row[0] != NULL) {
                        mop_hp -= 5;
                        memset(query, 0, sizeof(query));
                        sprintf(query, "UPDATE gwangju_sword_master.user_state SET hp = hp - 3 WHERE id = '%s'", id);
                        if (mysql_query(&db, query)) {
                            db_query_error(&db);
                            mysql_close(&db);
                            exit(0);
                        }
                    }
                    mysql_free_result(res);
                }
                memset(query, 0, sizeof(query));    
                sprintf(query, "SELECT max_mp,mp FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
                if (mysql_query(&db, query)) {
                    db_query_error(&db);
                    mysql_close(&db);
                    exit(1);
                }
                res = mysql_store_result(&db);
                MYSQL_ROW row = mysql_fetch_row(res);
                int mp_max = atoi(row[0]);
                int mp = atoi(row[1]);
                mysql_free_result(res);
                memset(query, 0, sizeof(query));
                int mp_reco = mp + 10 > mp_max ? mp_max - mp : 10;
                if (mana_recovery) {
                    memset(query, 0, sizeof(query));
                    sprintf(query, "UPDATE gwangju_sword_master.user_state SET mp = mp+%d WHERE id = '%s'", mp_reco, id);
                    if (mysql_query(&db, query)) {
                        db_query_error(&db);
                        mysql_close(&db);
                        exit(0);
                    }
                }
                mana_recovery = true;
                if (!mysql_ping(&db)) {
                    connect_to_db(&db);
                }
                gotoxy(50, 21);
                printf("                                           ");
                mop_hp_bar(mop_hp, mop_max_hp, 50, 21, m[i].name);
                ClearViewState();
                now_level(id);
                now_state(id);
                hp_mp_bar(id);
                long long b = ingame_select(id, m, turn, initial_x, initial_y);
                if (b == 1831) {
                    mop_num++;
                    break;
                }
                else if (b == 1023914) {
                    i = -1;
                    mop_num = 1;
                    goto label;
                    continue;
                }
                else {
                    short sync = 0;
                    mop_hp -= b;
                    turn++;
                    match_turn = true;
                    if (mop_hp > 0) {
                        if (match_turn == true) {
                            sync = mop_turn(id, m, i, initial_x, initial_y);
                        }
                        if (sync) {
                            mop_hp += 5;
                            memset(query, 0, sizeof(query));
                            sprintf(query, "UPDATE gwangju_sword_master.user_state SET hp = hp - 5 WHERE id = '%s'", id);
                            if (mysql_query(&db, query)) {
                                db_query_error(&db);
                                mysql_close(&db);
                                exit(0);
                            }
                        }
                        continue;
                    }
                    else if (mop_hp <= 0) {
                        memset(string, 0, sizeof(string));
                        setRGBColor(255, 255, 51);
                        sprintf(string, "%s�� óġ�ߴ�!", m[i].name);
                        drop_booty(id, m[i].name);
                        scrollup_motion(initial_x, 17);
                        printAt(initial_x, initial_y, string);
                        gotoxy(initial_x + strlen(string), initial_y);
                        resetColor();
                        memset(query, 0, sizeof(query));
                        sprintf(query, "UPDATE gwangju_sword_master.account SET mop_num = mop_num + 1 WHERE id = '%s'", id);
                        if (mysql_query(&db, query)) {
                            db_query_error(&db);
                            mysql_close(&db);
                            exit(0);
                        }
                        event:;
                        if (mop_num == 2) {
                            Clear_Gamelog();
                            gotoxy(50, 21);
                            printf("                                              ");
                            Rooting_conn(id);
                            memset(query, 0, sizeof(query));
                            Clear_Gamelog();
                        }
                        if (mop_num == 8) {
                            Clear_Gamelog();
                            gotoxy(50, 21);
                            printf("                                                  ");
                            Mimic_conn(id);
                            memset(query, 0, sizeof(query));
                            Clear_Gamelog();
                        }
                        mop_num++;
                        break;
                    }
                }
            }
            check_and_delete_expired_effects_fug(id, &db);
            Effect_Counter(id);
        }
    }
    mysql_close(&db);
    gotoxy(50, 21);
    printf("                                               ");
    stage4_clear(id);
    final_stage(id, 1);
}

void stage4_clear(char id[]) {
    MYSQL db;
    gotoxy(50, 21);
    printf("                                           ");
    connect_to_db(&db);
    Clear_Gamelog();
    char query[255];
    unsigned int line = 0;
    unsigned int final_y = 2;
    sprintf(query, "SELECT gender FROM gwangju_sword_master.account WHERE id = '%s'", id);
    if (mysql_query(&db, query)) {
		db_query_error(&db);
		mysql_close(&db);
		exit(0);
	}
    MYSQL_RES* res = mysql_store_result(&db);
    if (res == NULL) {
		db_query_error(&db);
		mysql_close(&db);
		exit(0);
	}
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row == NULL) {
        db_query_error(&db);
        mysql_close(&db);
        mysql_free_result(res);
        exit(1);
    }
    const char* text;
    if (!strcmp(row[0], "male")) {
        memset(query, 0, sizeof(query));
        text = "�� �� ���� ���� �ᱹ �׶����� �տ� ���� ������ �Բ��Ͽ���\n"
            "����� ���� �Ƿ� ��������ϴ�.\n"
            "�ڲٸ� ��ð��� ������\n"
            "����ϱ��� ������ ��� ����� ����� �ϼ��ؾ� �մϴ�.\n"
            "���ָ� ���϶�� ��ɾƷ� ������� �� ��ŭ ������ �����ô�!\n";
    }
    else {
        memset(query, 0, sizeof(query));
        text = "�� �� ���� ���� �ᱹ �׶����� �տ� ���� ������ �Բ��Ͽ���\n"
            "����� ���� �Ƿ� ��������ϴ�.\n"
            "�ڲٸ� ��ð��� ������\n"
            "����ϱ��� ������ ��� ����� ����� �ϼ��ؾ� �մϴ�.\n"
            "���ڸ� ���϶�� ��ɾƷ� ������� �� ��ŭ ������ �����ô�!";
    }
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
    const char* hp_recovered_text = "[HP�� �ִ�ġ���� ȸ���Ǿ����ϴ�]";
    int hp_recovered_x = start_x + (console_width - strlen(hp_recovered_text)) / 2;
    gotoxy(hp_recovered_x, final_y + 1);
    setRGBColor(0, 255, 0);
    printf("%s", hp_recovered_text);
    resetColor();
    int message_x = start_x + (console_width - 27) / 2;
    gotoxy(message_x, final_y + 4);
    Sleep(1975);
    printf("����Ϸ��� Enter�� ��������");
    CursorView(0);
    while (true) {
        int n = KeyControl();
        if (n == SUBMIT) {
            sprintf(query, "UPDATE gwangju_sword_master.account SET stage = 2, mop_num = 1 WHERE id = '%s'", id);
            if (mysql_query(&db, query)) {
                db_query_error(&db);
                mysql_close(&db);
                exit(0);
            }
            memset(query, 0, sizeof(query));
            sprintf(query, "UPDATE gwangju_sword_master.user_state SET hp = max_hp WHERE id = '%s'", id);
            if (mysql_query(&db, query)) {
                db_query_error(&db);
                mysql_close(&db);
                exit(0);
            }
            mysql_close(&db);
            return;
        }
        else {
            continue;
        }
    }
}

void final_stage(char id[], int mop_num) {
    bool mana_recovery = false;
    Clear_Gamelog();
    static int initial_x = 32, initial_y = 17, mop_hp, mop_max_hp;
    int n = 1;
    label:;
    Monster m[1] = { Grandis() };
    memset(string, 0, sizeof(string));
    setRGBColor(255, 0, 0);
    strcpy(string, "�����ִ� ��, �׶���");
    printAt(initial_x, initial_y, string);
    resetColor();
    MYSQL db;
    connect_to_db(&db);
    memset(string, 0, sizeof(string));
    strcpy(string, " ");
    scrollup_motion(initial_x, 17);
    printAt(initial_x, initial_y, string);
    gotoxy(initial_x + strlen(string), initial_y);
    char query[255];
    char event_check[30];
    memset(event_check, 0, sizeof(event_check));
    sprintf(query, "UPDATE gwangju_sword_master.account SET stage = 5, mop_num = %d WHERE id = '%s'", mop_num, id);
    if (mysql_query(&db, query)) {
        db_query_error(&db);
        mysql_close(&db);
        exit(0);
    }
    for (int i = mop_num - 1; i < n; i++) {
        strcpy(event_check, m[i].type);
        if (strcmp(event_check, "Event") == 0) {
            Whisper(id);
            MYSQL db;
            connect_to_db(&db);
            memset(query, 0, sizeof(query));
            sprintf(query, "UPDATE gwangju_sword_master.account SET mop_num = mop_num + 1 WHERE id = '%s'", id);
            if (mysql_query(&db, query)) {
                db_query_error(&db);
                mysql_close(&db);
                exit(0);
            }
            mysql_close(&db);
            continue;
        }
        else {
            unsigned char match_turn = false;
            if (i > 0) {
                scrollup_motion(initial_x, initial_y);
            }
            memset(string, 0, sizeof(string));
            gotoxy(50, 21);
            printf("                                                           ");
            scrollup_motion(initial_x, 17);
            printAt(initial_x, initial_y, string);
            mop_max_hp = mop_hp = m[i].hp;
            while (true) {
                memset(query, 0, sizeof(query));
                sprintf(query, "SELECT number FROM gwangju_sword_master.effect WHERE id = '%s' AND effect = 'burn'", id);
                if (mysql_query(&db, query)) {
                    db_query_error(&db);
                    mysql_close(&db);
                    exit(1);
                }
                MYSQL_RES* res = mysql_store_result(&db);
                if (res != NULL) {
                    MYSQL_ROW row = mysql_fetch_row(res);
                    if (row != NULL && row[0] != NULL) {
                        mop_hp -= 5;
                        memset(query, 0, sizeof(query));
                        sprintf(query, "UPDATE gwangju_sword_master.user_state SET hp = hp - 3 WHERE id = '%s'", id);
                        if (mysql_query(&db, query)) {
                            db_query_error(&db);
                            mysql_close(&db);
                            exit(0);
                        }
                    }
                    mysql_free_result(res);
                }
                memset(query, 0, sizeof(query));
                sprintf(query, "SELECT max_mp,mp FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
                if (mysql_query(&db, query)) {
                    db_query_error(&db);
                    mysql_close(&db);
                    exit(1);
                }
                res = mysql_store_result(&db);
                MYSQL_ROW row = mysql_fetch_row(res);
                int mp_max = atoi(row[0]);
                int mp = atoi(row[1]);
                mysql_free_result(res);
                memset(query, 0, sizeof(query));
                int mp_reco = mp + 10 > mp_max ? mp_max - mp : 10;
                if (mana_recovery) {
                    memset(query, 0, sizeof(query));
                    sprintf(query, "UPDATE gwangju_sword_master.user_state SET mp = mp+%d WHERE id = '%s'", mp_reco, id);
                    if (mysql_query(&db, query)) {
                        db_query_error(&db);
                        mysql_close(&db);
                        exit(0);
                    }
                }
                mana_recovery = true;
                if (!mysql_ping(&db)) {
                    connect_to_db(&db);
                }
                gotoxy(50, 21);
                printf("                                           ");
                mop_hp_bar(mop_hp, mop_max_hp, 50, 21, m[i].name);
                ClearViewState();
                now_level(id);
                now_state(id);
                hp_mp_bar(id);
                long long b = ingame_select(id, m, turn, initial_x, initial_y);
                if (b == 1831) {
                    mop_num++;
                    break;
                }
                else if (b == 1023914) {
                    i = -1;
                    mop_num = 1;
                    goto label;
                    continue;
                }
                else {
                    short sync = 0;
                    mop_hp -= b;
                    turn++;
                    match_turn = true;
                    if (mop_hp > 0) {
                        if (match_turn == true) {
                            sync = mop_turn(id, m, i, initial_x, initial_y);
                        }
                        if (sync) {
                            mop_hp += 30;
                            memset(query, 0, sizeof(query));
                            sprintf(query, "UPDATE gwangju_sword_master.user_state SET hp = hp - 30 WHERE id = '%s'", id);
                            if (mysql_query(&db, query)) {
                                db_query_error(&db);
                                mysql_close(&db);
                                exit(0);
                            }
                        }
                        continue;
                    }
                    else if (mop_hp <= 0) {
                        memset(string, 0, sizeof(string));
                        setRGBColor(255, 255, 51);
                        sprintf(string, "%s�� óġ�ߴ�!", m[i].name);
                        drop_booty(id, m[i].name);
                        scrollup_motion(initial_x, 17);
                        printAt(initial_x, initial_y, string);
                        gotoxy(initial_x + strlen(string), initial_y);
                        resetColor();
                        memset(query, 0, sizeof(query));
                        sprintf(query, "UPDATE gwangju_sword_master.account SET mop_num = mop_num + 1 WHERE id = '%s'", id);
                        if (mysql_query(&db, query)) {
                            db_query_error(&db);
                            mysql_close(&db);
                            exit(0);
                        }
                        mop_num++;
                        break;
                    }
                }
            }
            check_and_delete_expired_effects_fug(id, &db);
            Effect_Counter(id);
        }
        mysql_close(&db);
        gotoxy(50, 21);
        printf("                                               ");
    }
    stage5_clear(id);
    mysql_close(&db);
    end(id);
}

void stage5_clear(char id[]) {
    system("cls");
}

void end(char id[]) {
    MYSQL db;
    connect_to_db(&db);
    Clear_Gamelog();
    char query[255];
    sprintf(query, "SELECT good_and_evil FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
    if (mysql_query(&db, query)) {
        db_query_error(&db);
        mysql_close(&db);
        exit(0);
    }
    MYSQL_RES* res = mysql_store_result(&db);
    if (res == NULL) {
        db_query_error(&db);
        mysql_close(&db);
        exit(0);
    }
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row == NULL) {
        db_query_error(&db);
        mysql_close(&db);
        mysql_free_result(res);
        exit(1);
    }
    memset(query, 0, sizeof(query));
    int GE = atoi(row[0]);
    sprintf(query, "SELECT reset_count FROM gwangju_sword_master.account WHERE id = '%s'", id);
    if (mysql_query(&db, query)) {
        db_query_error(&db);
        mysql_close(&db);
        exit(0);
    }
    res = mysql_store_result(&db);
    if (res == NULL) {
        db_query_error(&db);
        mysql_close(&db);
        exit(0);
    }
    row = mysql_fetch_row(res);
    if (row == NULL) {
        db_query_error(&db);
        mysql_close(&db);
        mysql_free_result(res);
        exit(1);
    }
    unsigned int line = 0, final_y = 10;
    int RS = atoi(row[0]);
    char* text = (char*)malloc(9024 * sizeof(char));
    memset(text, 0, 9024 * sizeof(char));
    char RS_num[100];
    memset(RS_num, 0, sizeof(RS_num));
    if (GE >= 0 && RS <= 1) {
        memset(query, 0, sizeof(query));
        sprintf(query, "SELECT gender FROM gwangju_sword_master.account WHERE id = '%s'", id);
        if (mysql_query(&db, query)) {
            db_query_error(&db);
            mysql_close(&db);
            exit(0);
        }
        res = mysql_store_result(&db);
        if (res == NULL) {
            db_query_error(&db);
            mysql_close(&db);
            exit(0);
        }
        row = mysql_fetch_row(res);
        if (row == NULL) {
            db_query_error(&db);
            mysql_close(&db);
            mysql_free_result(res);
            exit(1);
        }
        if (strcmp(row[0], "female") == 0) {
            strcpy(text, "����� �׶��𽺸� ����ġ�� ���������� ���ڸ� ���߽��ϴ�.\n"
                "�׶��𽺰� �ִ� ������ ���� �� �����ƴ� ������� ������ �޾�\n"
                "������ ����µ� �����߰� ���ڸ� ���� ���� �����޾�\n"
                "���ڿ� ��ȥ�ϰ� �Ǿ����ϴ�.\n"
                "����� ������ �̷��� ���Դϴ�.\n");
        }
        else {
            strcpy(text, "����� �׶��𽺸� ����ġ�� ���������� ���ָ� ���߽��ϴ�.\n"
                "�׶��𽺰� �ִ� ������ ���� �� �����ƴ� ������� ������ �޾�\n"
                "������ ����µ� �����߰� ���ָ� ���� ���� �����޾�\n"
                "���ֿ� ��ȥ�ϰ� �Ǿ����ϴ�.\n"
                "����� ������ �̷��� ���Դϴ�.\n");
        }
        sprintf(RS_num, "����� %dȸ�� ȸ�ͳ��� ����� �ϼ��Ͽ����ϴ�...", RS);
        strcat(text, RS_num);
    }
    else if (GE < 0 || RS > 1) {
        memset(query, 0, sizeof(query));
        sprintf(query, "SELECT gender FROM gwangju_sword_master.account WHERE id = '%s'", id);
        if (mysql_query(&db, query)) {
            db_query_error(&db);
            mysql_close(&db);
            exit(0);
        }
        res = mysql_store_result(&db);
        if (res == NULL) {
            db_query_error(&db);
            mysql_close(&db);
            exit(0);
        }
        row = mysql_fetch_row(res);
        if (row == NULL) {
            db_query_error(&db);
            mysql_close(&db);
            mysql_free_result(res);
            exit(1);
        }
        if (strcmp(row[0], "female") == 0) {
            strcpy(text, "����� �׶��𽺸� ����������\n"
                "���� ���� ������ ������ ����� ������ Ÿ�����׽��ϴ�.\n"
                "�׶����� ������ ���� ���� �� ����� ����� �ذ�\n"
                "�׿� ���� Ÿ���� �������μ� ���� �ٸ� �ձ��� ���ڸ� �븱���Դϴ�.\n"
                "����� ������ �̷��� ���Դϴ�.\n");
        }
        else {
            strcpy(text, "����� �׶��𽺸� ����������\n"
                "���� ���� ������ ������ ����� ������ Ÿ�����׽��ϴ�.\n"
                "�׶����� ������ ���� ���� �� ����� ����� �ذ�\n"
                "�׿� ���� Ÿ���� �������μ� ���� �ٸ� �ձ��� ���ָ� �븱���Դϴ�.\n"
                "����� ������ �̷��� ���Դϴ�.\n");
        }
        sprintf(RS_num, "����� %dȸ�� ȸ�ͳ��� ����� �ϼ��Ͽ����ϴ�...", RS);
        strcat(text, RS_num);
    }
    else {
        memset(query, 0, sizeof(query));
        sprintf(query, "SELECT gender FROM gwangju_sword_master.account WHERE id = '%s'", id);
        if (mysql_query(&db, query)) {
            db_query_error(&db);
            mysql_close(&db);
            exit(0);
        }
        res = mysql_store_result(&db);
        if (res == NULL) {
            db_query_error(&db);
            mysql_close(&db);
            exit(0);
        }
        row = mysql_fetch_row(res);
        if (row == NULL) {
            db_query_error(&db);
            mysql_close(&db);
            mysql_free_result(res);
            exit(1);
        }
        if (strcmp(row[0], "female") == 0) {
            strcpy(text, "����� �׶��𽺸� ���������� �˼� ���� ����\n"
                "���ڿ��Է� ���ϴ� ����� ���� ���ҽ��ϴ�.\n"
                "�׷��� �㹫�ϰ� ���տ��� ���ڸ� ���� �����\n"
                "�ձ����Ե� �����ް� ���ֹ��� ������\n"
                "���踦 ������ �Ǿ����ϴ�.\n");
        }
        else {
            strcpy(text, "����� �׶��𽺸� ���������� �˼� ���� ����\n"
                "���ֿ��Է� ���ϴ� ����� ���� ���ҽ��ϴ�.\n"
                "�׷��� �㹫�ϰ� ���տ��� ���ָ� ���� �����\n"
                "�ձ����Ե� �����ް� ���ֹ��� ������\n"
                "���踦 ������ �Ǿ����ϴ�.\n");
        }
        sprintf(RS_num, "����� %dȸ�� ȸ�ͳ��� ����� �ϼ��Ͽ����ϴ�...", RS);
        strcat(text, RS_num);
    }
    int console_width = get_console_width();
    int current_x;
    gotoxy(0, 10);
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
                current_x = (console_width - line_length) / 2;
                gotoxy(current_x, 10 + line);
            }
            printf("%c", text[i]);
        }
        Sleep(50);
    }
    final_y += line;
    gotoxy(45, final_y + 2);
    Sleep(1975);
    printf("����Ϸ��� Enter�� ��������");
    CursorView(0);
    free(text);
    while (true) {
        int n = KeyControl();
        if (n == SUBMIT) {
            sprintf(query, "UPDATE gwangju_sword_master.account SET save_file = 0, mop_num = 1, stage = 0 WHERE id = '%s'", id);
            if (mysql_query(&db, query)) {
                db_query_error(&db);
                mysql_close(&db);
                exit(0);
            }
            mysql_close(&db);
            system("cls");
            Gamemenu(id);
            return;
        }
        else {
            continue;
        }
    }
}