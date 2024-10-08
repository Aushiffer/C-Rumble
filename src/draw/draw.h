#ifndef __DRAW__
#define __DRAW__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/display.h>
#include "../game_states/game_states.h"
#include "../fighter/fighter.h"

#define COLOR_BLACK al_map_rgb(0, 0, 0)
#define COLOR_WHITE al_map_rgb(255, 255, 255)
#define COLOR_LIGHT_GRAY al_map_rgb(120, 120, 120)
#define COLOR_DARK_BLUE al_map_rgb(0, 25, 51)
#define COLOR_TOMATO al_map_rgb(64, 0, 0)
#define COLOR_DARK_GREEN al_map_rgb(0, 42, 0)
#define COLOR_LIGHT_GREEN al_map_rgb(0, 255, 0)
#define COLOR_LIGHT_RED al_map_rgb(255, 0, 0)
#define COLOR_YELLOW al_map_rgb(255, 255, 0)
#define COLOR_ORANGE al_map_rgb(255, 165, 0)

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
void draw_stages(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *stage1_bitmap, ALLEGRO_BITMAP *stage2_bitmap, ALLEGRO_BITMAP *stage3_bitmap, ALLEGRO_BITMAP *stage4_bitmap, GameStates *game_states);

/* Anima o soco do lutador na tela */
void draw_hi_punch_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames);

/* Anima o personagem dando um soco baixo */
void draw_lo_punch_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames);

/* Anima o personagem dando um soco aéreo */
void draw_air_punch_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames);

/* Anima o chute do lutador na tela */
void draw_hi_kick_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames);

/* Anima o chute agachado do lutador na tela */
void draw_lo_kick_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames);

/* Anima o personagem dando um chute aéreo */
void draw_air_kick_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames);

/* Anima o personagem correndo */
void draw_running_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, float frame_duration_idle, float *time_frame_idle, unsigned int *current_frame_idle, unsigned int num_frames, unsigned int num_frames_idle);

/* Anima o personagem em repouso */
void draw_idle_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames);

/* Anima o personagem bloqueando */
void draw_blocking_animation(Fighter *player);

/* Anima o personagem bloqueando agachado */
void draw_lo_blocking_animation(Fighter *player);

/* Anima o personagem abaixado */
void draw_crouching_animation(Fighter *player);

/* Anima o personagem pulando */
void draw_jumping_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames);

/* Renderiza a barra de vida do jogador */
void draw_health_bars(Fighter *player1, Fighter *player2, ALLEGRO_DISPLAY *display);

/* Renderiza nomes dos personagens embaixo das barras de vida */
void draw_rumble_header(GameStates *game_states, ALLEGRO_DISPLAY *display, ALLEGRO_FONT *rumble_display_character_name_font, ALLEGRO_FONT *character_select_header_font, char *wins_text_p1, char *wins_text_p2);

/* Renderiza a tela de fim de jogo */
void draw_rumble_end(GameStates *game_states, ALLEGRO_DISPLAY *display, ALLEGRO_FONT *header_font, ALLEGRO_FONT *prompt_input_font, Fighter *player1, Fighter *player2);

/* Renderiza a tela de pause */
void draw_pause(ALLEGRO_FONT *pause_header_font, ALLEGRO_FONT *pause_options_font, ALLEGRO_DISPLAY *display, GameStates *game_states);

#endif // __DRAW__