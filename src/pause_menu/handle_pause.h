#ifndef __HANDLE_PAUSE__
#define __HANDLE_PAUSE__

#include <allegro5/allegro_audio.h>
#include "../game_states/game_states.h"

void handle_pause_selection(
        ALLEGRO_SAMPLE *enable_pause_sample, ALLEGRO_SAMPLE_ID enable_pause_sample_id, 
        ALLEGRO_SAMPLE_ID stage1_sample_id, ALLEGRO_SAMPLE_ID stage2_sample_id, 
        GameStates *game_states
);

#endif // __HANDLE_PAUSE__