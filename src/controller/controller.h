#ifndef __CONTROLLER__
#define __CONTROLLER__

#include <stdlib.h>

/* Controle usado para movimentar os personagens */
typedef struct Controller {
        unsigned char right;
        unsigned char left;
        unsigned char up;
        unsigned char down;
        unsigned char punch;
        unsigned char kick;
} Controller;

/* Cria um novo controle */
Controller *create_controller();

/* Move o controle para a direita */
void move_controller_right(Controller *controller);

/* Move o controle para a esquerda */
void move_controller_left(Controller *controller);

/* Move o controle para cima */
void move_controller_up(Controller *controller);

/* Move o controle para baixo */
void move_controller_down(Controller *controller);

/* Pressiona o botão de soco */
void move_controller_punch(Controller *controller);

/* Pressiona o botão de chute */
void move_controller_kick(Controller *controller);

/* Destrói um controle */
void destroy_controller(Controller *controller);

#endif // __CONTROLLER__