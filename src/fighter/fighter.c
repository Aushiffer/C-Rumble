#include "fighter.h"

Fighter *create_fighter(unsigned char width, unsigned char height, unsigned short fighter_x, unsigned short fighter_y, unsigned short max_x, unsigned short max_y) {
        if ((fighter_x - width / 2 < 0) || (fighter_x + width / 2 > max_x) || (fighter_y - height / 2 < 0) || (fighter_y + height / 2 > max_y))
                return NULL;

        Fighter *fighter = (Fighter *)malloc(sizeof(Fighter));

        if (!fighter)
                return NULL;

        fighter->hitbox->hitbox_width = width;
        fighter->hitbox->hitbox_height = height;
        fighter->hitbox->hitbox_x = fighter_x;
        fighter->hitbox->hitbox_y = fighter_y;
        fighter->health = 100.0;
        fighter->stamina = 100.0;

        return fighter;
}