#include "superclass.h"
#include "player_state.h"

int main() {
    mail_send();
    Sleep(7500);
    int sync = 0;
    Program_config();
    ASCII_Art_print();
    CursorView(0);
    sync = loginmenuDraw();
    while (sync == 1) {
        Program_config();
        ASCII_Art_print();
        loginmenuDraw();
    }
    exit(1);
}

int game_core_code(char id[]) {
    initial_hp(id);
    initial_mp(id);
    now_level(id);
    now_state(id);
    ingame_select();
    stage_1(id);
    Sleep(10000);
}