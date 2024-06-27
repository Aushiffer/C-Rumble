#include "controller.h"

Controller *create_controller() {
        Controller *controller = (Controller *)malloc(sizeof(Controller));

        if (!controller)
                return NULL;

        controller->right = 0;
        controller->left = 0;
        controller->up = 0;
        controller->down = 0;
        controller->punch = 0;
        controller->kick = 0;

        return controller;
}

void move_controller_right(Controller *controller) { controller->right ^= 1; }

void move_controller_left(Controller *controller) { controller->left ^= 1; }

void move_controller_up(Controller *controller) { controller->up ^= 1; }

void move_controller_down(Controller *controller) { controller->down ^= 1; }

void move_controller_punch(Controller *controller) { controller->punch ^= 1; }

void move_controller_kick(Controller *controller) { controller->kick ^= 1; }

void move_controller_special(Controller *controller) { controller->special ^= 1; }

void destroy_controller(Controller *controller) {
        if (controller)
                free(controller);
}