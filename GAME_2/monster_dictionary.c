#include "superclass.h"
#include "mop_dictionary.h"

//index [0] == name / [1] == hp / [2] == attack / [3] == defense / [4] == speed

Monster goblin(void) {
    Monster goblin = { "���",50,5,3,15 };
    return goblin;
}

long long goblin_skill_1(void) {
	long long damage;
    memset(string, 0, sizeof(string));
	damage = 3;
    sprintf(string, "����� �ϰ�! ���ظ� %lld �޾Ҵ�", damage);
    scrollUpImproved(32, 3, 17);
    printAt(32, 17, string);
    gotoxy(32 + strlen(string), 17);
	return damage;
}

Monster slime(void) {
    Monster slime = { "������",30,0,5,3 };
    return slime;
}

void slime_skill_1(void) {
	memset(string, 0, sizeof(string));
	strcat(string, "�������� �ʻ� �幰�Ÿ���! ������ �ƹ��ϵ� �Ͼ�� �ʾҴ�!");
	scrollUpImproved(32, 3, 17);
	printAt(32, 17, string);
	gotoxy(32 + strlen(string), 17);
	return;
}

Monster bat(void) {
    Monster bat = { "����",25,8,0,30 };
    return bat;
}

long long bat_skill_1(void) {
	memset(string, 0, sizeof(string));
	long long damage = 5;
	strcat(string, "���㰡 ������ �ߴ�! HP�� 5 �����");
	scrollUpImproved(32, 3, 17);
	printAt(32, 17, string);
	gotoxy(32 + strlen(string), 17);
	return damage;
}

long long bat_skill_2(void) {
    memset(string, 0, sizeof(string));
	long long damage = 8;
	strcat(string, "������ ������! ���ظ� 8 �޾Ҵ�");
	scrollUpImproved(32, 3, 17);
	printAt(32, 17, string);
	gotoxy(32 + strlen(string), 17);
	return damage;
}

Monster oak(void) {
    Monster oak = { "��ũ",175,10,15,5 };
    return oak;
}

Monster wolfman(void) {
    Monster wolfman = { "�����ΰ�",150,10,13,20 };
    return wolfman;
}

Monster magician(void) {
    Monster magician = { "�渶����",90,0,3,1 };
    return magician;
}

Monster dragon(void) {
    Monster dragon = { "�巡��",300,15,30,30 };
}