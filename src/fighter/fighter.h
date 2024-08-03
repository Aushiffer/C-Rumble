#ifndef __FIGHTER__
#define __FIGHTER__

#include <stdlib.h>
#include <allegro5/bitmap.h>
#include <allegro5/display.h>
#include <allegro5/allegro_audio.h>
#include "../hitbox/hitbox.h"
#include "../controller/controller.h"
#include "../game_states/game_states.h"

/* Macros do Ryu */
#define NUM_RYU_IDLE_FRAMES 5        
#define NUM_RYU_RUNNING_FRAMES 5
#define NUM_RYU_HI_KICK_FRAMES 3
#define NUM_RYU_LO_KICK_FRAMES 2
#define NUM_RYU_AIR_KICK_FRAMES 3
#define NUM_RYU_HI_PUNCH_FRAMES 3
#define NUM_RYU_LO_PUNCH_FRAMES 2
#define NUM_RYU_AIR_PUNCH_FRAMES 3
#define NUM_RYU_CROUCH_FRAMES 1
#define NUM_RYU_BLOCK_FRAMES 1
#define NUM_RYU_JUMP_FRAMES 6

#define PLAYER_STEPS 15.0
#define MAX_HEALTH 100.0
#define MAX_STAMINA 100.0
#define GRAVITY 1.0
#define JUMP_STRENGTH -20.0

/* Lutador */
typedef struct Fighter {
        Hitbox *hitbox_upper;
        Hitbox *hitbox_lower;
        Controller *controller;
        ALLEGRO_BITMAP **idle_spriteset;
        ALLEGRO_BITMAP **hi_punch_spriteset;
        ALLEGRO_BITMAP **lo_punch_spriteset;
        ALLEGRO_BITMAP **air_punch_spriteset;
        ALLEGRO_BITMAP **hi_kick_spriteset;
        ALLEGRO_BITMAP **lo_kick_spriteset;
        ALLEGRO_BITMAP **air_kick_spriteset;
        ALLEGRO_BITMAP **hi_block_spriteset;
        ALLEGRO_BITMAP **lo_block_spriteset;
        ALLEGRO_BITMAP **running_spriteset;
        ALLEGRO_BITMAP **crouch_spriteset;
        ALLEGRO_BITMAP **jump_spriteset;
        float health;
        float absolute_height;
        float velocity_y;
        unsigned char direction_facing;
        unsigned char rounds_won;
        unsigned char is_running_right;
        unsigned char is_running_left;
        unsigned char is_punching;
        unsigned char is_kicking;
        unsigned char is_blocking;
        unsigned char is_crouching;
        unsigned char on_ground;
} Fighter;

/* Cria um novo lutador */
Fighter *create_fighter(
        float fighter_width, float fighter_height, 
        float fighter_x, float fighter_y, 
        float max_x, float max_y, 
        ALLEGRO_BITMAP **idle_spriteset, ALLEGRO_BITMAP **hi_punch_spriteset, 
        ALLEGRO_BITMAP **lo_punch_spriteset, ALLEGRO_BITMAP **air_punch_spriteset,
        ALLEGRO_BITMAP **hi_kick_spriteset, ALLEGRO_BITMAP **lo_kick_spriteset,
        ALLEGRO_BITMAP **air_kick_spriteset, ALLEGRO_BITMAP **hi_block_spriteset, 
        ALLEGRO_BITMAP **lo_block_spriteset, ALLEGRO_BITMAP **running_spriteset, 
        ALLEGRO_BITMAP **crouch_spriteset, ALLEGRO_BITMAP **jump_spriteset, 
        unsigned char direction_facing, float absolute_height
);

/* Mover à direita */
void move_fighter_right(Fighter *fighter, unsigned short max_x);

/* Mover à esquerda */
void move_fighter_left(Fighter *fighter);

/* Pular */
void move_fighter_jump(Fighter *fighter, const float gravity);

/* Soco */
void move_fighter_punch(Fighter *fighter);

/* Chute */
void move_fighter_kick(Fighter *fighter);

/* Faz jogadores receberem dano caso um hit puder ser considerado */
void compute_hit(
        Fighter *player1, Fighter *player2, 
        unsigned int current_frame_hi_kick_p1, unsigned int current_frame_lo_kick_p1, 
        unsigned int current_frame_air_kick_p1, unsigned int current_frame_hi_punch_p1, 
        unsigned int current_frame_lo_punch_p1, unsigned int current_frame_air_punch_p1,
        unsigned int hit_frame_hi_kick_p1, unsigned int hit_frame_lo_kick_p1,
        unsigned int hit_frame_air_kick_p1, unsigned int hit_frame_hi_punch_p1,
        unsigned int hit_frame_lo_punch_p1, unsigned int hit_frame_air_punch_p1,
        unsigned int current_frame_hi_kick_p2, unsigned int current_frame_lo_kick_p2, 
        unsigned int current_frame_air_kick_p2, unsigned int current_frame_hi_punch_p2, 
        unsigned int current_frame_lo_punch_p2, unsigned int current_frame_air_punch_p2,
        unsigned int hit_frame_hi_kick_p2, unsigned int hit_frame_lo_kick_p2,
        unsigned int hit_frame_air_kick_p2, unsigned int hit_frame_hi_punch_p2,
        unsigned int hit_frame_lo_punch_p2, unsigned int hit_frame_air_punch_p2,
        ALLEGRO_SAMPLE *hit_sfx, ALLEGRO_SAMPLE_ID hit_sfx_id
);

/* Implementa lógica para um dos jogadores vencer */
void handle_rumble_end(Fighter *player1, Fighter *player2, GameStates *game_states);

/* Reseta o x de ambos os jogadores */
void reset_players_x(Fighter *player1, Fighter *player2, ALLEGRO_DISPLAY *display);

/* Atualiza as posições dos jogadores. Implemente sempre dentro do evento de timer */
void update_fighter_pos(Fighter *player1, Fighter *player2, unsigned short max_x);

/* Atualiza os seletores de personagem */
void update_fighter_selectors(GameStates *game_states);

/* Destrói um lutador */
void destroy_fighter_sprites(Fighter *fighter);

#endif // __FIGHTER__