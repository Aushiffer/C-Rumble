#include "fighter.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/bitmap.h>
#include <allegro5/display.h>

Fighter *create_fighter(
        float fighter_width, float fighter_height, 
        float fighter_x, float fighter_y, 
        float max_x, float max_y, 
        ALLEGRO_BITMAP **idle_spriteset, ALLEGRO_BITMAP **hi_punch_spriteset, 
        ALLEGRO_BITMAP **lo_punch_spriteset, ALLEGRO_BITMAP **air_punch_spriteset,
        ALLEGRO_BITMAP **hi_kick_spriteset, ALLEGRO_BITMAP **lo_kick_spriteset,
        ALLEGRO_BITMAP **air_kick_spriteset, ALLEGRO_BITMAP **hi_block_spriteset, 
        ALLEGRO_BITMAP **lo_block_spriteset, ALLEGRO_BITMAP **running_spriteset, 
        ALLEGRO_BITMAP **crouch_spriteset, ALLEGRO_BITMAP **jump_spriteset, 
        unsigned char direction_facing, float absolute_height
) {
        if ((fighter_x - fighter_width / 2 < 0) || (fighter_x + fighter_width / 2 > max_x) || (fighter_y - fighter_height / 2 < 0) || (fighter_y + fighter_height / 2 > max_y))
                return NULL;

        Fighter *fighter = (Fighter *)malloc(sizeof(Fighter));

        if (!fighter)
                return NULL;

        fighter->controller = create_controller();

        if (!fighter->controller)
                return NULL;

        fighter->idle_spriteset = idle_spriteset;
        fighter->hi_punch_spriteset = hi_punch_spriteset;
        fighter->lo_punch_spriteset = lo_punch_spriteset;
        fighter->air_punch_spriteset = air_punch_spriteset;
        fighter->hi_kick_spriteset = hi_kick_spriteset;
        fighter->lo_kick_spriteset = lo_kick_spriteset;
        fighter->air_kick_spriteset = air_kick_spriteset;
        fighter->hi_block_spriteset = hi_block_spriteset;
        fighter->lo_block_spriteset = lo_block_spriteset;
        fighter->running_spriteset = running_spriteset;
        fighter->crouch_spriteset = crouch_spriteset;
        fighter->jump_spriteset = jump_spriteset;

        fighter->hitbox_upper = create_hitbox(fighter_width, fighter_height, fighter_x, fighter_y, max_x, max_y);

        if (!fighter->hitbox_upper)
                return NULL;

        fighter->hitbox_lower = create_hitbox(fighter_width, fighter_height, fighter_x, fighter_y + (float)al_get_bitmap_width(idle_spriteset[0]) / 2 + 32, max_x, max_y);

        if (!fighter->hitbox_lower)
                return NULL;

        fighter->health = MAX_HEALTH;
        fighter->velocity_y = 0.0;
        fighter->absolute_height = absolute_height;
        fighter->direction_facing = direction_facing;
        fighter->rounds_won = 0;
        fighter->is_running_right = 0;
        fighter->is_running_left = 0;
        fighter->is_punching = 0;
        fighter->is_kicking = 0;
        fighter->is_blocking = 0;
        fighter->is_crouching = 0;
        fighter->on_ground = 1;

        return fighter;
}

void move_fighter_right(Fighter *fighter, unsigned short max_x) {
        fighter->hitbox_upper->hitbox_x = fighter->hitbox_upper->hitbox_x + PLAYER_STEPS;

        if (((fighter->hitbox_upper->hitbox_x + PLAYER_STEPS) + fighter->hitbox_upper->hitbox_width / 2) > max_x)
                fighter->hitbox_upper->hitbox_x = fighter->hitbox_upper->hitbox_x - PLAYER_STEPS;

        fighter->hitbox_lower->hitbox_x = fighter->hitbox_lower->hitbox_x + PLAYER_STEPS;

        if (((fighter->hitbox_lower->hitbox_x + PLAYER_STEPS) + fighter->hitbox_lower->hitbox_width / 2) > max_x)
                fighter->hitbox_lower->hitbox_x = fighter->hitbox_lower->hitbox_x - PLAYER_STEPS;
}

void move_fighter_left(Fighter *fighter) {
        fighter->hitbox_upper->hitbox_x = fighter->hitbox_upper->hitbox_x - PLAYER_STEPS;

        if (((fighter->hitbox_upper->hitbox_x - PLAYER_STEPS) - fighter->hitbox_upper->hitbox_width / 2) < 0)
                fighter->hitbox_upper->hitbox_x = fighter->hitbox_upper->hitbox_x + PLAYER_STEPS;

        fighter->hitbox_lower->hitbox_x = fighter->hitbox_lower->hitbox_x - PLAYER_STEPS;

        if (((fighter->hitbox_lower->hitbox_x - PLAYER_STEPS) - fighter->hitbox_lower->hitbox_width / 2) < 0)
                fighter->hitbox_lower->hitbox_x = fighter->hitbox_lower->hitbox_x + PLAYER_STEPS;
}

void move_fighter_jump(Fighter *fighter, const float gravity) {
        fighter->velocity_y += gravity;
        fighter->hitbox_upper->hitbox_y += fighter->velocity_y;

        if (fighter->hitbox_upper->hitbox_y >= fighter->absolute_height) {
                fighter->hitbox_upper->hitbox_y = fighter->absolute_height;
                fighter->velocity_y = 0.0;
                fighter->on_ground = 1;
        }
}

void compute_hit(
        Fighter *player1, Fighter *player2, 
        unsigned int current_frame_hi_kick_p1, unsigned int current_frame_lo_kick_p1, 
        unsigned int current_frame_air_kick_p1, unsigned int current_frame_hi_punch_p1, 
        unsigned int current_frame_lo_punch_p1, unsigned int current_frame_air_punch_p1,
        unsigned int hit_frame_hi_kick_p1, unsigned int hit_frame_lo_kick_p1,
        unsigned int hit_frame_air_kick_p1, unsigned int hit_frame_hi_punch_p1,
        unsigned int hit_frame_lo_punch_p1, unsigned int hit_frame_air_punch_p1,
        unsigned int current_frame_hi_kick_p2, unsigned int current_frame_lo_kick_p2, 
        unsigned int current_frame_air_kick_p2, unsigned int current_frame_hi_punch_p2, 
        unsigned int current_frame_lo_punch_p2, unsigned int current_frame_air_punch_p2,
        unsigned int hit_frame_hi_kick_p2, unsigned int hit_frame_lo_kick_p2,
        unsigned int hit_frame_air_kick_p2, unsigned int hit_frame_hi_punch_p2,
        unsigned int hit_frame_lo_punch_p2, unsigned int hit_frame_air_punch_p2,
        ALLEGRO_SAMPLE *hit_sfx, ALLEGRO_SAMPLE_ID hit_sfx_id
) {
        if ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 253.0 
        && !player1->is_running_right && !player1->is_running_left 
        && !player1->is_blocking && !player2->is_blocking 
        && !player2->is_crouching && player1->is_punching 
        && current_frame_hi_punch_p1 == hit_frame_hi_punch_p1) {
                al_play_sample(hit_sfx, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &hit_sfx_id);
                
                player2->health -= 2.0;
        }

        if ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 200.0 
        && !player1->is_running_right && !player1->is_running_left 
        && !player1->is_blocking && !(player2->is_blocking && player2->is_crouching)
        && player1->is_punching && current_frame_lo_punch_p1 == hit_frame_lo_punch_p1 
        && player1->is_crouching && player2->on_ground) {
                al_play_sample(hit_sfx, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &hit_sfx_id);

                player2->health -= 2.0;
        }

        if ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 213.0 
        && (player2->hitbox_upper->hitbox_y - player1->hitbox_upper->hitbox_y) <= 100.0
        && !player1->is_blocking && !player2->is_blocking
        && player1->is_punching && current_frame_air_punch_p1 == hit_frame_air_punch_p1 
        && !player1->on_ground) {
                al_play_sample(hit_sfx, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &hit_sfx_id);
                
                player2->health -= 2.0;
        }

        if ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 213.0 
        && !player1->is_running_right && !player1->is_running_left 
        && !player1->is_blocking && !player2->is_blocking
        && player1->is_kicking && current_frame_hi_kick_p1 == hit_frame_hi_kick_p1
        && !player2->is_crouching) {
                al_play_sample(hit_sfx, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &hit_sfx_id);
                
                player2->health -= 2.75;
        }

        if ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 213.0 
        && !player1->is_running_right && !player1->is_running_left 
        && !player1->is_blocking && !(player2->is_blocking && player2->is_crouching)
        && player1->is_kicking && current_frame_lo_kick_p1 == hit_frame_lo_kick_p1 
        && player1->is_crouching && player2->on_ground) {
                al_play_sample(hit_sfx, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &hit_sfx_id);
                
                player2->health -= 2.75;
        }

        if ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 213.0 
        && (player2->hitbox_upper->hitbox_y - player1->hitbox_upper->hitbox_y <= 100.0)
        && !player1->is_blocking && !player2->is_blocking
        && player1->is_kicking && current_frame_air_kick_p1 == hit_frame_air_kick_p1 
        && !player1->on_ground) {
                al_play_sample(hit_sfx, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &hit_sfx_id);
                
                player2->health -= 2.75;
        }

        if ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 253.0 
        && !player2->is_running_right && !player2->is_running_left 
        && !player2->is_blocking && !player1->is_blocking 
        && !player1->is_crouching && player2->is_punching 
        && current_frame_hi_punch_p2 == hit_frame_hi_punch_p2) {
                al_play_sample(hit_sfx, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &hit_sfx_id);
                
                player1->health -= 2.0;
        }

        if ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 200.0 
        && !player2->is_running_right && !player2->is_running_left 
        && !player2->is_blocking && !(player1->is_blocking && player1->is_crouching)
        && player2->is_punching && current_frame_lo_punch_p2 == hit_frame_lo_punch_p2 
        && player2->is_crouching && player1->on_ground) {
                al_play_sample(hit_sfx, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &hit_sfx_id);

                player1->health -= 2.0;
        }

        if ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 213.0 
        && (player2->hitbox_upper->hitbox_y - player1->hitbox_upper->hitbox_y) >= -100.0
        && !player2->is_blocking && !player1->is_blocking
        && player2->is_punching && current_frame_air_punch_p2 == hit_frame_air_punch_p2 
        && !player2->on_ground) {
                al_play_sample(hit_sfx, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &hit_sfx_id);
                
                player1->health -= 2.0;
        }

        if ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 213.0 
        && !player2->is_running_right && !player2->is_running_left 
        && !player2->is_blocking && !player1->is_blocking
        && player2->is_kicking && current_frame_hi_kick_p2 == hit_frame_hi_kick_p2
        && !player1->is_crouching) {
                al_play_sample(hit_sfx, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &hit_sfx_id);
                
                player1->health -= 2.75;
        }

        if ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 213.0 
        && !player2->is_running_right && !player2->is_running_left 
        && !player2->is_blocking && !(player1->is_blocking && player1->is_crouching)
        && player2->is_kicking && current_frame_lo_kick_p2 == hit_frame_lo_kick_p2 
        && player2->is_crouching && player1->on_ground) {
                al_play_sample(hit_sfx, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &hit_sfx_id);
                
                player1->health -= 2.75;
        }

        if ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 213.0 
        && (player2->hitbox_upper->hitbox_y - player1->hitbox_upper->hitbox_y >= -100.0)
        && !player2->is_blocking && !player1->is_blocking
        && player2->is_kicking && current_frame_air_kick_p2 == hit_frame_air_kick_p2 
        && !player2->on_ground) {
                al_play_sample(hit_sfx, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &hit_sfx_id);
                
                player1->health -= 2.75;
        }
}

void handle_rumble_end(Fighter *player1, Fighter *player2, GameStates *game_states) {
        player1->rounds_won++;

        if (player1->rounds_won == 2) {
                game_states->rumble_end = 1;
                game_states->play_rumble_end_sample = 1;
                player1->is_crouching = 0;
                player2->is_crouching = 0;
        }

        player2->health = MAX_HEALTH;
        player1->health = MAX_HEALTH;
}

void reset_players_x(Fighter *player1, Fighter *player2, ALLEGRO_DISPLAY *display) {
        player1->hitbox_upper->hitbox_x = 94.5;
        player2->hitbox_upper->hitbox_x = (float)al_get_display_width(display) - 94.5;
        player1->hitbox_lower->hitbox_x = 94.5;
        player2->hitbox_lower->hitbox_x = (float)al_get_display_width(display) - 94.5;
}

void update_fighter_pos(Fighter *player1, Fighter *player2, unsigned short max_x) {
        if (!(player1->controller->left && player1->controller->right) && !player1->is_crouching) {
                if (player1->controller->right && !player1->is_blocking) {
                        move_fighter_right(player1, max_x);
        
                        if (calc_collision(player1->hitbox_upper, player2->hitbox_upper))
                                move_fighter_left(player1);
                } else if (player1->controller->left) {
                        move_fighter_left(player1);

                        if (calc_collision(player1->hitbox_upper, player2->hitbox_upper))
                                move_fighter_right(player1, max_x);
                }
        }

        if (!player1->on_ground)
                move_fighter_jump(player1, GRAVITY);
        
        if (!(player2->controller->left && player2->controller->right) && !player2->is_crouching) {
                if (player2->controller->right) {
                        move_fighter_right(player2, max_x);

                        if (calc_collision(player1->hitbox_upper, player2->hitbox_upper) || calc_collision(player1->hitbox_lower, player2->hitbox_lower))
                                move_fighter_left(player2);
                } else if (player2->controller->left) {
                        move_fighter_left(player2);

                        if (calc_collision(player1->hitbox_upper, player2->hitbox_upper) || calc_collision(player1->hitbox_lower, player2->hitbox_lower))
                                move_fighter_right(player2, max_x);
                }
        }

        if (!player2->on_ground)
                move_fighter_jump(player2, GRAVITY);
}

void update_fighter_selectors(GameStates *game_states) {
        switch (game_states->character_select_nav_p1) {
                case 0:
                        game_states->rumble_fighter_p1 = 0;

                        break;

                case 1:
                        game_states->rumble_fighter_p1 = 1;

                        break;

                case 2:
                        game_states->rumble_fighter_p1 = 2;

                        break;

                case 3:
                        game_states->rumble_fighter_p1 = 3;

                        break;
        }

        switch (game_states->character_select_nav_p2) {
                case 0:
                        game_states->rumble_fighter_p2 = 0;

                        break;

                case 1:
                        game_states->rumble_fighter_p2 = 1;

                        break;

                case 2:
                        game_states->rumble_fighter_p2 = 2;

                        break;

                case 3:
                        game_states->rumble_fighter_p2 = 3;

                        break;
        }
}