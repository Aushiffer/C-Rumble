#ifndef __DESTROY_RESOURCES__
#define __DESTROY_RESOURCES__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>

#define ARRAY_MAX_SIZE 100000

typedef struct BitmapGarbageArray {
        ALLEGRO_BITMAP **array;
        unsigned int array_size;
} BitmapGarbageArray;

typedef struct SampleGarbageArray {
        ALLEGRO_SAMPLE **array;
        unsigned int array_size;
} SampleGarbageArray;

/* Cria um vetor de descarte de bitmaps */
BitmapGarbageArray *create_bitmap_garbage_array(void);

/* Insere um bitmap no vetor de descarte de bitmaps */
void insert_bitmap_array(BitmapGarbageArray *bitmap_garbage_array, ALLEGRO_BITMAP *bitmap);

/* Descarta um vetor de descarte de bitmaps */
void destroy_bitmap_garbage_array(BitmapGarbageArray *bitmap_garbage_array);

/* Cria um vetor de descarte de amostras de áudio */
SampleGarbageArray *create_sample_garbage_array(void);

/* Insere uma amostra de áudio no vetor de descarte de amostras de áudio */
void insert_sample_array(SampleGarbageArray *sample_garbage_array, ALLEGRO_SAMPLE *sample);

/* Descarta um vetor de descarte de amostras de áudio */
void destroy_sample_garbage_array(SampleGarbageArray *sample_garbage_array);

/* Destrói todas as amostras de áudio do jogo */
void destroy_samples(
        ALLEGRO_SAMPLE *menu_sample, ALLEGRO_SAMPLE *menu_confirm_sample, 
        ALLEGRO_SAMPLE *menu_select_sample, ALLEGRO_SAMPLE *cancel_sound_sample,
        ALLEGRO_SAMPLE *character_select_welcome_sample, ALLEGRO_SAMPLE *character_select_sample,
        ALLEGRO_SAMPLE *character_select_confirm_sample, ALLEGRO_SAMPLE *pause_sound_effect,
        ALLEGRO_SAMPLE *dark_forest_sample, ALLEGRO_SAMPLE *abandoned_factory_sample,
        ALLEGRO_SAMPLE *calm_forest_sample, ALLEGRO_SAMPLE *rumble_end_sample
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
        ALLEGRO_BITMAP *stage_calm_forest
);

/* Destrói um set de sprites de um personagem */
void destroy_spriteset(ALLEGRO_BITMAP **spriteset, unsigned int num_frames);

#endif // __DESTROY_RESOURCES__