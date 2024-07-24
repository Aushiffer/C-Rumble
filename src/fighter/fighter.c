#include "fighter.h"
#include <allegro5/bitmap.h>

Fighter *create_fighter(
        float width, float height, 
        float x, float y, 
        float max_x, float max_y, 
        ALLEGRO_BITMAP **idle_spriteset, ALLEGRO_BITMAP **hi_punch_spriteset, 
        ALLEGRO_BITMAP **lo_punch_spriteset, ALLEGRO_BITMAP **kick_spriteset,
        ALLEGRO_BITMAP **hi_block_spriteset, ALLEGRO_BITMAP **running_spriteset, 
        ALLEGRO_BITMAP **crouch_spriteset, unsigned char direction_facing, 
        float absolute_height
) {
        if ((x - width / 2 < 0) || (x + width / 2 > max_x) || (y - height / 2 < 0) || (y + height / 2 > max_y))
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
        fighter->kick_spriteset = kick_spriteset;
        fighter->hi_block_spriteset = hi_block_spriteset;
        fighter->running_spriteset = running_spriteset;
        fighter->crouch_spriteset = crouch_spriteset;

        fighter->hitbox_upper = create_hitbox(width, height, x, y, max_x, max_y);

        if (!fighter->hitbox_upper)
                return NULL;

        fighter->hitbox_lower = create_hitbox(width, height, x, y + (float)al_get_bitmap_width(idle_spriteset[0]) / 2, max_x, max_y);

        if (!fighter->hitbox_lower)
                return NULL;

        fighter->health = MAX_HEALTH;
        fighter->stamina = MAX_STAMINA;
        fighter->absolute_height = absolute_height;
        fighter->direction_facing = direction_facing;
        fighter->rounds_won = 0;
        fighter->is_running_right = 0;
        fighter->is_running_left = 0;
        fighter->is_punching = 0;
        fighter->is_kicking = 0;
        fighter->is_blocking = 0;
        fighter->is_crouching = 0;

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

void move_fighter_crouch(Fighter *fighter) {
        fighter->hitbox_upper->hitbox_y = fighter->hitbox_lower->hitbox_y;
}

void update_stamina(Fighter *player1, Fighter *player2) {
        if ((player1->is_kicking || player1->is_punching) && ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 251.0) && player2->is_blocking) 
                player2->stamina -= 0.5;

        if (!player2->is_blocking && player2->stamina < MAX_STAMINA)
                player2->stamina += 0.25;

        if ((player2->is_kicking || player2->is_punching) && ((player2->hitbox_upper->hitbox_x - player1->hitbox_upper->hitbox_x) <= 251.0) && player1->is_blocking) 
                player1->stamina -= 0.5;

        if (!player1->is_blocking && player1->stamina < MAX_STAMINA)
                player1->stamina += 0.25;
}

void handle_rumble_end(Fighter *player1, Fighter *player2, ALLEGRO_DISPLAY *display, GameStates *game_states) {
        if (player2->health <= 0) {
                player1->rounds_won++;

                if (player1->rounds_won == 3) {
                        game_states->rumble_end = 1;
                        game_states->play_rumble_end_sample = 1;
                } else {
                        player2->health = MAX_HEALTH;
                }

                reset_players_x(player1, player2, display);
        }
}

void reset_players_x(Fighter *player1, Fighter *player2, ALLEGRO_DISPLAY *display) {
        player1->hitbox_upper->hitbox_x = 94.5;
        player2->hitbox_upper->hitbox_x = (float)al_get_display_width(display) - 94.5;
        player1->hitbox_lower->hitbox_x = 94.5;
        player2->hitbox_lower->hitbox_x = (float)al_get_display_width(display) - 94.5;
}

void update_fighter_pos(Fighter *player1, Fighter *player2, unsigned short max_x, unsigned short max_y) {
        if (!(player1->controller->left && player1->controller->right) && !player1->is_crouching) {
                if (player1->controller->right && !(player1->is_blocking || player1->is_crouching)) {
                        move_fighter_right(player1, max_x);
        
                        if (calc_collision(player1->hitbox_upper, player2->hitbox_upper) || calc_collision(player1->hitbox_lower, player2->hitbox_lower))
                                move_fighter_left(player1);
                } else if (player1->controller->left) {
                        move_fighter_left(player1);

                        if (calc_collision(player1->hitbox_upper, player2->hitbox_upper) || calc_collision(player1->hitbox_lower, player2->hitbox_lower))
                                move_fighter_right(player1, max_x);
                } else if (player1->controller->down) {
                        move_fighter_crouch(player1);
                }
        }

        if (!(player2->controller->left && player2->controller->right) && !player2->is_crouching) {
                if (player2->controller->right) {
                        move_fighter_right(player2, max_x);

                        if (calc_collision(player1->hitbox_upper, player2->hitbox_upper) || calc_collision(player1->hitbox_lower, player2->hitbox_lower))
                                move_fighter_left(player2);
                } else if (player2->controller->left) {
                        move_fighter_left(player2);

                        if (calc_collision(player1->hitbox_upper, player2->hitbox_upper) || calc_collision(player1->hitbox_lower, player2->hitbox_lower))
                                move_fighter_right(player2, max_x);
                } else if (player2->controller->down) {
                        move_fighter_crouch(player2);
                }
        }
}

void destroy_fighter(Fighter *fighter) {
        if (fighter) {
                destroy_hitbox(fighter->hitbox_upper);
                destroy_hitbox(fighter->hitbox_lower);
                destroy_controller(fighter->controller);
                free(fighter);
        }
}