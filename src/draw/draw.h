#ifndef __DRAW__
#define __DRAW__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "../game_states/game_states.h"

/* Renderiza o menu principal */
void draw_menu(ALLEGRO_FONT *menu_header_font, ALLEGRO_FONT *menu_options_font, ALLEGRO_DISPLAY *display, GameStates *game_states);

/* Renderiza a tela de seleção de personagens */
void draw_character_select( 
        ALLEGRO_FONT *character_select_header_font, ALLEGRO_FONT *menu_options_font, 
        ALLEGRO_FONT *character_select_display_name_font, ALLEGRO_DISPLAY *display,
        ALLEGRO_BITMAP *character_icon1, ALLEGRO_BITMAP *character_icon2, 
        ALLEGRO_BITMAP *character_icon3, ALLEGRO_BITMAP *character_icon4,
        GameStates *game_states
);

#endif // __DRAW__