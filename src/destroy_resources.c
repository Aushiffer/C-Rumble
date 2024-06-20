#include "destroy_resources.h"

void destroy_samples(
        ALLEGRO_SAMPLE *menu_sample, ALLEGRO_SAMPLE *menu_confirm_sample, 
        ALLEGRO_SAMPLE *menu_select_sample, ALLEGRO_SAMPLE *cancel_sound_sample, 
        ALLEGRO_SAMPLE *character_select_welcome_sample, ALLEGRO_SAMPLE *character_select_sample, 
        ALLEGRO_SAMPLE *character_select_confirm_sample, ALLEGRO_SAMPLE *pause_sound_effect,
        ALLEGRO_SAMPLE *dark_forest_sample, ALLEGRO_SAMPLE *abandoned_factory_sample
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
        ALLEGRO_BITMAP *viking_idle_spriteset[], int NUM_IDLE_FRAMES
) {
        al_destroy_bitmap(window_icon);
        al_destroy_bitmap(viking_icon);
        al_destroy_bitmap(knight_icon);
        al_destroy_bitmap(spearwoman_icon);
        al_destroy_bitmap(fire_warrior_icon);
        al_destroy_bitmap(stage_select_arrow_icon);
        al_destroy_bitmap(stage_dark_forest);
        al_destroy_bitmap(stage_abandoned_factory);

        for (int i = 0; i < NUM_IDLE_FRAMES; i++)
                al_destroy_bitmap(viking_idle_spriteset[i]);
}