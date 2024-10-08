#include "hitbox.h"

Hitbox *create_hitbox(float width, float height, float hitbox_x, float hitbox_y, float max_x, float max_y) {
        if ((hitbox_x - width / 2 < 0) || (hitbox_x + width / 2 > max_x) || (hitbox_y - height / 2 < 0) || (hitbox_y + height / 2 > max_y))
                return NULL;
        
        Hitbox *hitbox = (Hitbox *)malloc(sizeof(Hitbox));

        if (!hitbox)
                return NULL;

        hitbox->hitbox_width = width;
        hitbox->hitbox_height = height;
        hitbox->hitbox_x = hitbox_x;
        hitbox->hitbox_y = hitbox_y;

        return hitbox;
}

unsigned char calc_collision(Hitbox *hitbox1, Hitbox *hitbox2) {
        if (!hitbox1 || !hitbox2)
                return 2;

        if ((((hitbox1->hitbox_x + hitbox1->hitbox_width / 2 >= hitbox2->hitbox_x - hitbox2->hitbox_width / 2 + 32) && (hitbox2->hitbox_x - hitbox2->hitbox_width / 2 >= hitbox1->hitbox_x - hitbox1->hitbox_width / 2)) 
        || ((hitbox2->hitbox_x + hitbox2->hitbox_width / 2 >= hitbox1->hitbox_x - hitbox1->hitbox_width / 2 + 32) && (hitbox1->hitbox_x - hitbox1->hitbox_width / 2 >= hitbox2->hitbox_x - hitbox2->hitbox_width / 2))) 
        && (((hitbox1->hitbox_y + hitbox1->hitbox_height / 2 >= hitbox2->hitbox_y - hitbox2->hitbox_height / 2) && (hitbox2->hitbox_y - hitbox2->hitbox_height / 2 >= hitbox1->hitbox_y - hitbox1->hitbox_height / 2)) 
        || ((hitbox2->hitbox_y + hitbox2->hitbox_height / 2 >= hitbox1->hitbox_y - hitbox1->hitbox_height / 2) && (hitbox1->hitbox_y - hitbox1->hitbox_height / 2 >= hitbox2->hitbox_y - hitbox2->hitbox_height / 2))))
                return 1;

        return 0;
}

void destroy_hitbox(Hitbox *hitbox) {
        if (hitbox)
                free(hitbox);
}