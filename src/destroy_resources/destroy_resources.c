#include "destroy_resources.h"

BitmapGarbageArray *create_bitmap_garbage_array(void) {
        BitmapGarbageArray *garbage_array = (BitmapGarbageArray *)malloc(sizeof(BitmapGarbageArray));

        if (!garbage_array)
                return NULL;
        
        garbage_array->array = (ALLEGRO_BITMAP **)malloc(ARRAY_SIZE * sizeof(ALLEGRO_BITMAP *));

        if (!garbage_array->array)
                return NULL;

        garbage_array->array_size = 0;

        return garbage_array;
}

void insert_bitmap_array(BitmapGarbageArray *bitmap_garbage_array, ALLEGRO_BITMAP *bitmap) {
        (bitmap_garbage_array->array_size)++;
        bitmap_garbage_array->array[bitmap_garbage_array->array_size - 1] = bitmap;
}

void destroy_bitmap_garbage_array(BitmapGarbageArray *bitmap_garbage_array) {
        for (unsigned int i = 0; i < bitmap_garbage_array->array_size; i++)
                al_destroy_bitmap(bitmap_garbage_array->array[i]);

        free(bitmap_garbage_array);
}

SampleGarbageArray *create_sample_garbage_array(void) {
        SampleGarbageArray *garbage_array = (SampleGarbageArray *)malloc(sizeof(SampleGarbageArray));

        if (!garbage_array)
                return NULL;
        
        garbage_array->array = (ALLEGRO_SAMPLE **)malloc(ARRAY_SIZE * sizeof(ALLEGRO_SAMPLE *));

        if (!garbage_array->array)
                return NULL;

        garbage_array->array_size = 0;

        return garbage_array;
}

void insert_sample_array(SampleGarbageArray *sample_garbage_array, ALLEGRO_SAMPLE *sample) {
        (sample_garbage_array->array_size)++;
        sample_garbage_array->array[sample_garbage_array->array_size - 1] = sample;
}

void destroy_sample_garbage_array(SampleGarbageArray *sample_garbage_array) {
        for (unsigned int i = 0; i < sample_garbage_array->array_size; i++)
                al_destroy_sample(sample_garbage_array->array[i]);

        free(sample_garbage_array);
}

void destroy_samples(
        ALLEGRO_SAMPLE *menu_sample, ALLEGRO_SAMPLE *menu_confirm_sample, 
        ALLEGRO_SAMPLE *menu_select_sample, ALLEGRO_SAMPLE *cancel_sound_sample, 
        ALLEGRO_SAMPLE *character_select_welcome_sample, ALLEGRO_SAMPLE *character_select_sample, 
        ALLEGRO_SAMPLE *character_select_confirm_sample, ALLEGRO_SAMPLE *pause_sound_effect,
        ALLEGRO_SAMPLE *dark_forest_sample, ALLEGRO_SAMPLE *abandoned_factory_sample,
        ALLEGRO_SAMPLE *calm_forest_sample, ALLEGRO_SAMPLE *rumble_end_sample
) {
        al_destroy_sample(menu_sample);
        al_destroy_sample(menu_confirm_sample);
        al_destroy_sample(menu_select_sample);
        al_destroy_sample(character_select_welcome_sample);
        al_destroy_sample(character_select_sample);
        al_destroy_sample(character_select_confirm_sample);
        al_destroy_sample(cancel_sound_sample);
        al_destroy_sample(pause_sound_effect);
        al_destroy_sample(dark_forest_sample);
        al_destroy_sample(abandoned_factory_sample);
        al_destroy_sample(calm_forest_sample);
        al_destroy_sample(rumble_end_sample);
}

void destroy_fonts(
        ALLEGRO_FONT *menu_header_font, ALLEGRO_FONT *menu_options_font, 
        ALLEGRO_FONT *character_select_header_font, ALLEGRO_FONT *character_select_display_name_font
) {
        al_destroy_font(menu_header_font);
        al_destroy_font(menu_options_font);
        al_destroy_font(character_select_header_font);
        al_destroy_font(character_select_display_name_font);
}

void destroy_bitmaps(
        ALLEGRO_BITMAP *window_icon, ALLEGRO_BITMAP *viking_icon, 
        ALLEGRO_BITMAP *knight_icon, ALLEGRO_BITMAP *spearwoman_icon, 
        ALLEGRO_BITMAP *fire_warrior_icon, ALLEGRO_BITMAP *stage_select_arrow_icon, 
        ALLEGRO_BITMAP *stage_dark_forest, ALLEGRO_BITMAP *stage_abandoned_factory,
        ALLEGRO_BITMAP *stage_calm_forest
) {
        al_destroy_bitmap(window_icon);
        al_destroy_bitmap(viking_icon);
        al_destroy_bitmap(knight_icon);
        al_destroy_bitmap(spearwoman_icon);
        al_destroy_bitmap(fire_warrior_icon);
        al_destroy_bitmap(stage_select_arrow_icon);
        al_destroy_bitmap(stage_dark_forest);
        al_destroy_bitmap(stage_abandoned_factory);
        al_destroy_bitmap(stage_calm_forest);
}

void destroy_spriteset(ALLEGRO_BITMAP **spriteset, unsigned int num_frames) {
        for (unsigned int i = 0; i < num_frames; i++)
                al_destroy_bitmap(spriteset[i]);

        free(spriteset);
}