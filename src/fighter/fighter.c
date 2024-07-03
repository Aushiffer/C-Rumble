#include "fighter.h"

Fighter *create_fighter(
        float width, float height, 
        float x, float y, 
        float max_x, float max_y, 
        ALLEGRO_BITMAP **idle_spriteset, ALLEGRO_BITMAP **hi_punch_spriteset, 
        ALLEGRO_BITMAP **lo_punch_spriteset, ALLEGRO_BITMAP **kick_spriteset,
        ALLEGRO_BITMAP **damage_spriteset, ALLEGRO_BITMAP **death_spriteset,
        ALLEGRO_BITMAP **hi_block_spriteset, ALLEGRO_BITMAP **special_spriteset,
        ALLEGRO_BITMAP **running_spriteset, ALLEGRO_BITMAP **crouch_spriteset,
        unsigned char direction_facing
) {
        if ((x - width / 2 < 0) || (x + width / 2 > max_x) || (y - height / 2 < 0) || (y + height / 2 > max_y))
                return NULL;

        Fighter *fighter = (Fighter *)malloc(sizeof(Fighter));

        if (!fighter)
                return NULL;

        fighter->hitbox = create_hitbox(width, height, x, y, max_x, max_y);

        if (!fighter->hitbox)
                return NULL;

        fighter->controller = create_controller();

        if (!fighter->controller)
                return NULL;

        fighter->idle_spriteset = idle_spriteset;
        fighter->hi_punch_spriteset = hi_punch_spriteset;
        fighter->lo_punch_spriteset = lo_punch_spriteset;
        fighter->kick_spriteset = kick_spriteset;
        fighter->damage_spriteset = damage_spriteset;
        fighter->death_spriteset = death_spriteset;
        fighter->hi_block_spriteset = hi_block_spriteset;
        fighter->special_spriteset = special_spriteset;
        fighter->running_spriteset = running_spriteset;
        fighter->crouch_spriteset = crouch_spriteset;
        fighter->health = 100.0;
        fighter->stamina = 100.0;
        fighter->direction_facing = direction_facing;
        fighter->rounds_won = 0;
        fighter->is_running_right = 0;
        fighter->is_running_left = 0;
        fighter->is_hi_punching = 0;
        fighter->is_hi_kicking = 0;
        fighter->is_blocking = 0;
        fighter->is_crouching = 0;

        return fighter;
}

void move_fighter_right(Fighter *fighter, unsigned short max_x) {
        fighter->hitbox->hitbox_x = fighter->hitbox->hitbox_x + PLAYER_STEPS;

        if (((fighter->hitbox->hitbox_x + PLAYER_STEPS) + fighter->hitbox->hitbox_width / 2) > max_x)
                fighter->hitbox->hitbox_x = fighter->hitbox->hitbox_x - PLAYER_STEPS;
}

void move_fighter_left(Fighter *fighter) {
        fighter->hitbox->hitbox_x = fighter->hitbox->hitbox_x - PLAYER_STEPS;

        if (((fighter->hitbox->hitbox_x - PLAYER_STEPS) - fighter->hitbox->hitbox_width / 2) < 0)
                fighter->hitbox->hitbox_x = fighter->hitbox->hitbox_x + PLAYER_STEPS;
}

void move_fighter_crouch(Fighter *fighter) {
        // fighter->hitbox->hitbox_height = fighter->hitbox->hitbox_height / 2;
}

void update_fighter_pos(Fighter *player1, Fighter *player2, unsigned short max_x, unsigned short max_y) {
        if (!(player1->controller->left && player1->controller->right)) {
                if (player1->controller->right) {
                move_fighter_right(player1, max_x);

                if (calc_collision(player1->hitbox, player2->hitbox))
                        move_fighter_left(player1);
                } else if (player1->controller->left) {
                        move_fighter_left(player1);

                        if (calc_collision(player1->hitbox, player2->hitbox))
                                move_fighter_right(player1, max_x);
                } else if (player1->controller->down) {
                        move_fighter_crouch(player1);
                }
        }

        if (!(player2->controller->left && player2->controller->right)) {
                if (player2->controller->right) {
                        move_fighter_right(player2, max_x);

                        if (calc_collision(player2->hitbox, player1->hitbox))
                                move_fighter_left(player2);
                } else if (player2->controller->left) {
                        move_fighter_left(player2);

                        if (calc_collision(player2->hitbox, player1->hitbox))
                                move_fighter_right(player2, max_x);
                } else if (player2->controller->down) {
                        move_fighter_crouch(player2);
                }
        }
}

void destroy_fighter(Fighter *fighter) {
        if (fighter) {
                destroy_hitbox(fighter->hitbox);
                destroy_controller(fighter->controller);
                free(fighter);
        }
}