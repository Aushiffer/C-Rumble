#include "handle_pause.h"

void handle_pause_selection(
        ALLEGRO_SAMPLE *enable_pause_sample, ALLEGRO_SAMPLE_ID enable_pause_sample_id, 
        ALLEGRO_SAMPLE_ID stage1_sample_id, ALLEGRO_SAMPLE_ID stage2_sample_id, 
        ALLEGRO_SAMPLE_ID stage3_sample_id,  ALLEGRO_SAMPLE_ID stage4_sample_id,
        Fighter *player1, Fighter *player2,
        GameStates *game_states
) {
        if (game_states->rumble_pause) {
                al_play_sample(enable_pause_sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &enable_pause_sample_id);

                if (game_states->rumble_pause_select == 0) {
                        game_states->rumble_pause = 0;
                } else if (game_states->rumble_pause_select == 1) {
                        game_states->character_select = 1;
                        game_states->rumble = 0;
                } else if (game_states->rumble_pause_select == 2) {
                        game_states->menu = 1;
                        game_states->rumble = 0;
                }

                if (game_states->rumble_pause_select != 0) {
                        switch (game_states->stage_select_nav) {
                                case 0:
                                        al_stop_sample(&stage1_sample_id);

                                        break;

                                case 1:
                                        al_stop_sample(&stage2_sample_id);

                                        break;

                                case 2:
                                        al_stop_sample(&stage3_sample_id);

                                        break;

                                case 3:
                                        al_stop_sample(&stage4_sample_id);

                                        break;
                        }

                        player1->is_crouching = 0;
                        player2->is_crouching = 0;
                        player1->is_blocking = 0;
                        player2->is_blocking = 0;
                        player1->hitbox_upper->hitbox_y = player1->absolute_height;
                        player1->velocity_y = 0.0;
                        player1->on_ground = 1;
                        player2->hitbox_upper->hitbox_y = player2->absolute_height;
                        player2->velocity_y = 0.0;
                        player2->on_ground = 1;
                }
        }
}