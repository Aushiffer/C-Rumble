#include "draw.h"

void draw_menu(ALLEGRO_FONT *menu_header_font, ALLEGRO_FONT *menu_options_font, ALLEGRO_DISPLAY *display, GameStates *game_states) {
        al_clear_to_color(COLOR_DARK_BLUE);
        al_draw_text(menu_header_font, COLOR_WHITE, (float)al_get_display_width(display) / 2, 128, ALLEGRO_ALIGN_CENTRE, "C-RUMBLE");

        switch (game_states->menu_select) {
                case 0:
                al_draw_text(menu_options_font, COLOR_WHITE, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 64, ALLEGRO_ALIGN_CENTRE, "1P VS. 2P");
                al_draw_text(menu_options_font, COLOR_LIGHT_GRAY, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 128, ALLEGRO_ALIGN_CENTRE, "EXIT");

                break;

                case 1:
                al_draw_text(menu_options_font, COLOR_LIGHT_GRAY, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 64, ALLEGRO_ALIGN_CENTRE, "1P VS. 2P");
                al_draw_text(menu_options_font, COLOR_WHITE, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) / 2 + 128, ALLEGRO_ALIGN_CENTRE, "EXIT");

                break;
        }
}

void draw_character_select(
        ALLEGRO_FONT *character_select_header_font, ALLEGRO_FONT *menu_options_font, 
        ALLEGRO_FONT *character_select_display_name_font, ALLEGRO_DISPLAY *display, 
        ALLEGRO_BITMAP *character_icon1, ALLEGRO_BITMAP *character_icon2, 
        ALLEGRO_BITMAP *character_icon3, ALLEGRO_BITMAP *character_icon4,
        GameStates *game_states
) {
        al_clear_to_color(COLOR_TOMATO);
        al_draw_text(character_select_header_font, COLOR_WHITE, (float)al_get_display_width(display) / 2, 128, ALLEGRO_ALIGN_CENTRE, "CHOOSE YOUR CHARACTER");
        al_draw_text(menu_options_font, COLOR_WHITE, 256, 256, ALLEGRO_ALIGN_CENTRE, "1P");
        al_draw_text(menu_options_font, COLOR_WHITE, (float)al_get_display_width(display) - 256, 256, ALLEGRO_ALIGN_CENTRE, "2P");
                                
        al_draw_scaled_bitmap(character_icon1, 0.0, 0.0, al_get_bitmap_width(character_icon1), al_get_bitmap_height(character_icon1), 32, 356, 95, 95, 0);                      //
        al_draw_scaled_bitmap(character_icon2, 0.0, 0.0, al_get_bitmap_width(character_icon2), al_get_bitmap_height(character_icon2), 138, 356, 95, 95, 0); // coloca os ícones (P1)
        al_draw_scaled_bitmap(character_icon3, 0.0, 0.0, al_get_bitmap_width(character_icon3), al_get_bitmap_height(character_icon3), 248, 356, 95, 95, 0); // 
        al_draw_scaled_bitmap(character_icon4, 0.0, 0.0, al_get_bitmap_width(character_icon4), al_get_bitmap_height(character_icon4), 355, 356, 95, 95, 0); //

        al_draw_scaled_bitmap(character_icon1, 0.0, 0.0, al_get_bitmap_width(character_icon1), al_get_bitmap_height(character_icon1), al_get_display_width(display) - 452, 356, 95, 95, ALLEGRO_FLIP_HORIZONTAL);                       //
        al_draw_scaled_bitmap(character_icon2, 0.0, 0.0, al_get_bitmap_width(character_icon2), al_get_bitmap_height(character_icon2), al_get_display_width(display) - 345, 356, 95, 95, ALLEGRO_FLIP_HORIZONTAL);                       // coloca os ícones (P2)
        al_draw_scaled_bitmap(character_icon3, 0.0, 0.0, al_get_bitmap_width(character_icon3), al_get_bitmap_height(character_icon3), al_get_display_width(display) - 238, 356, 95, 95, ALLEGRO_FLIP_HORIZONTAL);           //
        al_draw_scaled_bitmap(character_icon4, 0.0, 0.0, al_get_bitmap_width(character_icon4), al_get_bitmap_height(character_icon4), al_get_display_width(display) - 128, 356, 95, 95, ALLEGRO_FLIP_HORIZONTAL);     //

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