#include "selector.h"

void handle_selection(char *selector_ptr, char num_options, unsigned char increase, ALLEGRO_SAMPLE *select_sample, ALLEGRO_SAMPLE_ID select_sample_id) {
        if (increase) {
                (*selector_ptr)++;
                                
                al_play_sample(select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &select_sample_id);

                if ((*selector_ptr) > num_options - 1)
                        (*selector_ptr) = 0;
        } else {
                (*selector_ptr)--;

                al_play_sample(select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &select_sample_id);

                if ((*selector_ptr) < 0)
                        (*selector_ptr) = num_options - 1;
        }
}