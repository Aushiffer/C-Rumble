#ifndef __FIGHTER__
#define __FIGHTER__

#include <stdlib.h>
#include <allegro5/bitmap.h>
#include "../hitbox/hitbox.h"
#include "../controller/controller.h"

#define PLAYER_STEPS 15.0

/* Lutador */
typedef struct Fighter {
        Hitbox *hitbox;
        Controller *controller;
        ALLEGRO_BITMAP **idle_spriteset;
        ALLEGRO_BITMAP **hi_punch_spriteset;
        ALLEGRO_BITMAP **lo_punch_spriteset;
        ALLEGRO_BITMAP **kick_spriteset;
        ALLEGRO_BITMAP **damage_spriteset;
        ALLEGRO_BITMAP **death_spriteset;
        ALLEGRO_BITMAP **hi_block_spriteset;
        ALLEGRO_BITMAP **special_spriteset;
        ALLEGRO_BITMAP **running_spriteset;
        ALLEGRO_BITMAP **crouch_spriteset;
        float health;
        float stamina;
        unsigned char direction_facing;
        unsigned char rounds_won;
        unsigned char is_running_right;
        unsigned char is_running_left;
        unsigned char is_punching;
        unsigned char is_kicking;
        unsigned char is_blocking;
        unsigned char is_crouching;
} Fighter;

/* Cria um novo lutador */
Fighter *create_fighter(
        float fighter_width, float fighter_height, 
        float fighter_x, float fighter_y, 
        float max_x, float max_y, 
        ALLEGRO_BITMAP **idle_spriteset, ALLEGRO_BITMAP **hi_punch_spriteset, 
        ALLEGRO_BITMAP **lo_punch_spriteset, ALLEGRO_BITMAP **kick_spriteset,
        ALLEGRO_BITMAP **damage_spriteset, ALLEGRO_BITMAP **death_spriteset,
        ALLEGRO_BITMAP **hi_block_spriteset, ALLEGRO_BITMAP **special_spriteset,
        ALLEGRO_BITMAP **running_spriteset, ALLEGRO_BITMAP **crouch_spriteset,
        unsigned char direction_facing
);

/* Mover à direita */
void move_fighter_right(Fighter *fighter, unsigned short max_x);

/* Mover à esquerda */
void move_fighter_left(Fighter *fighter);

/* Pular */
void move_fighter_jump(Fighter *fighter, unsigned short max_x, unsigned short max_y);

/* Abaixar */
void move_fighter_crouch(Fighter *fighter);

/* Soco */
void move_fighter_punch(Fighter *fighter);

/* Chute */
void move_fighter_kick(Fighter *fighter);

/* Atualiza as posições dos jogadores. Implemente sempre dentro do evento de timer */
void update_fighter_pos(Fighter *player1, Fighter *player2, unsigned short max_x, unsigned short max_y);

/* Destrói um lutador */
void destroy_fighter(Fighter *fighter);

#endif // __FIGHTER__