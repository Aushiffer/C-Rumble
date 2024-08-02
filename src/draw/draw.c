#include "draw.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/display.h>

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
        al_draw_scaled_bitmap(knight_icon, 0.0, 0.0, al_get_bitmap_width(knight_icon), al_get_bitmap_height(knight_icon), 138, 356, 95, 95, ALLEGRO_FLIP_HORIZONTAL); // coloca os ícones (P1)
        al_draw_scaled_bitmap(spearwoman_icon, 0.0, 0.0, al_get_bitmap_width(spearwoman_icon), al_get_bitmap_height(spearwoman_icon), 248, 356, 95, 95, 0); // 
        al_draw_scaled_bitmap(fire_warrior_icon, 0.0, 0.0, al_get_bitmap_width(fire_warrior_icon), al_get_bitmap_height(fire_warrior_icon), 355, 356, 95, 95, 0); //

        al_draw_scaled_bitmap(viking_icon, 0.0, 0.0, al_get_bitmap_width(viking_icon), al_get_bitmap_height(viking_icon), al_get_display_width(display) - 452, 356, 95, 95, ALLEGRO_FLIP_HORIZONTAL);                       //
        al_draw_scaled_bitmap(knight_icon, 0.0, 0.0, al_get_bitmap_width(knight_icon), al_get_bitmap_height(knight_icon), al_get_display_width(display) - 345, 356, 95, 95, 0);                       // coloca os ícones (P2)
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
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, 256, 512, ALLEGRO_ALIGN_CENTRE, "RYU");

                        break;

                case 1:
                        al_draw_rectangle(138, 356, 238, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, 256, 512, ALLEGRO_ALIGN_CENTRE, "KEN");

                        break;

                case 2:
                        al_draw_rectangle(248, 356, 345, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, 256, 512, ALLEGRO_ALIGN_CENTRE, "GUILE");

                        break;

                case 3:
                        al_draw_rectangle(355, 356, 452, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, 256, 512, ALLEGRO_ALIGN_CENTRE, "VEGA");

                        break;
        }

        switch (game_states->character_select_nav_p2) {
                case 0:
                        al_draw_rectangle(al_get_display_width(display) - 355, 356, al_get_display_width(display) - 452, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, al_get_display_width(display) - 256, 512, ALLEGRO_ALIGN_CENTRE, "RYU");

                        break;

                case 1:
                        al_draw_rectangle(al_get_display_width(display) - 248, 356, al_get_display_width(display) - 345, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, al_get_display_width(display) - 256, 512, ALLEGRO_ALIGN_CENTRE, "KEN");

                        break;

                case 2:
                        al_draw_rectangle(al_get_display_width(display) - 138, 356, al_get_display_width(display) - 238, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, al_get_display_width(display) - 256, 512, ALLEGRO_ALIGN_CENTRE, "GUILE");

                        break;

                case 3:
                        al_draw_rectangle(al_get_display_width(display) - 32, 356, al_get_display_width(display) - 128, 452, COLOR_WHITE, 2.0);
                        al_draw_text(character_select_display_name_font, COLOR_WHITE, al_get_display_width(display) - 256, 512, ALLEGRO_ALIGN_CENTRE, "VEGA");

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
                        al_draw_text(stage_display_name_font, COLOR_WHITE, (float)al_get_display_width(display) / 2 - 8, (float)al_get_display_height(display) / 2 + 4, ALLEGRO_ALIGN_CENTRE, "SUZAKU CASTLE");

                        break;

                case 1:
                        al_draw_text(stage_display_name_font, COLOR_WHITE, (float)al_get_display_width(display) / 2 - 8, (float)al_get_display_height(display) / 2 + 4, ALLEGRO_ALIGN_CENTRE, "BATTLE HARBOR");

                        break;

                case 2:
                        al_draw_text(stage_display_name_font, COLOR_WHITE, (float)al_get_display_width(display) / 2 - 8, (float)al_get_display_height(display) / 2 + 4, ALLEGRO_ALIGN_CENTRE, "AIR FORCE BASE");

                        break;

                case 3:
                        al_draw_text(stage_display_name_font, COLOR_WHITE, (float)al_get_display_width(display) / 2 - 8, (float)al_get_display_height(display) / 2 + 4, ALLEGRO_ALIGN_CENTRE, "MESÓN DE LA TABERNA");

                        break;
        }
}

void draw_stages(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *stage1_bitmap, ALLEGRO_BITMAP *stage2_bitmap, ALLEGRO_BITMAP *stage3_bitmap, ALLEGRO_BITMAP *stage4_bitmap, GameStates *game_states) {
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

                case 2:
                        al_draw_scaled_bitmap(
                                stage3_bitmap, 0.0, 
                                0.0, al_get_bitmap_width(stage3_bitmap), 
                                al_get_bitmap_height(stage3_bitmap), 0.0, 
                                0.0, al_get_display_width(display), al_get_display_height(display), 
                                0
                        );

                        break;

                case 3:
                        al_draw_scaled_bitmap(
                                stage4_bitmap, 0.0, 
                                0.0, al_get_bitmap_width(stage4_bitmap), 
                                al_get_bitmap_height(stage4_bitmap), 0.0, 
                                0.0, al_get_display_width(display), al_get_display_height(display), 
                                0
                        );

                        break;
        }
}

void draw_hi_punch_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames) {
        if (player->is_running_left || player->is_running_right || player->is_blocking || player->is_kicking || player->is_crouching) {
                player->is_punching = 0;

                return;
        }
        
        if ((*time_frame) >= frame_duration) {
                (*time_frame) = 0;
                (*current_frame) = ((*current_frame) + 1) % num_frames;

                if ((*current_frame) == 0)
                        player->is_punching = 0;
        }

        if (player->direction_facing == 0)
                al_draw_bitmap(
                        player->hi_punch_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->hi_punch_spriteset[(*current_frame)]) / 2 + 64,
                        player->hitbox_upper->hitbox_y, 0
                );
        else
                al_draw_bitmap(
                        player->hi_punch_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->hi_punch_spriteset[(*current_frame)]) / 2 - 64,
                        player->hitbox_upper->hitbox_y, ALLEGRO_FLIP_HORIZONTAL
                );
}

void draw_lo_punch_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames) {
        if (player->is_running_left || player->is_running_right || player->is_blocking || player->is_kicking) {
                player->is_punching = 0;

                return;
        }
        
        if ((*time_frame) >= frame_duration) {
                (*time_frame) = 0;
                (*current_frame) = ((*current_frame) + 1) % num_frames;

                if ((*current_frame) == 0)
                        player->is_punching = 0;
        }

        if (player->direction_facing == 0)
                al_draw_bitmap(
                        player->lo_punch_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->lo_punch_spriteset[(*current_frame)]) / 2,
                        player->hitbox_upper->hitbox_y + (float)al_get_bitmap_width(player->lo_punch_spriteset[(*current_frame)]) / 2 - 12, 0
                );
        else
                al_draw_bitmap(
                        player->lo_punch_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->lo_punch_spriteset[(*current_frame)]) / 2,
                        player->hitbox_upper->hitbox_y + (float)al_get_bitmap_width(player->lo_punch_spriteset[(*current_frame)]) / 2 - 12, ALLEGRO_FLIP_HORIZONTAL
                );
}

void draw_air_punch_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames) {
        if (player->is_blocking || player->is_kicking || player->on_ground) {
                player->is_punching = 0;

                return;
        }

        if ((*time_frame) >= frame_duration) {
                (*time_frame) = 0;
                (*current_frame) = ((*current_frame) + 1) % num_frames;

                if ((*current_frame) == 0)
                        player->is_punching = 0;
        }

        if (player->direction_facing == 0) {
                al_draw_bitmap(
                        player->air_punch_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->air_punch_spriteset[(*current_frame)]) / 2,
                        player->hitbox_upper->hitbox_y, 0
                );
        } else if (player->direction_facing == 1) {
                al_draw_bitmap(
                        player->air_punch_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->air_punch_spriteset[(*current_frame)]) / 2,
                        player->hitbox_upper->hitbox_y, ALLEGRO_FLIP_HORIZONTAL
                );
        }        
}

void draw_hi_kick_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames) {
        if (player->is_running_left || player->is_running_right || player->is_blocking || player->is_crouching || player->is_punching) {
                player->is_kicking = 0;

                return;
        }
        
        if ((*time_frame) >= frame_duration) {
                (*time_frame) = 0;
                (*current_frame) = ((*current_frame) + 1) % num_frames;

                if ((*current_frame) == 0)
                        player->is_kicking = 0;
        }
        
        if (player->direction_facing == 0) {
                al_draw_bitmap(
                        player->hi_kick_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->hi_kick_spriteset[(*current_frame)]) / 2,
                        player->hitbox_upper->hitbox_y, 0
                );
        } else if (player->direction_facing == 1) {
                al_draw_bitmap(
                        player->hi_kick_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->hi_kick_spriteset[(*current_frame)]) / 2,
                        player->hitbox_upper->hitbox_y, ALLEGRO_FLIP_HORIZONTAL
                );
        }
}

void draw_lo_kick_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames) {
        if (player->is_running_left || player->is_running_right || player->is_blocking || player->is_punching) {
                player->is_kicking = 0;

                return;
        }
        
        if ((*time_frame) >= frame_duration) {
                (*time_frame) = 0;
                (*current_frame) = ((*current_frame) + 1) % num_frames;

                if ((*current_frame) == 0)
                        player->is_kicking = 0;
        }
        
        if (player->direction_facing == 0) {
                al_draw_bitmap(
                        player->lo_kick_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->lo_kick_spriteset[(*current_frame)]) / 2,
                        player->hitbox_upper->hitbox_y + (float)al_get_bitmap_height(player->lo_kick_spriteset[(*current_frame)]) / 2, 0
                );
        } else if (player->direction_facing == 1) {
                al_draw_bitmap(
                        player->lo_kick_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->lo_kick_spriteset[(*current_frame)]) / 2,
                        player->hitbox_upper->hitbox_y + (float)al_get_bitmap_height(player->lo_kick_spriteset[(*current_frame)]) / 2, ALLEGRO_FLIP_HORIZONTAL
                );
        }
}

void draw_running_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int *current_frame_idle, unsigned int num_frames) {
        if ((*time_frame) >= frame_duration) {
                (*time_frame) = 0;
                (*current_frame) = ((*current_frame) + 1) % num_frames;
        }

        if (player->is_running_left) {
                if (!player->is_running_right)
                        al_draw_bitmap(
                                player->running_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->running_spriteset[(*current_frame)]) / 2, 
                                player->hitbox_upper->hitbox_y, ALLEGRO_FLIP_HORIZONTAL
                        );
                else if (player->is_running_right)
                        al_draw_bitmap(
                                player->idle_spriteset[(*current_frame_idle)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->idle_spriteset[(*current_frame_idle)]) / 2, 
                                player->hitbox_upper->hitbox_y, 0
                        );  
        } else if (player->is_running_right) {
                if (!player->is_running_left)
                        al_draw_bitmap(
                                player->running_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->running_spriteset[(*current_frame)]) / 2, 
                                player->hitbox_upper->hitbox_y, 0
                        );
                else if (player->is_running_left)
                        al_draw_bitmap(
                                player->idle_spriteset[(*current_frame_idle)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->idle_spriteset[(*current_frame_idle)]) / 2, 
                                player->hitbox_upper->hitbox_y, 0
                        );
        }
}

void draw_idle_animation(Fighter *player, unsigned int current_frame) {
        if (player->direction_facing == 0) {
                al_draw_bitmap(
                        player->idle_spriteset[current_frame], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->idle_spriteset[current_frame]) / 2, 
                        player->hitbox_upper->hitbox_y, 0
                );
        } else {
                al_draw_bitmap(
                        player->idle_spriteset[current_frame], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->idle_spriteset[current_frame]) / 2, 
                        player->hitbox_upper->hitbox_y, ALLEGRO_FLIP_HORIZONTAL
                );
        }
}

void draw_blocking_animation(Fighter *player) {
        if (player->direction_facing == 0)
                al_draw_bitmap(
                        player->hi_block_spriteset[0], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->hi_block_spriteset[0]) / 2, 
                        player->hitbox_upper->hitbox_y, 0
                );
        else
                al_draw_bitmap(
                        player->hi_block_spriteset[0], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->hi_block_spriteset[0]) / 2, 
                        player->hitbox_upper->hitbox_y, ALLEGRO_FLIP_HORIZONTAL
                );
}

void draw_lo_blocking_animation(Fighter *player) {
        if (player->direction_facing == 0)
                al_draw_bitmap(
                        player->lo_block_spriteset[0], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->lo_block_spriteset[0]) / 2, 
                        player->hitbox_upper->hitbox_y + (float)al_get_bitmap_width(player->lo_block_spriteset[0]) / 2, 0
                );
        else
                al_draw_bitmap(
                        player->lo_block_spriteset[0], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->lo_block_spriteset[0]) / 2, 
                        player->hitbox_upper->hitbox_y + (float)al_get_bitmap_width(player->lo_block_spriteset[0]) / 2, ALLEGRO_FLIP_HORIZONTAL
                );
}

void draw_crouching_animation(Fighter *player) {
        if (!player->is_blocking) {
                if (player->direction_facing == 0)
                        al_draw_bitmap(
                                player->crouch_spriteset[0], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->crouch_spriteset[0]) / 2, 
                                player->hitbox_upper->hitbox_y + (float)al_get_bitmap_width(player->crouch_spriteset[0]) / 2, 0
                        );
                else
                        al_draw_bitmap(
                                player->crouch_spriteset[0], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->crouch_spriteset[0]) / 2, 
                                player->hitbox_upper->hitbox_y + (float)al_get_bitmap_width(player->crouch_spriteset[0]) / 2, ALLEGRO_FLIP_HORIZONTAL
                        );
        }
}

void draw_jumping_animation(Fighter *player, float frame_duration, float *time_frame, unsigned int *current_frame, unsigned int num_frames) {
        if ((*time_frame) >= frame_duration) {
                (*time_frame) = 0;
                (*current_frame) = ((*current_frame) + 1) % num_frames;
        }

        if (player->direction_facing == 0)
                al_draw_bitmap(
                        player->jump_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->jump_spriteset[(*current_frame)]) / 2, 
                        player->hitbox_upper->hitbox_y, 0
                );
        else
                al_draw_bitmap(
                        player->jump_spriteset[(*current_frame)], player->hitbox_upper->hitbox_x - (float)al_get_bitmap_width(player->jump_spriteset[(*current_frame)]) / 2, 
                        player->hitbox_upper->hitbox_y, ALLEGRO_FLIP_HORIZONTAL
                );
}

void draw_health_bars(Fighter *player1, Fighter *player2, ALLEGRO_DISPLAY *display) {
        const float health_bar_width = 512.0;

        al_draw_filled_rectangle(16, 32, health_bar_width, 64, COLOR_LIGHT_RED);
        al_draw_filled_rectangle((float)al_get_display_width(display) - 16, 32, (float)al_get_display_width(display) - health_bar_width, 64, COLOR_LIGHT_RED);

        if (player1->health > 0)
                al_draw_filled_rectangle(16, 32, health_bar_width * (player1->health / MAX_HEALTH), 64, COLOR_YELLOW);

        if (player2->health > 0) {
                float player2_health_bar_width = health_bar_width * (player2->health / MAX_HEALTH);
                float player2_health_bar_start_x = (float)al_get_display_width(display) - 16 - player2_health_bar_width;
                
                al_draw_filled_rectangle(player2_health_bar_start_x + 16, 32, player2_health_bar_start_x + player2_health_bar_width, 64, COLOR_YELLOW);
        }
}

void draw_stamina_bars(Fighter *player1, Fighter *player2, ALLEGRO_DISPLAY *display) {
        const float stamina_bar_width = 512.0;

        al_draw_filled_rectangle(16, 76, stamina_bar_width, 96, COLOR_LIGHT_RED);
        al_draw_filled_rectangle((float)al_get_display_width(display) - 16, 76, (float)al_get_display_width(display) - stamina_bar_width, 96, COLOR_LIGHT_RED);

        if (player1->stamina > 0)
                al_draw_filled_rectangle(16, 76, stamina_bar_width * (player1->stamina / MAX_STAMINA), 96, COLOR_LIGHT_GREEN);

        if (player2->stamina > 0) {
                float player2_stamina_bar_width = stamina_bar_width * (player2->stamina / MAX_STAMINA);
                float player2_stamina_bar_start_x = (float)al_get_display_width(display) - 16 - player2_stamina_bar_width;
                
                al_draw_filled_rectangle(player2_stamina_bar_start_x + 16, 76, player2_stamina_bar_start_x + player2_stamina_bar_width, 96, COLOR_LIGHT_GREEN);
        }
}

void draw_rumble_header(GameStates *game_states, ALLEGRO_DISPLAY *display, ALLEGRO_FONT *rumble_display_character_name_font, ALLEGRO_FONT *character_select_header_font, char *wins_text_p1, char *wins_text_p2) {
        switch (game_states->rumble_fighter_p1) {
                case 0:
                        al_draw_text(rumble_display_character_name_font, COLOR_BLACK, 28, 116, ALLEGRO_ALIGN_LEFT, "RYU");
                        al_draw_text(rumble_display_character_name_font, COLOR_WHITE, 32, 116, ALLEGRO_ALIGN_LEFT, "RYU");

                        break;
                case 1:
                        al_draw_text(rumble_display_character_name_font, COLOR_BLACK, 28, 116, ALLEGRO_ALIGN_LEFT, "KEN");
                        al_draw_text(rumble_display_character_name_font, COLOR_WHITE, 32, 116, ALLEGRO_ALIGN_LEFT, "KEN");

                        break;
                case 2:
                        al_draw_text(rumble_display_character_name_font, COLOR_BLACK, 28, 116, ALLEGRO_ALIGN_LEFT, "GUILE");
                        al_draw_text(rumble_display_character_name_font, COLOR_WHITE, 32, 116, ALLEGRO_ALIGN_LEFT, "GUILE");

                        break;
                case 3:
                        al_draw_text(rumble_display_character_name_font, COLOR_BLACK, 28, 116, ALLEGRO_ALIGN_LEFT, "VEGA");
                        al_draw_text(rumble_display_character_name_font, COLOR_WHITE, 32, 116, ALLEGRO_ALIGN_LEFT, "VEGA");

                        break;
        }

        switch (game_states->rumble_fighter_p2) {
                case 0:
                        al_draw_text(rumble_display_character_name_font, COLOR_BLACK, (float)al_get_display_width(display) - 28, 116, ALLEGRO_ALIGN_RIGHT, "RYU");
                        al_draw_text(rumble_display_character_name_font, COLOR_WHITE, (float)al_get_display_width(display) - 32, 116, ALLEGRO_ALIGN_RIGHT, "RYU");

                        break;
                case 1:
                        al_draw_text(rumble_display_character_name_font, COLOR_BLACK, (float)al_get_display_width(display) - 28, 116, ALLEGRO_ALIGN_RIGHT, "KEN");
                        al_draw_text(rumble_display_character_name_font, COLOR_WHITE, (float)al_get_display_width(display) - 32, 116, ALLEGRO_ALIGN_RIGHT, "KEN");

                        break;
                case 2:
                        al_draw_text(rumble_display_character_name_font, COLOR_BLACK, (float)al_get_display_width(display) - 28, 116, ALLEGRO_ALIGN_RIGHT, "GUILE");
                        al_draw_text(rumble_display_character_name_font, COLOR_WHITE, (float)al_get_display_width(display) - 32, 116, ALLEGRO_ALIGN_RIGHT, "GUILE");

                        break;
                case 3:
                        al_draw_text(rumble_display_character_name_font, COLOR_BLACK, (float)al_get_display_width(display) - 28, 116, ALLEGRO_ALIGN_RIGHT, "VEGA");
                        al_draw_text(rumble_display_character_name_font, COLOR_WHITE, (float)al_get_display_width(display) - 32, 116, ALLEGRO_ALIGN_RIGHT, "VEGA");

                        break;
        }

        al_draw_text(rumble_display_character_name_font, COLOR_BLACK, 28, 148, ALLEGRO_ALIGN_LEFT, wins_text_p1);
        al_draw_text(rumble_display_character_name_font, COLOR_WHITE, 32, 148, ALLEGRO_ALIGN_LEFT, wins_text_p1);
        al_draw_text(rumble_display_character_name_font, COLOR_BLACK, (float)al_get_display_width(display) - 28, 148, ALLEGRO_ALIGN_RIGHT, wins_text_p2);
        al_draw_text(rumble_display_character_name_font, COLOR_WHITE, (float)al_get_display_width(display) - 32, 148, ALLEGRO_ALIGN_RIGHT, wins_text_p2);
        al_draw_text(character_select_header_font, COLOR_BLACK, (float)al_get_display_width(display) / 2 - 4, 32, ALLEGRO_ALIGN_CENTRE, "VS.");
        al_draw_text(character_select_header_font, COLOR_WHITE, (float)al_get_display_width(display) / 2 + 4, 32, ALLEGRO_ALIGN_CENTRE, "VS.");
}

void draw_rumble_end(GameStates *game_states, ALLEGRO_DISPLAY *display, ALLEGRO_FONT *header_font, ALLEGRO_FONT *prompt_input_font, Fighter *player1, Fighter *player2) {
        al_clear_to_color(COLOR_WHITE);
        al_draw_text(header_font, COLOR_BLACK, (float)al_get_display_width(display) / 2 + 8, 128, ALLEGRO_ALIGN_CENTRE, "GAME OVER!");
        al_draw_text(header_font, COLOR_ORANGE, (float)al_get_display_width(display) / 2, 128, ALLEGRO_ALIGN_CENTRE, "GAME OVER!");

        if ((player1->rounds_won == 2 && player2->rounds_won == 1) || (player1->rounds_won == 2 && player2->rounds_won == 0)) {
                al_draw_text(header_font, COLOR_BLACK, (float)al_get_display_width(display) / 2 + 8, 356, ALLEGRO_ALIGN_CENTRE, "P1 WINS!");
                al_draw_text(header_font, COLOR_ORANGE, (float)al_get_display_width(display) / 2, 356, ALLEGRO_ALIGN_CENTRE, "P1 WINS!");
        } else if ((player2->rounds_won == 2 && player1->rounds_won == 1) || (player2->rounds_won == 2 && player1->rounds_won == 0)) {
                al_draw_text(header_font, COLOR_BLACK, (float)al_get_display_width(display) / 2 + 8, 356, ALLEGRO_ALIGN_CENTRE, "P2 WINS!");
                al_draw_text(header_font, COLOR_ORANGE, (float)al_get_display_width(display) / 2, 356, ALLEGRO_ALIGN_CENTRE, "P2 WINS!");
        } else {
                al_draw_text(header_font, COLOR_BLACK, (float)al_get_display_width(display) / 2 + 8, 356, ALLEGRO_ALIGN_CENTRE, "DRAW!");
                al_draw_text(header_font, COLOR_ORANGE, (float)al_get_display_width(display) / 2, 356, ALLEGRO_ALIGN_CENTRE, "DRAW!");
        }

        al_draw_text(prompt_input_font, COLOR_BLACK, (float)al_get_display_width(display) / 2 + 4, (float)al_get_display_height(display) - 128, ALLEGRO_ALIGN_CENTRE, "PRESS ENTER");
        al_draw_text(prompt_input_font, COLOR_ORANGE, (float)al_get_display_width(display) / 2, (float)al_get_display_height(display) - 128, ALLEGRO_ALIGN_CENTRE, "PRESS ENTER");

        game_states->rumble = 0;
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