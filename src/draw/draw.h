#ifndef __DRAW__
#define __DRAW__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "../game_states/game_states.h"

#define COLOR_BLACK al_map_rgb(0, 0, 0)
#define COLOR_WHITE al_map_rgb(255, 255, 255)
#define COLOR_LIGHT_GRAY al_map_rgb(120, 120, 120)
#define COLOR_DARK_BLUE al_map_rgb(0, 25, 51)
#define COLOR_TOMATO al_map_rgb(64, 0, 0)
#define COLOR_DARK_GREEN al_map_rgb(0, 64, 0)

/* Renderiza o menu principal */
void draw_menu(ALLEGRO_FONT *menu_header_font, ALLEGRO_FONT *menu_options_font, ALLEGRO_DISPLAY *display, GameStates *game_states);

/* Renderiza a tela de seleção de personagens */
void draw_character_select( 
        ALLEGRO_FONT *character_select_header_font, ALLEGRO_FONT *player_indicator_font, 
        ALLEGRO_FONT *character_select_display_name_font, ALLEGRO_DISPLAY *display,
        ALLEGRO_BITMAP *character_icon1, ALLEGRO_BITMAP *character_icon2, 
        ALLEGRO_BITMAP *character_icon3, ALLEGRO_BITMAP *character_icon4,
        GameStates *game_states
);

/* Renderiza a tela de seleção de cenário */
void draw_stage_select(ALLEGRO_FONT *header_font, ALLEGRO_FONT *stage_display_name_font, ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *stage_select_arrow_icon, GameStates *game_states);

#endif // __DRAW__