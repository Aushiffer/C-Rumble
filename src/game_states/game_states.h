#ifndef __GAME_STATES__
#define __GAME_STATES__

#include <stdio.h>
#include <stdlib.h>

/* Estrutura de estados de jogo, contendo flags importantes para o funcionamento do programa */
typedef struct GameStates {
        unsigned char menu;
        unsigned char play_menu_sample;
        unsigned char character_select;
        unsigned char character_select_nav_p1_confirm;
        unsigned char character_select_nav_p2_confirm;
        unsigned char play_character_select_welcome_sample;
        unsigned char play_character_select_sample;
        unsigned char stage_select;
        unsigned char play_stage_select_sample;
        unsigned char rumble;
        unsigned char rumble_fighter_p1;
        unsigned char rumble_fighter_p2;
        unsigned char rumble_pause;
        char menu_select;
        char character_select_nav_p1;
        char character_select_nav_p2;
        char stage_select_nav;
} GameStates;

/* Cria estrutura de estados de jogo */
GameStates *create_game_states();

/* Destrói estrutura de dados de jogo */
void destroy_game_states(GameStates *game_states);

#endif // __GAME_STATES__