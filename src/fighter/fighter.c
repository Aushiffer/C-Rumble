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
        ALLEGRO_BITMAP **fighter_block_spriteset, unsigned char player_type
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

        fighter->fighter_idle_spriteset = fighter_idle_spriteset;
        fighter->fighter_hi_punch_spriteset = fighter_hi_punch_spriteset;
        fighter->fighter_lo_punch_spriteset = fighter_lo_punch_spriteset;
        fighter->fighter_kick_spriteset = fighter_kick_spriteset;
        fighter->fighter_damage_spriteset = fighter_damage_spriteset;
        fighter->fighter_death_spriteset = fighter_death_spriteset;
        fighter->fighter_block_spriteset = fighter_block_spriteset;
        fighter->health = 100.0;
        fighter->stamina = 100.0;
        fighter->player_type = player_type;

        return fighter;
}

void play_idle_animation(Fighter *fighter, unsigned int current_idle_frame) {
        if (fighter->controller->right == 0 && fighter->controller->left == 0 
        && fighter->controller->up == 0 && fighter->controller->down == 0 
        && fighter->controller->punch == 0 && fighter->controller->kick == 0) {
                al_draw_scaled_bitmap(
                        fighter->fighter_idle_spriteset[current_idle_frame], 0.0, 
                        0.0, al_get_bitmap_width(fighter->fighter_idle_spriteset[current_idle_frame]), 
                        al_get_bitmap_height(fighter->fighter_idle_spriteset[current_idle_frame]), fighter->hitbox->hitbox_x, 
                        fighter->hitbox->hitbox_y, fighter->hitbox->hitbox_width, 
                        fighter->hitbox->hitbox_height, 0
                );
        }
}

void destroy_fighter(Fighter *fighter) {
        if (fighter) {
                destroy_hitbox(fighter->hitbox);
                destroy_controller(fighter->controller);
                free(fighter);
        }
}