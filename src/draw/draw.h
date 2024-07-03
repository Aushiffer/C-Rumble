#ifndef __DRAW__
#define __DRAW__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "../game_states/game_states.h"
#include "../fighter/fighter.h"

#define COLOR_BLACK al_map_rgb(0, 0, 0)
#define COLOR_WHITE al_map_rgb(255, 255, 255)
#define COLOR_LIGHT_GRAY al_map_rgb(120, 120, 120)
#define COLOR_DARK_BLUE al_map_rgb(0, 25, 51)
#define COLOR_TOMATO al_map_rgb(64, 0, 0)
#define COLOR_DARK_GREEN al_map_rgb(0, 42, 0)

/* Renderiza o menu principal */
void draw_menu(ALLEGRO_FONT *menu_header_font, ALLEGRO_FONT *menu_options_font, ALLEGRO_DISPLAY *display, GameStates *game_states);

/* Renderiza a tela de seleção de personagens */
void draw_character_select( 
        ALLEGRO_FONT *character_select_header_font, ALLEGRO_FONT *player_indicator_font, 
        ALLEGRO_FONT *character_select_display_name_font, ALLEGRO_DISPLAY *display,
        ALLEGRO_BITMAP *viking_icon, ALLEGRO_BITMAP *knight_icon, 
        ALLEGRO_BITMAP *spearwoman_icon, ALLEGRO_BITMAP *fire_warrior_icon,
        GameStates *game_states
);

/* Renderiza a tela de seleção de cenário */
void draw_stage_select(
        ALLEGRO_FONT *header_font, ALLEGRO_FONT *stage_display_name_font, 
        ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *stage_select_arrow_icon, 
        GameStates *game_states
);

/* Renderiza o cenário selecionado pelo jogador */
void draw_stage(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *stage1_bitmap, ALLEGRO_BITMAP *stage2_bitmap, GameStates *game_states);

/* Renderiza as hitboxes dos jogadores */
void draw_player_hitboxes(Fighter *player1, Fighter *player2, ALLEGRO_DISPLAY *display);

/* Anima o soco do lutador na tela */
void draw_hi_punch_animation(Fighter *player, float frame_duration, float *time_animation, unsigned int *current_frame, unsigned int num_frames);

/* Renderiza a tela de pause */
void draw_pause(ALLEGRO_FONT *pause_header_font, ALLEGRO_FONT *pause_options_font, ALLEGRO_DISPLAY *display, GameStates *game_states);

#endif // __DRAW__