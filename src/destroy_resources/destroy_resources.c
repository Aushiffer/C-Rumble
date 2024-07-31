#include "destroy_resources.h"

BitmapGarbageArray *create_bitmap_garbage_array(void) {
        BitmapGarbageArray *garbage_array = (BitmapGarbageArray *)malloc(sizeof(BitmapGarbageArray));

        if (!garbage_array)
                return NULL;
        
        garbage_array->array = (ALLEGRO_BITMAP **)malloc(ARRAY_MAX_SIZE * sizeof(ALLEGRO_BITMAP *));

        if (!garbage_array->array)
                return NULL;

        garbage_array->array_size = 0;

        return garbage_array;
}

void insert_bitmap_array(BitmapGarbageArray *bitmap_garbage_array, ALLEGRO_BITMAP *bitmap) {
        if (bitmap_garbage_array->array_size == ARRAY_MAX_SIZE) {
                fprintf(stderr, "[-] insert_bitmap_array(): garbage array overflow\n");

                return;
        }
        
        (bitmap_garbage_array->array_size)++;
        bitmap_garbage_array->array[bitmap_garbage_array->array_size - 1] = bitmap;
}

void destroy_bitmap_garbage_array(BitmapGarbageArray *bitmap_garbage_array) {
        for (unsigned int i = 0; i < bitmap_garbage_array->array_size; i++)
                al_destroy_bitmap(bitmap_garbage_array->array[i]);
        
        free(bitmap_garbage_array->array);
        free(bitmap_garbage_array);
}

SampleGarbageArray *create_sample_garbage_array(void) {
        SampleGarbageArray *garbage_array = (SampleGarbageArray *)malloc(sizeof(SampleGarbageArray));

        if (!garbage_array)
                return NULL;
        
        garbage_array->array = (ALLEGRO_SAMPLE **)malloc(ARRAY_MAX_SIZE * sizeof(ALLEGRO_SAMPLE *));

        if (!garbage_array->array)
                return NULL;

        garbage_array->array_size = 0;

        return garbage_array;
}

void insert_sample_array(SampleGarbageArray *sample_garbage_array, ALLEGRO_SAMPLE *sample) {
        if (sample_garbage_array->array_size == ARRAY_MAX_SIZE) {
                fprintf(stderr, "[-] insert_sample_array(): garbage array overflow\n");

                return;
        }
        
        (sample_garbage_array->array_size)++;
        sample_garbage_array->array[sample_garbage_array->array_size - 1] = sample;
}

void destroy_sample_garbage_array(SampleGarbageArray *sample_garbage_array) {
        for (unsigned int i = 0; i < sample_garbage_array->array_size; i++)
                al_destroy_sample(sample_garbage_array->array[i]);
        
        free(sample_garbage_array->array);
        free(sample_garbage_array);
}

FontGarbageArray *create_font_garbage_array(void) {
        FontGarbageArray *garbage_array = (FontGarbageArray *)malloc(sizeof(FontGarbageArray));

        if (!garbage_array)
                return NULL;

        garbage_array->array = (ALLEGRO_FONT **)malloc(ARRAY_MAX_SIZE * sizeof(ALLEGRO_FONT *));

        if (!garbage_array->array)
                return NULL;

        garbage_array->array_size = 0;

        return garbage_array;
}

void insert_font_array(FontGarbageArray *font_garbage_array, ALLEGRO_FONT *font) {
        if (font_garbage_array->array_size == ARRAY_MAX_SIZE) {
                fprintf(stderr, "[-] insert_font_array(): garbage array overflow\n");

                return;
        }

        (font_garbage_array->array_size)++;
        font_garbage_array->array[font_garbage_array->array_size - 1] = font;
}

void destroy_font_garbage_array(FontGarbageArray *font_garbage_array) {
        for (unsigned int i = 0; i < font_garbage_array->array_size; i++)
                al_destroy_font(font_garbage_array->array[i]);
        
        free(font_garbage_array->array);
        free(font_garbage_array);
}

void destroy_spriteset(ALLEGRO_BITMAP **spriteset, unsigned int num_frames) {
        for (unsigned int i = 0; i < num_frames; i++)
                al_destroy_bitmap(spriteset[i]);

        free(spriteset);
}