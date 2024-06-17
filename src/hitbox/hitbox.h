#ifndef __HITBOX__
#define __HITBOX__

#include <stdlib.h>

/* Hitbox */
typedef struct Hitbox {
        unsigned char hitbox_width;
        unsigned char hitbox_height;
        unsigned short hitbox_x;
        unsigned short hitbox_y;
} Hitbox;

/* Cria uma hitbox */
Hitbox *create_hitbox(unsigned char width, unsigned char height, unsigned short hitbox_x, unsigned short hitbox_y, unsigned short max_x, unsigned short max_y);

/* Calcula a colisão entre duas hitboxes. Retorna 1 se houver colisão e 0 caso contrário */
unsigned char calc_collision(Hitbox *hitbox1, Hitbox *hitbox2);

/* Destrói uma hitbox */
void destroy_hitbox(Hitbox *hitbox);

#endif // __HITBOX__