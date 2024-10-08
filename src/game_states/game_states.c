#include "game_states.h"

GameStates *create_game_states(void) {
        GameStates *game_states = (GameStates *)malloc(sizeof(GameStates));

        if (!game_states)
                return NULL;

        game_states->menu = 1;
        game_states->play_menu_sample = 1;
        game_states->character_select = 0;
        game_states->character_select_nav_p1_confirm = 0;
        game_states->character_select_nav_p2_confirm = 0;
        game_states->play_character_select_welcome_sample = 0;
        game_states->play_character_select_sample = 0;
        game_states->stage_select = 0;
        game_states->play_stage_select_sample = 0;
        game_states->rumble = 0;
        game_states->play_rumble_sample = 0;
        game_states->rumble_fighter_p1 = 0;
        game_states->rumble_fighter_p2 = 0;
        game_states->rumble_pause = 0;
        game_states->rumble_pause_select = 0;
        game_states->rumble_end = 0;
        game_states->play_rumble_end_sample = 0;
        game_states->menu_select = 0;
        game_states->character_select_nav_p1 = 0;
        game_states->character_select_nav_p2 = 0;   
        game_states->stage_select_nav = 0;     

        return game_states;
}

void destroy_game_states(GameStates *game_states) {
        if (game_states)
                free(game_states);
}