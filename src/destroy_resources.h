#ifndef __DESTROY_RESOURCES__
#define __DESTROY_RESOURCES__

#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>

/* Destrói todas as amostras de áudio do jogo */
void destroy_samples(
        ALLEGRO_SAMPLE *menu_sample, ALLEGRO_SAMPLE *menu_confirm_sample, 
        ALLEGRO_SAMPLE *menu_select_sample, ALLEGRO_SAMPLE *cancel_sound_sample,
        ALLEGRO_SAMPLE *character_select_welcome_sample, ALLEGRO_SAMPLE *character_select_sample,
        ALLEGRO_SAMPLE *character_select_confirm_sample, ALLEGRO_SAMPLE *pause_sound_effect,
        ALLEGRO_SAMPLE *dark_forest_sample, ALLEGRO_SAMPLE *abandoned_factory_sample
);

/* Destrói todas as fontes usadas no jogo */
void destroy_fonts(
        ALLEGRO_FONT *menu_header_font, ALLEGRO_FONT *menu_options_font, 
        ALLEGRO_FONT *character_select_header_font, ALLEGRO_FONT *character_select_display_name_font
);

/* Destrói todos os bitmaps usados no jogo */
void destroy_bitmaps(
        ALLEGRO_BITMAP *window_icon, ALLEGRO_BITMAP *viking_icon,
        ALLEGRO_BITMAP *knight_icon, ALLEGRO_BITMAP *spearwoman_icon,
        ALLEGRO_BITMAP *fire_warrior_icon, ALLEGRO_BITMAP *stage_select_arrow_icon, 
        ALLEGRO_BITMAP *stage_dark_forest, ALLEGRO_BITMAP *stage_abandoned_factory,
        ALLEGRO_BITMAP *viking_idle_spriteset[], int NUM_IDLE_FRAMES
);

#endif // __DESTROY_RESOURCES__