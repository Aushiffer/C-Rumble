#ifndef __HITBOX__
#define __HITBOX__

/* Hitbox */
typedef struct Hitbox {
        unsigned char hitbox_width;
        unsigned char hitbox_height;
} Hitbox;

/* Cria uma hitbox */
Hitbox *create_hitbox(unsigned char width, unsigned char height);

/* Calcula a colisão entre duas hitboxes. Retorna 1 se houver colisão e 0 caso contrário */
unsigned char calc_collision(Hitbox *hitbox1, Hitbox *hitbox2);

/* Destrói uma hitbox */
void destroy_hitbox(Hitbox *hitbox);

#endif // __HITBOX__