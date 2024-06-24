#include "fighter.h"
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>

Fighter *create_fighter(
        float width, float height, 
        float fighter_x, float fighter_y, 
        float max_x, float max_y, 
        ALLEGRO_BITMAP **fighter_idle_spriteset, ALLEGRO_BITMAP **fighter_hi_punch_spriteset, 
        ALLEGRO_BITMAP **fighter_lo_punch_spriteset, ALLEGRO_BITMAP **fighter_kick_spriteset,
        ALLEGRO_BITMAP **fighter_damage_spriteset, ALLEGRO_BITMAP **fighter_death_spriteset,
        ALLEGRO_BITMAP **fighter_hi_block_spriteset, ALLEGRO_BITMAP **fighter_special_spriteset,
        ALLEGRO_BITMAP **fighter_running_spriteset, ALLEGRO_BITMAP **fighter_crouch_spriteset,
        unsigned char player_type
) {
        if ((fighter_x - width / 2 < 0) || (fighter_x + width / 2 > max_x) || (fighter_y - height / 2 < 0) || (fighter_y + height / 2 > max_y))
                return NULL;

        Fighter *fighter = (Fighter *)malloc(sizeof(Fighter));

        if (!fighter)
                return NULL;

        fighter->hitbox = create_hitbox(width, height, fighter_x, fighter_y, max_x, max_y);

        if (!fighter->hitbox)
                return NULL;

        fighter->controller = create_controller();

        if (!fighter->controller)
                return NULL;

        fighter->idle_spriteset = fighter_idle_spriteset;
        fighter->hi_punch_spriteset = fighter_hi_punch_spriteset;
        fighter->lo_punch_spriteset = fighter_lo_punch_spriteset;
        fighter->kick_spriteset = fighter_kick_spriteset;
        fighter->damage_spriteset = fighter_damage_spriteset;
        fighter->death_spriteset = fighter_death_spriteset;
        fighter->hi_block_spriteset = fighter_hi_block_spriteset;
        fighter->special_spriteset = fighter_special_spriteset;
        fighter->running_spriteset = fighter_running_spriteset;
        fighter->crouch_spriteset = fighter_crouch_spriteset;
        fighter->health = 100.0;
        fighter->stamina = 100.0;
        fighter->player_type = player_type;

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
        //fighter->hitbox->hitbox_height = fighter->hitbox->hitbox_height / 2;
}

void update_fighter_pos(Fighter *player1, Fighter *player2, unsigned short max_x, unsigned short max_y) {
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

void update_animations(
        unsigned int current_idle_frame, unsigned int current_running_frame, 
        unsigned int current_damage_frame, unsigned int current_hi_block_frame, 
        unsigned int current_death_frame, unsigned int current_hi_punch_frame, 
        unsigned int current_lo_punch_frame, unsigned int current_kick_frame, 
        unsigned int current_special_frame, Fighter *fighter
) {
        if (!fighter->controller->left && !fighter->controller->right && !fighter->controller->down && !fighter->controller->up)
                al_draw_bitmap(fighter->idle_spriteset[current_idle_frame], fighter->hitbox->hitbox_x - (float)al_get_bitmap_width(fighter->idle_spriteset[current_idle_frame]) / 2, fighter->hitbox->hitbox_y, (fighter->player_type - 1) % 2);
        else if (!fighter->controller->left && fighter->controller->right && !fighter->controller->down && !fighter->controller->up)
                al_draw_bitmap(fighter->running_spriteset[current_running_frame], fighter->hitbox->hitbox_x - (float)al_get_bitmap_width(fighter->running_spriteset[current_running_frame]) / 2, fighter->hitbox->hitbox_y, (fighter->player_type - 1) % 2);
        else if (fighter->controller->left && !fighter->controller->right && !fighter->controller->down && !fighter->controller->up)
                al_draw_bitmap(fighter->running_spriteset[current_running_frame], fighter->hitbox->hitbox_x - (float)al_get_bitmap_width(fighter->running_spriteset[current_running_frame]) / 2, fighter->hitbox->hitbox_y, fighter->player_type % 2);
        else if (!fighter->controller->left && !fighter->controller->right && fighter->controller->down && !fighter->controller->up)
                al_draw_bitmap(fighter->crouch_spriteset[1], fighter->hitbox->hitbox_x - (float)al_get_bitmap_width(fighter->crouch_spriteset[1]) / 2, fighter->hitbox->hitbox_y + (float)al_get_bitmap_width(fighter->crouch_spriteset[1]) / 2, (fighter->player_type - 1) % 2);
}

void destroy_fighter(Fighter *fighter) {
        if (fighter) {
                destroy_hitbox(fighter->hitbox);
                destroy_controller(fighter->controller);
                free(fighter);
        }
}