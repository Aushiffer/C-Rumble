#ifndef __HITBOX__
#define __HITBOX__

#include <stdlib.h>

/* Hitbox */
typedef struct Hitbox {
        float hitbox_width;
        float hitbox_height;
        float hitbox_x;
        float hitbox_y;
} Hitbox;

/* Cria uma hitbox */
Hitbox *create_hitbox(float width, float height, float hitbox_x, float hitbox_y, float max_x, float max_y);

/* Calcula a colisão entre duas hitboxes. Retorna 1 se houver colisão e 0 caso contrário */
unsigned char calc_collision(Hitbox *hitbox1, Hitbox *hitbox2);

/* Destrói uma hitbox */
void destroy_hitbox(Hitbox *hitbox);

#endif // __HITBOX__