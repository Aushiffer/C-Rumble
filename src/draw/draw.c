#include "draw.h"

void draw_menu(ALLEGRO_FONT *menu_header_font, ALLEGRO_FONT *menu_options_font, ALLEGRO_DISPLAY *display, GameStates *game_states) {
        al_clear_to_color(COLOR_DARK_BLUE);
        al_draw_text(menu_header_font, COLOR_WHITE, (float)al_get_display_width(display) / 2, 64, ALLEGRO_ALIGN_CENTRE, "C-RUMBLE");

        switch (game_states->menu_select) {
                case 0:
                        al_draw_text(menu_options_font, COLOR_WHITE, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 32, ALLEGRO_ALIGN_CENTRE, "PLAY");
                        al_draw_text(menu_options_font, COLOR_LIGHT_GRAY, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 96, ALLEGRO_ALIGN_CENTRE, "EXIT");

                        break;

                case 1:
                        al_draw_text(menu_options_font, COLOR_LIGHT_GRAY, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 32, ALLEGRO_ALIGN_CENTRE, "PLAY");
                        al_draw_text(menu_options_font, COLOR_WHITE, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 96, ALLEGRO_ALIGN_CENTRE, "EXIT");

                        break;
        }
}

void draw_character_select(
        ALLEGRO_FONT *character_select_header_font, ALLEGRO_FONT *player_indicator_font, 
        ALLEGRO_FONT *character_select_display_name_font, ALLEGRO_DISPLAY *display, 
        ALLEGRO_BITMAP *viking_icon, ALLEGRO_BITMAP *knight_icon, 
        ALLEGRO_BITMAP *spearwoman_icon, ALLEGRO_BITMAP *fire_warrior_icon,
        GameStates *game_states)
{
        al_clear_to_color(COLOR_TOMATO);
        al_draw_text(character_select_header_font, COLOR_WHITE, (float)al_get_display_width(display) / 2, 128, ALLEGRO_ALIGN_CENTRE, "CHOOSE YOUR CHARACTER");
        al_draw_text(player_indicator_font, COLOR_WHITE, 256, 256, ALLEGRO_ALIGN_CENTRE, "1P");
        al_draw_text(player_indicator_font, COLOR_WHITE, (float)al_get_display_width(display) - 256, 256, ALLEGRO_ALIGN_CENTRE, "2P");
                                
        al_draw_scaled_bitmap(viking_icon, 0.0, 0.0, al_get_bitmap_width(viking_icon), al_get_bitmap_height(viking_icon), 32, 356, 95, 95, 0);                      //
        al_draw_scaled_bitmap(knight_icon, 0.0, 0.0, al_get_bitmap_width(knight_icon), al_get_bitmap_height(knight_icon), 138, 356, 95, 95, 0); // coloca os ícones (P1)
        al_draw_scaled_bitmap(spearwoman_icon, 0.0, 0.0, al_get_bitmap_width(spearwoman_icon), al_get_bitmap_height(spearwoman_icon), 248, 356, 95, 95, 0); // 
        al_draw_scaled_bitmap(fire_warrior_icon, 0.0, 0.0, al_get_bitmap_width(fire_warrior_icon), al_get_bitmap_height(fire_warrior_icon), 355, 356, 95, 95, 0); //

        al_draw_scaled_bitmap(viking_icon, 0.0, 0.0, al_get_bitmap_width(viking_icon), al_get_bitmap_height(viking_icon), al_get_display_width(display) - 452, 356, 95, 95, ALLEGRO_FLIP_HORIZONTAL);                       //
        al_draw_scaled_bitmap(knight_icon, 0.0, 0.0, al_get_bitmap_width(knight_icon), al_get_bitmap_height(knight_icon), al_get_display_width(display) - 345, 356, 95, 95, ALLEGRO_FLIP_HORIZONTAL);                       // coloca os ícones (P2)
        al_draw_scaled_bitmap(spearwoman_icon, 0.0, 0.0, al_get_bitmap_width(spearwoman_icon), al_get_bitmap_height(spearwoman_icon), al_get_display_width(display) - 238, 356, 95, 95, ALLEGRO_FLIP_HORIZONTAL);           //
        al_draw_scaled_bitmap(fire_warrior_icon, 0.0, 0.0, al_get_bitmap_width(fire_warrior_icon), al_get_bitmap_height(fire_warrior_icon), al_get_display_width(display) - 128, 356, 95, 95, ALLEGRO_FLIP_HORIZONTAL);     //

        al_draw_rectangle(32, 356, 128, 452, COLOR_BLACK, 2.0);  //
        al_draw_rectangle(138, 356, 238, 452, COLOR_BLACK, 2.0); // placeholders dos ícones dos personagens (P1)
        al_draw_rectangle(248, 356, 345, 452, COLOR_BLACK, 2.0); //
        al_draw_rectangle(355, 356, 452, 452, COLOR_BLACK, 2.0); //

        al_draw_rectangle(al_get_display_width(display) - 355, 356, al_get_display_width(display) - 452, 452, COLOR_BLACK, 2.0); //
        al_draw_rectangle(al_get_display_width(display) - 248, 356, al_get_display_width(display) - 345, 452, COLOR_BLACK, 2.0); // placeholders dos ícones dos personagens (P2)
        al_draw_rectangle(al_get_display_width(display) - 138, 356, al_get_display_width(display) - 238, 452, COLOR_BLACK, 2.0); //
        al_draw_rectangle(al_get_display_width(display) - 32, 356, al_get_display_width(display) - 128, 452, COLOR_BLACK, 2.0);  //

        switch (game_states->character_select_nav_p1) {
                case 0:
                        al_draw_rectangle(32, 356, 128, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, 256, 512, ALLEGRO_ALIGN_CENTRE, "VIKING");

                        break;

                case 1:
                        al_draw_rectangle(138, 356, 238, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, 256, 512, ALLEGRO_ALIGN_CENTRE, "KNIGHT");

                        break;

                case 2:
                        al_draw_rectangle(248, 356, 345, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, 256, 512, ALLEGRO_ALIGN_CENTRE, "SPEARWOMAN");

                        break;

                case 3:
                        al_draw_rectangle(355, 356, 452, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, 256, 512, ALLEGRO_ALIGN_CENTRE, "FIRE WARRIOR");

                        break;
        }

        switch (game_states->character_select_nav_p2) {
                case 0:
                        al_draw_rectangle(al_get_display_width(display) - 355, 356, al_get_display_width(display) - 452, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, al_get_display_width(display) - 256, 512, ALLEGRO_ALIGN_CENTRE, "VIKING");

                        break;

                case 1:
                        al_draw_rectangle(al_get_display_width(display) - 248, 356, al_get_display_width(display) - 345, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, al_get_display_width(display) - 256, 512, ALLEGRO_ALIGN_CENTRE, "KNIGHT");

                        break;

                case 2:
                        al_draw_rectangle(al_get_display_width(display) - 138, 356, al_get_display_width(display) - 238, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, al_get_display_width(display) - 256, 512, ALLEGRO_ALIGN_CENTRE, "SPEARWOMAN");

                        break;

                case 3:
                        al_draw_rectangle(al_get_display_width(display) - 32, 356, al_get_display_width(display) - 128, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, al_get_display_width(display) - 256, 512, ALLEGRO_ALIGN_CENTRE, "FIRE WARRIOR");

                        break;
        }
}

void draw_stage_select(ALLEGRO_FONT *header_font, ALLEGRO_FONT *stage_display_name_font, ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *stage_select_arrow_icon, GameStates *game_states) {
        al_clear_to_color(COLOR_DARK_GREEN);
        al_draw_text(header_font, al_map_rgb(255, 255, 255), (float)al_get_display_width(display) / 2, 128, ALLEGRO_ALIGN_CENTRE, "STAGE SELECTION");
        al_draw_scaled_bitmap(stage_select_arrow_icon, 0.0, 0.0, al_get_bitmap_width(stage_select_arrow_icon), al_get_bitmap_height(stage_select_arrow_icon), (float)al_get_display_width(display) / 2 + 256, (float)al_get_display_height(display) / 2, 64, 48, 0);
        al_draw_scaled_bitmap(stage_select_arrow_icon, 0.0, 0.0, al_get_bitmap_width(stage_select_arrow_icon), al_get_bitmap_height(stage_select_arrow_icon), (float)al_get_display_width(display) / 2 - 356, (float)al_get_display_height(display) / 2, 64, 48, ALLEGRO_FLIP_HORIZONTAL);

        switch (game_states->stage_select_nav) {
                case 0:
                        al_draw_text(stage_display_name_font, COLOR_WHITE, (float)al_get_display_width(display) / 2 - 8, (float)al_get_display_height(display) / 2 + 4, ALLEGRO_ALIGN_CENTRE, "DARK FOREST");

                        break;

                case 1:
                        al_draw_text(stage_display_name_font, COLOR_WHITE, (float)al_get_display_width(display) / 2 - 8, (float)al_get_display_height(display) / 2 + 4, ALLEGRO_ALIGN_CENTRE, "ABANDONED FACTORY");

                        break;
        }
}

void draw_stage(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *stage1_bitmap, ALLEGRO_BITMAP *stage2_bitmap, GameStates *game_states) {
        switch (game_states->stage_select_nav) {
                case 0:
                        al_draw_scaled_bitmap(
                                stage1_bitmap, 0.0, 
                                0.0, al_get_bitmap_width(stage1_bitmap), 
                                al_get_bitmap_height(stage1_bitmap), 0.0, 
                                0.0, al_get_display_width(display), al_get_display_height(display), 
                                0
                        );

                        break;

                case 1:
                        al_draw_scaled_bitmap(
                                stage2_bitmap, 0.0, 
                                0.0, al_get_bitmap_width(stage2_bitmap), 
                                al_get_bitmap_height(stage2_bitmap), 0.0, 
                                0.0, al_get_display_width(display), al_get_display_height(display), 
                                0
                        );

                        break;
        }
}

void draw_hi_punch_animation(Fighter *player, float frame_duration, float *time_animation, unsigned int (*current_frame), unsigned int num_frames) {
        if ((*time_animation) >= frame_duration) {
                (*time_animation) = 0;
                (*current_frame) = ((*current_frame) + 1) % num_frames;

                if ((*current_frame) == 0)
                        player->is_hi_punching = 0;
        }

        al_draw_bitmap(
                player->hi_punch_spriteset[(*current_frame)], player->hitbox->hitbox_x - (float)al_get_bitmap_width(player->hi_punch_spriteset[(*current_frame)]) / 2 + 64,
                player->hitbox->hitbox_y, 0
        );
}

void draw_pause(ALLEGRO_FONT *pause_header_font, ALLEGRO_FONT *pause_options_font, ALLEGRO_DISPLAY *display, GameStates *game_states) {
        al_clear_to_color(COLOR_BLACK);
        al_draw_text(pause_header_font, COLOR_WHITE, (float)al_get_display_width(display) / 2, 64, ALLEGRO_ALIGN_CENTRE, "PAUSE");
                                                
        switch (game_states->rumble_pause_select) {
                case 0:
                        al_draw_text(pause_options_font, COLOR_WHITE, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 - 32, ALLEGRO_ALIGN_CENTRE, "RESUME");
                        al_draw_text(pause_options_font, COLOR_LIGHT_GRAY, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 32, ALLEGRO_ALIGN_CENTRE, "CHARACTER SELECTION");
                        al_draw_text(pause_options_font, COLOR_LIGHT_GRAY, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 96, ALLEGRO_ALIGN_CENTRE, "MAIN MENU");

                        break;

                case 1:
                        al_draw_text(pause_options_font, COLOR_LIGHT_GRAY, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 - 32, ALLEGRO_ALIGN_CENTRE, "RESUME");
                        al_draw_text(pause_options_font, COLOR_WHITE, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 32, ALLEGRO_ALIGN_CENTRE, "CHARACTER SELECTION");
                        al_draw_text(pause_options_font, COLOR_LIGHT_GRAY, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 96, ALLEGRO_ALIGN_CENTRE, "MAIN MENU");

                        break;

                case 2:
                        al_draw_text(pause_options_font, COLOR_LIGHT_GRAY, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 - 32, ALLEGRO_ALIGN_CENTRE, "RESUME");
                        al_draw_text(pause_options_font, COLOR_LIGHT_GRAY, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 32, ALLEGRO_ALIGN_CENTRE, "CHARACTER SELECTION");
                        al_draw_text(pause_options_font, COLOR_WHITE, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 96, ALLEGRO_ALIGN_CENTRE, "MAIN MENU");

                        break;
        }
}