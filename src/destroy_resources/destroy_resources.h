#ifndef __DESTROY_RESOURCES__
#define __DESTROY_RESOURCES__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>

#define ARRAY_MAX_SIZE 100000

/* Vetor para descarte futuro de bitmaps do jogo */
typedef struct BitmapGarbageArray {
        ALLEGRO_BITMAP **array;
        unsigned int array_size;
} BitmapGarbageArray;

/* Vetor para descarte futuro de amostras de áudio do jogo */
typedef struct SampleGarbageArray {
        ALLEGRO_SAMPLE **array;
        unsigned int array_size;
} SampleGarbageArray;

/* Vetor para descarte futuro de fontes do jogo */
typedef struct FontGarbageArray {
        ALLEGRO_FONT **array;
        unsigned int array_size;
} FontGarbageArray;

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

/* Cria um vetor de descarte de fontes */
FontGarbageArray *create_font_garbage_array(void);

/* Insere uma fonte no vetor de descartes de fontes */
void insert_font_array(FontGarbageArray *font_garbage_array, ALLEGRO_FONT *font);

/* Descarta um vetor de descarte de fontes */
void destroy_font_garbage_array(FontGarbageArray *font_garbage_array);

/* Destrói um set de sprites de um personagem */
void destroy_spriteset(ALLEGRO_BITMAP **spriteset, unsigned int num_frames);

#endif // __DESTROY_RESOURCES__