#include "superclass.h"
#include "mop_dictionary.h"

//index [0] == name / [1] == attack / [2] == defense / [3] == speed

Monster goblin(void) {
    Monster goblin = { "���", 5, 3, 15 };
    return goblin;
}

Monster slime(void) {
    Monster slime = { "������",0,5,3 };
    return slime;
}

Monster bat(void) {
    Monster bat = { "����",8,0,30 };
    return bat;
}

Monster oak(void) {
    Monster oak = { "��ũ",10,15,5 };
    return oak;
}

Monster wolfman(void) {
    Monster wolfman = { "�����ΰ�",10,13,20 };
    return wolfman;
}

Monster magician(void) {
    Monster magician = { "�渶����",0,3,1 };
    return magician;
}

Monster dragon(void) {
    Monster dragon = { "�巡��",15,30,30 };
}