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
        ALLEGRO_BITMAP **fighter_idle_spriteset;
        ALLEGRO_BITMAP **fighter_hi_punch_spriteset;
        ALLEGRO_BITMAP **fighter_lo_punch_spriteset;
        ALLEGRO_BITMAP **fighter_kick_spriteset;
        ALLEGRO_BITMAP **fighter_damage_spriteset;
        ALLEGRO_BITMAP **fighter_death_spriteset;
        ALLEGRO_BITMAP **fighter_block_spriteset;
        float health;
        float stamina;
        unsigned char player_type;
} Fighter;

/* Cria um novo lutador */
Fighter *create_fighter(
        float fighter_width, float fighter_height, 
        float fighter_x, float fighter_y, 
        float max_x, float max_y, 
        ALLEGRO_BITMAP **fighter_idle_spriteset, ALLEGRO_BITMAP **fighter_hi_punch_spriteset, 
        ALLEGRO_BITMAP **fighter_lo_punch_spriteset, ALLEGRO_BITMAP **fighter_kick_spriteset,
        ALLEGRO_BITMAP **fighter_damage_spriteset, ALLEGRO_BITMAP **fighter_death_spriteset,
        ALLEGRO_BITMAP **fighter_block_spriteset, unsigned char player_type
);

/* Roda a animação do personagem parado */
void play_idle_animation(Fighter *fighter, unsigned int current_idle_frame);

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