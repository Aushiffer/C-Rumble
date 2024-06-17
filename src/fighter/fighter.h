#ifndef __FIGHTER__
#define __FIGHTER__

#include <stdlib.h>
#include <allegro5/bitmap.h>
#include "../hitbox/hitbox.h"
#include "../controller/controller.h"

/* Lutador */
typedef struct Fighter {
        Hitbox *hitbox;
        Controller *controller;
        ALLEGRO_BITMAP *high_punch;
        ALLEGRO_BITMAP *low_punch;
        ALLEGRO_BITMAP *high_kick;
        ALLEGRO_BITMAP *low_kick;
        ALLEGRO_BITMAP *crouch;
        ALLEGRO_BITMAP *jump;
        ALLEGRO_BITMAP *jump_punch;
        ALLEGRO_BITMAP *jump_kick;
        ALLEGRO_BITMAP *high_block;
        ALLEGRO_BITMAP *low_block;
        float hp;
        unsigned char on_air;
} Fighter;

/* Cria um novo lutador */
Fighter *create_fighter(unsigned char width, unsigned char height);

/* Mover à direita */
void move_fighter_right(Fighter *fighter);

/* Mover à esquerda */
void move_fighter_left(Fighter *fighter);

/* Pular */
void move_fighter_jump(Fighter *fighter);

/* Abaixar */
void move_fighter_crouch(Fighter *fighter);

/* Atualiza as posições dos jogadores. Implemente sempre dentro do evento de timer */
void update_fighter_pos(Fighter *player1, Fighter *player2);

/* Destrói um lutador */
void destroy_fighter(Fighter *fighter);

#endif // __FIGHTER__