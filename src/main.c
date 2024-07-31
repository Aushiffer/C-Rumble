#include <allegro5/display.h>
#include <allegro5/keycodes.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "../error_enums/main_func_flags.h"
#include "controller/controller.h"
#include "fighter/fighter.h"
#include "game_states/game_states.h"
#include "draw/draw.h"
#include "hitbox/hitbox.h"
#include "load_spriteset/load_spriteset.h"
#include "pause_menu/handle_pause.h"
#include "selector/selector.h"
#include "destroy_resources/destroy_resources.h"

#define WIN_WIDTH 1366
#define WIN_HEIGHT 768
#define NUM_MENU_OPTIONS 2
#define NUM_CHARACTERS 4
#define NUM_STAGES 3
#define NUM_PAUSE_OPTIONS 3
#define FRAMES_PER_SECOND 30.0
#define FRAME_DURATION_IDLE 0.088888
#define FRAME_DURATION_RUNNING 0.066666
#define FRAME_DURATION_HI_PUNCH 0.088888
#define FRAME_DURATION_KICK 0.055555
#define FRAME_DURATION_LO_PUNCH 0.055555
#define MAXLEN_SPRITE_PATH 65
#define MAXLEN_PLAYER_WINS_STRING 17

int main(void) {
        al_init();
        al_install_keyboard();
        al_init_font_addon();
        al_init_ttf_addon();
        al_init_primitives_addon();
        al_init_image_addon();

        ALLEGRO_DISPLAY *display = al_create_display(WIN_WIDTH, WIN_HEIGHT);

        al_hide_mouse_cursor(display);

        BitmapGarbageArray *bitmap_garbage_array = create_bitmap_garbage_array();
        SampleGarbageArray *sample_garbage_array = create_sample_garbage_array();

        ALLEGRO_TIMER *timer = al_create_timer(1.0 / FRAMES_PER_SECOND);
        ALLEGRO_BITMAP *window_icon = al_load_bitmap("imgs/icons/window_icon.png");

        if (!window_icon) {
                fprintf(stderr, "[-] main(): failed to load the game icon\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, window_icon);
        al_set_display_icon(display, window_icon);

        ALLEGRO_BITMAP *viking_icon = al_load_bitmap("imgs/icons/viking_icon.png");

        if (!viking_icon) {
                fprintf(stderr, "[-] main(): failed to load viking_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, viking_icon);

        ALLEGRO_BITMAP *knight_icon = al_load_bitmap("imgs/icons/knight_icon.png");

        if (!knight_icon) {
                fprintf(stderr, "[-] main(): failed to load knight_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, knight_icon);

        ALLEGRO_BITMAP *spearwoman_icon = al_load_bitmap("imgs/icons/spearwoman_icon.png");

        if (!spearwoman_icon) {
                fprintf(stderr, "[-] main(): failed to load spearwoman_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, spearwoman_icon);

        ALLEGRO_BITMAP *fire_warrior_icon = al_load_bitmap("imgs/icons/fire_warrior_icon.png");

        if (!fire_warrior_icon) {
                fprintf(stderr, "[-] main(): failed to load fire_warrior_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, fire_warrior_icon);

        ALLEGRO_BITMAP *stage_select_arrow_icon = al_load_bitmap("imgs/icons/stage_select_arrow_icon.png");

        if (!stage_select_arrow_icon) {
                fprintf(stderr, "[-] main(): failed to load stage_select_arrow_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, stage_select_arrow_icon);
        
        ALLEGRO_BITMAP *stage_dark_forest = al_load_bitmap("imgs/stages/stage_dark_forest.png");

        if (!stage_dark_forest) {
                fprintf(stderr, "[-] main(): failed to load stage -> dark forest\n");
                exit(AL_LOAD_STAGE_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, stage_dark_forest);

        ALLEGRO_BITMAP *stage_abandoned_factory = al_load_bitmap("imgs/stages/stage_abandoned_factory.png");

        if (!stage_abandoned_factory) {
                fprintf(stderr, "[-] main(): failed to load stage -> abandoned factory\n");
                exit(AL_LOAD_STAGE_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, stage_abandoned_factory);

        ALLEGRO_BITMAP *stage_calm_forest = al_load_bitmap("imgs/stages/stage_calm_forest.png");

        if (!stage_calm_forest) {
                fprintf(stderr, "[-] main(): failed to load stage -> calm forest\n");
                exit(AL_LOAD_STAGE_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, stage_calm_forest);

        ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

        if (!event_queue) {
                fprintf(stderr, "[-] main(): failed to initialize event queue\n");
                exit(AL_CREATE_EVENT_QUEUE_ERROR);
        }

        ALLEGRO_FONT *menu_header_font = al_load_font("fonts/Osake.ttf", 200, 0);

        if (!menu_header_font) {
                fprintf(stderr, "[-] main(): failed to load menu_header_font\n");
                exit(AL_LOAD_FONT_ERROR);
        }

        ALLEGRO_FONT *menu_options_font = al_load_font("fonts/osaka-re.ttf", 64, 0);

        if (!menu_options_font) {
                fprintf(stderr, "[-] main(): failed to load menu_options_font\n");
                exit(AL_LOAD_FONT_ERROR);
        }

        ALLEGRO_FONT *character_select_header_font = al_load_font("fonts/Osake.ttf", 64, 0);

        if (!character_select_header_font) {
                fprintf(stderr, "[-] main(): failed to load character_select_header_font\n");
                exit(AL_LOAD_FONT_ERROR);
        }

        ALLEGRO_FONT *character_select_display_name_font = al_load_font("fonts/OsakaBrightDemoRegular.ttf", 32, 0);

        if (!character_select_display_name_font) {
                fprintf(stderr, "[-] main(): failed to load character_select_display_name_font\n");
                exit(AL_LOAD_FONT_ERROR);
        }

        ALLEGRO_FONT *stage_display_name_font = al_load_font("fonts/osaka-re.ttf", 32, 0);

        if (!stage_display_name_font) {
                fprintf(stderr, "[-] main(): failed to load stage_display_name_font\n");
                exit(AL_LOAD_FONT_ERROR);
        }

        ALLEGRO_FONT *rumble_display_character_name_font = al_load_font("fonts/Osake.ttf", 32, 0);

        if (!rumble_display_character_name_font) {
                fprintf(stderr, "[-] main(): failed to load rumble display character name font\n");
                exit(AL_LOAD_FONT_ERROR);
        }

        if (!al_install_audio() || !al_init_acodec_addon() || !al_reserve_samples(10)) {
                fprintf(stderr, "[-] main(): failed to set audio\n");
                exit(AL_SET_AUDIO_ERROR);
        }

        ALLEGRO_SAMPLE_ID menu_sample_id;
        ALLEGRO_SAMPLE *menu_sample = al_load_sample("music/DavidKBD - See You in Hell Pack - 02 - The Eternal Fight.ogg");

        if (!menu_sample) {
                fprintf(stderr, "[-] main(): failed to load menu music\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        ALLEGRO_SAMPLE_ID menu_select_sample_id;
        ALLEGRO_SAMPLE *menu_select_sample = al_load_sample("sfx/menu_select_option.ogg");

        if (!menu_select_sample) {
                fprintf(stderr, "[-] main(): failed to load menu_select_sample.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        ALLEGRO_SAMPLE_ID menu_confirm_sample_id;
        ALLEGRO_SAMPLE *menu_confirm_sample = al_load_sample("sfx/menu_confirm_option.ogg");

        if (!menu_confirm_sample) {
                fprintf(stderr, "[-] main(): failed to load menu_confirm_sample.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        ALLEGRO_SAMPLE_ID character_select_sample_id;
        ALLEGRO_SAMPLE *character_select_sample = al_load_sample("music/DavidKBD - See You in Hell Pack - 13 - Without Me.ogg");

        if (!character_select_sample) {
                fprintf(stderr, "[-] main(): failed to load character select screen music\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        ALLEGRO_SAMPLE_ID character_select_welcome_sample_id;
        ALLEGRO_SAMPLE *character_select_welcome_sample = al_load_sample("sfx/choose_your_character.ogg");

        if (!character_select_welcome_sample) {
                fprintf(stderr, "[-] main(): failed to load choose_your_character.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        ALLEGRO_SAMPLE_ID cancel_sound_sample_id;
        ALLEGRO_SAMPLE *cancel_sound_sample = al_load_sample("sfx/cancel.ogg");

        if (!cancel_sound_sample) {
                fprintf(stderr, "[-] main(): failed to load cancel.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        ALLEGRO_SAMPLE_ID character_confirm_sample_id;
        ALLEGRO_SAMPLE *character_select_confirm_sample = al_load_sample("sfx/character_confirm.ogg");

        if (!character_select_confirm_sample) {
                fprintf(stderr, "[-] main(): failed to load character_confirm.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        ALLEGRO_SAMPLE_ID stage_select_sample_id;
        ALLEGRO_SAMPLE *stage_select_sample = al_load_sample("music/DavidKBD - See You in Hell Pack - 15 - Fear.ogg");

        if (!stage_select_sample) {
                fprintf(stderr, "[-] main(): failed to load stage select music\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        ALLEGRO_SAMPLE_ID pause_sound_effect_id;
        ALLEGRO_SAMPLE *pause_sound_effect = al_load_sample("sfx/pause.ogg");

        if (!pause_sound_effect) {
                fprintf(stderr, "[-] main(): failed to load pause sound effect\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        ALLEGRO_SAMPLE_ID dark_forest_sample_id;
        ALLEGRO_SAMPLE *dark_forest_sample = al_load_sample("music/dark_forest_soundtrack.ogg");

        if (!dark_forest_sample) {
                fprintf(stderr, "[-] main(): failed to load -> dark forest soundtrack\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        ALLEGRO_SAMPLE_ID abandoned_factory_sample_id;
        ALLEGRO_SAMPLE *abandoned_factory_sample = al_load_sample("music/abandoned_factory_soundtrack.ogg");

        if (!abandoned_factory_sample) {
                fprintf(stderr, "[-] main(): failed to load -> abandoned factory soundtrack\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        ALLEGRO_SAMPLE_ID calm_forest_sample_id;
        ALLEGRO_SAMPLE *calm_forest_sample = al_load_sample("music/calm_forest_soundtrack.ogg");

        if (!calm_forest_sample) {
                fprintf(stderr, "[-] main(): failed to load -> calm forest soundtrack\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        ALLEGRO_SAMPLE_ID rumble_end_sample_id;
        ALLEGRO_SAMPLE *rumble_end_sample = al_load_sample("music/Final Fantasy VII - Victory Fanfare [HD].ogg");

        if (!rumble_end_sample) {
                fprintf(stderr, "[-] main(): failed to load rumble end sample\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }
        
        ALLEGRO_EVENT event;

        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_timer_event_source(timer));
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_start_timer(timer);
        al_set_window_title(display, "C-Rumble");

        GameStates *game_states = create_game_states(); /* Estrutura com as flags relativas aos diversos estados do jogo */

        if (!game_states) {
                fprintf(stderr, "[-] main(): failed to create game states structure\n");
                exit(INVALID_GAME_STATES_ERROR);
        }

        char sprite_path_buf[MAXLEN_SPRITE_PATH]; /* String variável usada para encontrar o caminho dos sprites */
        ALLEGRO_BITMAP **viking_idle_spriteset = load_spriteset(NUM_VIKING_IDLE_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_idle/viking_idle", MAXLEN_SPRITE_PATH);

        if (!viking_idle_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's idle sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_running_spriteset = load_spriteset(NUM_VIKING_IDLE_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_running/viking_running", MAXLEN_SPRITE_PATH);

        if (!viking_running_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's running sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_kick_spriteset = load_spriteset(NUM_VIKING_KICK_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_kick/viking_kick", MAXLEN_SPRITE_PATH);

        if (!viking_kick_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's kick sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_hi_block_spriteset = load_spriteset(NUM_VIKING_CROUCH_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_block/viking_block", MAXLEN_SPRITE_PATH);

        if (!viking_hi_block_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's block spriteset\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_hi_punch_spriteset = load_spriteset(NUM_VIKING_HI_PUNCH_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_hi_punch/viking_hi_punch", MAXLEN_SPRITE_PATH);

        if (!viking_hi_punch_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's hi punch sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_lo_punch_spriteset = load_spriteset(NUM_VIKING_LO_PUNCH_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_lo_punch/viking_lo_punch", MAXLEN_SPRITE_PATH);

        if (!viking_lo_punch_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's lo punch sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_crouch_spriteset = load_spriteset(NUM_VIKING_CROUCH_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_crouch/viking_crouch", MAXLEN_SPRITE_PATH);

        if (!viking_crouch_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's crouch sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_jump_spriteset = load_spriteset(NUM_VIKING_JUMP_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_jump/viking_jump", MAXLEN_SPRITE_PATH);

        if (!viking_jump_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's jump spriteset\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        float player1_x = 94.5;
        float player2_x = al_get_display_width(display) - 94.5;
        float viking_time_frame_idle = 0.0;
        float viking_time_frame_hi_punch_p1 = 0.0;
        float viking_time_frame_lo_punch_p1 = 0.0;
        float viking_time_frame_hi_punch_p2 = 0.0;
        float viking_time_frame_lo_punch_p2 = 0.0;
        float viking_time_frame_kick_p1 = 0.0;
        float viking_time_frame_kick_p2 = 0.0;
        float viking_time_frame_block = 0.0;
        float viking_time_frame_running = 0.0;
        unsigned int viking_current_frame_idle = 0;
        unsigned int viking_current_frame_hi_punch_p1 = 0;
        unsigned int viking_current_frame_lo_punch_p1 = 0;
        unsigned int viking_current_frame_hi_punch_p2 = 0;
        unsigned int viking_current_frame_lo_punch_p2 = 0;
        unsigned int viking_current_frame_kick_p1 = 0;
        unsigned int viking_current_frame_kick_p2 = 0;
        unsigned int viking_current_frame_running = 0;
        char wins_text_p1[MAXLEN_PLAYER_WINS_STRING];
        char wins_text_p2[MAXLEN_PLAYER_WINS_STRING];

        Fighter *player1_viking = create_fighter(
                189.0, 256.0, 
                player1_x, (float)al_get_display_height(display) - 256.0, 
                al_get_display_width(display), al_get_display_height(display), 
                viking_idle_spriteset, viking_hi_punch_spriteset, 
                viking_lo_punch_spriteset, viking_kick_spriteset, 
                viking_hi_block_spriteset, viking_running_spriteset, 
                viking_crouch_spriteset, viking_jump_spriteset, 
                0, (float)al_get_display_height(display) - 256.0
        );

        if (!player1_viking) {
                fprintf(stderr, "[-] main(): failed to load player 1 (viking)\n");
                exit(INVALID_FIGHTER_ERROR);
        }

        Fighter *player2_viking = create_fighter(
                189.0, 256.0, 
                player2_x, (float)al_get_display_height(display) - 256.0, 
                al_get_display_width(display), al_get_display_height(display), 
                viking_idle_spriteset, viking_hi_punch_spriteset, 
                viking_lo_punch_spriteset, viking_kick_spriteset, 
                viking_hi_block_spriteset, viking_running_spriteset, 
                viking_crouch_spriteset, viking_jump_spriteset, 
                1, (float)al_get_display_height(display) - 256.0
        );

        if (!player2_viking) {
                fprintf(stderr, "[-] main(): failed to load player 2 (viking)\n");
                exit(INVALID_FIGHTER_ERROR);
        }

        printf("\n[+] main(): success, starting game...\n");

        while (1) {
                al_wait_for_event(event_queue, &event);

                if (event.type == ALLEGRO_EVENT_TIMER) {
                        if (game_states->rumble_end) {
                                draw_rumble_end(game_states, display, menu_header_font, menu_options_font, player1_viking, player2_viking);
                        } else {
                                if (game_states->menu) {
                                        draw_menu(menu_header_font, menu_options_font, display, game_states);
                                } else if (game_states->character_select) {
                                        draw_character_select(
                                                character_select_header_font, menu_options_font, 
                                                character_select_display_name_font, display, 
                                                viking_icon, knight_icon,
                                                spearwoman_icon, fire_warrior_icon, 
                                                game_states
                                        );
                                        reset_players_x(player1_viking, player2_viking, display);
                                } else if (game_states->stage_select) {
                                        draw_stage_select(character_select_header_font, stage_display_name_font, display, stage_select_arrow_icon, game_states);
                                } else if (game_states->rumble) {
                                        if (!game_states->rumble_pause) {
                                                viking_time_frame_idle += 1.0 / FRAMES_PER_SECOND;
                                                viking_time_frame_hi_punch_p1 += 1.0 / FRAMES_PER_SECOND;
                                                viking_time_frame_lo_punch_p1 += 1.0 / FRAMES_PER_SECOND;
                                                viking_time_frame_hi_punch_p2 += 1.0 / FRAMES_PER_SECOND;
                                                viking_time_frame_lo_punch_p2 += 1.0 / FRAMES_PER_SECOND;
                                                viking_time_frame_kick_p1 += 1.0 / FRAMES_PER_SECOND;
                                                viking_time_frame_kick_p2 += 1.0 / FRAMES_PER_SECOND;
                                                viking_time_frame_block += 1.0 / FRAMES_PER_SECOND;
                                                viking_time_frame_running += 1.0 / FRAMES_PER_SECOND;

                                                if (viking_time_frame_idle >= FRAME_DURATION_IDLE) {
                                                        viking_time_frame_idle = 0;
                                                        viking_current_frame_idle = (viking_current_frame_idle + 1) % NUM_VIKING_IDLE_FRAMES;
                                                }

                                                if (player2_viking->health <= 0) {
                                                        handle_rumble_end(player1_viking, player2_viking, game_states);
                                                        reset_players_x(player1_viking, player2_viking, display);
                                                }
                                                
                                                if (player1_viking->health <= 0) {
                                                        handle_rumble_end(player2_viking, player1_viking, game_states);
                                                        reset_players_x(player1_viking, player2_viking, display);
                                                }

                                                if (player2_viking->stamina <= 0)
                                                        player2_viking->is_blocking = 0;

                                                if (player1_viking->stamina <= 0)
                                                        player1_viking->is_blocking = 0;

                                                draw_stages(display, stage_dark_forest, stage_abandoned_factory, stage_calm_forest, game_states);
                                                draw_health_bars(player1_viking, player2_viking, display);
                                                update_stamina(player1_viking, player2_viking);
                                                draw_stamina_bars(player1_viking, player2_viking, display);
                                                update_fighter_pos(player1_viking, player2_viking, al_get_display_width(display), display);
                                                snprintf(wins_text_p1, MAXLEN_PLAYER_WINS_STRING, "WINS: %d", player1_viking->rounds_won);
                                                snprintf(wins_text_p2, MAXLEN_PLAYER_WINS_STRING, "WINS: %d", player2_viking->rounds_won);
                                                draw_rumble_header(game_states, display, rumble_display_character_name_font, character_select_header_font, wins_text_p1, wins_text_p2);

                                                switch (game_states->rumble_fighter_p1) {
                                                        case 0:
                                                                if (player1_viking->is_crouching && player1_viking->is_blocking && player1_viking->on_ground) {
                                                                        draw_lo_blocking_animation(player1_viking);
                                                                } else if (player1_viking->is_punching && player1_viking->is_crouching && player1_viking->on_ground) {
                                                                        draw_lo_punch_animation(player1_viking, FRAME_DURATION_LO_PUNCH, &viking_time_frame_lo_punch_p1, &viking_current_frame_lo_punch_p1, NUM_VIKING_LO_PUNCH_FRAMES);
                                                                } else if (player1_viking->is_punching && viking_current_frame_lo_punch_p1 == 0 && player1_viking->on_ground) {
                                                                        draw_hi_punch_animation(player1_viking, FRAME_DURATION_HI_PUNCH, &viking_time_frame_hi_punch_p1, &viking_current_frame_hi_punch_p1, NUM_VIKING_HI_PUNCH_FRAMES);
                                                                } else if (player1_viking->is_kicking && player1_viking->on_ground) {
                                                                        draw_hi_kick_animation(player1_viking, FRAME_DURATION_KICK, &viking_time_frame_kick_p1, &viking_current_frame_kick_p1, NUM_VIKING_KICK_FRAMES);
                                                                } else if ((player1_viking->is_running_right || player1_viking->is_running_left) &&  player1_viking->on_ground) {
                                                                        draw_running_animation(player1_viking, FRAME_DURATION_RUNNING, &viking_time_frame_running, &viking_current_frame_running, &viking_current_frame_idle, NUM_VIKING_RUNNING_FRAMES);
                                                                } else if (player1_viking->is_crouching && !player1_viking->is_blocking && player1_viking->on_ground) {
                                                                        draw_crouching_animation(player1_viking);
                                                                } else if (player1_viking->is_blocking && player1_viking->on_ground) {
                                                                        draw_blocking_animation(player1_viking);
                                                                } else if (!player1_viking->on_ground) {
                                                                        draw_jumping_animation(player1_viking);
                                                                } else {
                                                                        draw_idle_animation(player1_viking, viking_current_frame_idle);
                                                                }

                                                                break;
                                                }

                                                switch (game_states->rumble_fighter_p2) {
                                                        case 0:
                                                                if (player2_viking->is_crouching && player2_viking->is_blocking) {
                                                                        draw_lo_blocking_animation(player2_viking);
                                                                } else if (player2_viking->is_punching && player2_viking->is_crouching) {
                                                                        draw_lo_punch_animation(player2_viking, FRAME_DURATION_LO_PUNCH, &viking_time_frame_lo_punch_p2, &viking_current_frame_lo_punch_p2, NUM_VIKING_LO_PUNCH_FRAMES);
                                                                } else if (player2_viking->is_punching && viking_current_frame_lo_punch_p2 == 0) {
                                                                        draw_hi_punch_animation(player2_viking, FRAME_DURATION_HI_PUNCH, &viking_time_frame_hi_punch_p2, &viking_current_frame_hi_punch_p2, NUM_VIKING_HI_PUNCH_FRAMES);
                                                                } else if (player2_viking->is_kicking) {
                                                                        draw_hi_kick_animation(player2_viking, FRAME_DURATION_KICK, &viking_time_frame_kick_p2, &viking_current_frame_kick_p2, NUM_VIKING_KICK_FRAMES);
                                                                } else if (player2_viking->is_running_right || player2_viking->is_running_left) {
                                                                        draw_running_animation(player2_viking, FRAME_DURATION_RUNNING, &viking_time_frame_running, &viking_current_frame_running, &viking_current_frame_idle, NUM_VIKING_RUNNING_FRAMES);
                                                                } else if (player2_viking->is_crouching && !player2_viking->is_blocking) {
                                                                        draw_crouching_animation(player2_viking);
                                                                } else if (player2_viking->is_blocking) {
                                                                        draw_blocking_animation(player2_viking);
                                                                } else {
                                                                        draw_idle_animation(player2_viking, viking_current_frame_idle);
                                                                }

                                                                break;
                                                }

                                        } else if (game_states->rumble_pause) {
                                                draw_pause(menu_header_font, menu_options_font, display, game_states);
                                        }
                                }
                        }

                        al_flip_display();
                } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
                        break;
                }

                if (game_states->menu) {
                        if (game_states->play_menu_sample)
                                al_play_sample(menu_sample, 0.25, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &menu_sample_id);
                        
                        game_states->play_menu_sample = 0;
                        game_states->play_character_select_welcome_sample = 1;
                        game_states->play_character_select_sample = 1;
                        game_states->character_select_nav_p1 = 0;
                        game_states->character_select_nav_p2 = 0;
                        game_states->character_select_nav_p1_confirm = 0;
                        game_states->character_select_nav_p2_confirm = 0;
                        game_states->play_rumble_end_sample = 0;

                        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                                if (event.keyboard.keycode == ALLEGRO_KEY_S || event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                                        handle_selection(
                                                &game_states->menu_select, NUM_MENU_OPTIONS, 
                                                1, menu_select_sample, 
                                                menu_select_sample_id
                                        );
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_W || event.keyboard.keycode == ALLEGRO_KEY_UP) {
                                        handle_selection(
                                                &game_states->menu_select, NUM_MENU_OPTIONS, 
                                                0, menu_select_sample, 
                                                menu_select_sample_id
                                        );
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                                        if (game_states->menu_select == 0) {
                                                al_stop_sample(&menu_sample_id);
                                                al_play_sample(menu_confirm_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_confirm_sample_id);

                                                game_states->menu = 0;
                                                game_states->menu_select = 0;
                                                game_states->character_select = 1;
                                        } else {
                                                al_play_sample(menu_confirm_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_confirm_sample_id);

                                                break;
                                        }
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_DELETE) {
                                        al_play_sample(cancel_sound_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);

                                        break;
                                }
                        }
                } else if (game_states->character_select) {
                        if (game_states->play_character_select_welcome_sample && game_states->play_character_select_sample) {
                                al_play_sample(character_select_welcome_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &character_select_welcome_sample_id);
                                al_play_sample(character_select_sample, 0.25, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &character_select_sample_id);
                        }

                        game_states->play_character_select_welcome_sample = 0;
                        game_states->play_character_select_sample = 0;
                        game_states->play_menu_sample = 1;
                        game_states->stage_select_nav = 0;
                        game_states->play_stage_select_sample = 1;
                        game_states->menu_select = 0;
                        player1_viking->rounds_won = 0;
                        player2_viking->rounds_won = 0;
                        player1_viking->health = MAX_HEALTH;
                        player2_viking->health = MAX_HEALTH;

                        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                                if (event.keyboard.keycode == ALLEGRO_KEY_DELETE) {
                                        game_states->menu = 1;
                                        game_states->character_select = 0;

                                        al_play_sample(cancel_sound_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);
                                        al_stop_sample(&character_select_sample_id);
                                }
                                
                                if (event.keyboard.keycode == ALLEGRO_KEY_D && !game_states->character_select_nav_p1_confirm) {
                                        handle_selection(
                                                &game_states->character_select_nav_p1, NUM_CHARACTERS, 
                                                1, menu_select_sample, 
                                                menu_select_sample_id
                                        );
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_A && !game_states->character_select_nav_p1_confirm) {
                                        handle_selection(
                                                &game_states->character_select_nav_p1, NUM_CHARACTERS, 
                                                0, menu_select_sample, 
                                                menu_select_sample_id
                                        );
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && !game_states->character_select_nav_p1_confirm) {
                                        game_states->character_select_nav_p1_confirm = 1;

                                        al_play_sample(character_select_confirm_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &character_confirm_sample_id);

                                        switch (game_states->character_select_nav_p1) {
                                                case 0:
                                                        game_states->rumble_fighter_p1 = 0;

                                                        break;

                                                case 1:
                                                        game_states->rumble_fighter_p1 = 1;

                                                        break;

                                                case 2:
                                                        game_states->rumble_fighter_p1 = 2;

                                                        break;

                                                case 3:
                                                        game_states->rumble_fighter_p1 = 3;

                                                        break;
                                        }
                                }

                                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && !game_states->character_select_nav_p2_confirm) {
                                        handle_selection(
                                                &game_states->character_select_nav_p2, NUM_CHARACTERS, 
                                                1, menu_select_sample, 
                                                menu_select_sample_id
                                        );
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && !game_states->character_select_nav_p2_confirm) {
                                        handle_selection(
                                                &game_states->character_select_nav_p2, NUM_CHARACTERS, 
                                                0, menu_select_sample, 
                                                menu_select_sample_id
                                        );
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && !game_states->character_select_nav_p2_confirm) {
                                        al_play_sample(character_select_confirm_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &character_confirm_sample_id);
                                        update_fighter_selectors(game_states);
                                }
                        }

                        if (game_states->character_select_nav_p1_confirm && game_states->character_select_nav_p2_confirm) {
                                al_stop_sample(&character_select_sample_id);

                                game_states->stage_select = 1;
                                game_states->character_select = 0;
                        }
                } else if (game_states->stage_select) {
                        if (game_states->play_stage_select_sample)
                                al_play_sample(stage_select_sample, 0.25, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &stage_select_sample_id);
                        
                        game_states->play_stage_select_sample = 0;
                        game_states->character_select_nav_p1 = 0;
                        game_states->character_select_nav_p2 = 0;
                        game_states->character_select_nav_p1_confirm = 0;
                        game_states->character_select_nav_p2_confirm = 0;
                        game_states->play_character_select_sample = 1;
                        game_states->play_character_select_welcome_sample = 1;
                        game_states->play_rumble_sample = 1;
                        game_states->rumble_pause = 0;
                        game_states->rumble_pause_select = 0;

                        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                                if (event.keyboard.keycode == ALLEGRO_KEY_DELETE) {
                                        game_states->stage_select = 0;
                                        game_states->character_select = 1;

                                        al_play_sample(cancel_sound_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);
                                        al_stop_sample(&stage_select_sample_id);
                                }
                                
                                if (event.keyboard.keycode == ALLEGRO_KEY_D || event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                                        handle_selection(
                                                &game_states->stage_select_nav, NUM_STAGES, 
                                                1, menu_select_sample, 
                                                menu_select_sample_id
                                        );
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_A || event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                                        handle_selection(
                                                &game_states->stage_select_nav, NUM_STAGES, 
                                                0, menu_select_sample, 
                                                menu_select_sample_id
                                        );
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER || event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                                        game_states->rumble = 1;
                                        game_states->stage_select = 0;

                                        al_stop_sample(&stage_select_sample_id);
                                }
                        }
                } else if (game_states->rumble) {
                        if (game_states->play_rumble_sample) {
                                switch (game_states->stage_select_nav) {
                                        case 0:
                                                al_play_sample(dark_forest_sample, 0.25, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &dark_forest_sample_id);

                                                break;

                                        case 1:
                                                al_play_sample(abandoned_factory_sample, 0.25, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &abandoned_factory_sample_id);

                                                break;

                                        case 2:
                                                al_play_sample(calm_forest_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &calm_forest_sample_id);

                                                break;
                                }
                        }

                        game_states->play_rumble_sample = 0;
                        game_states->character_select_nav_p1 = 0;
                        game_states->character_select_nav_p2 = 0;
                        game_states->character_select_nav_p1_confirm = 0;
                        game_states->character_select_nav_p2_confirm = 0;
                        game_states->play_character_select_welcome_sample = 1;
                        game_states->play_character_select_sample = 1;
                        game_states->play_menu_sample = 1;

                        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                                /* Menu de pause */
                                if (event.keyboard.keycode == ALLEGRO_KEY_DELETE) {
                                        game_states->rumble_pause ^= 1;
                                        
                                        al_play_sample(pause_sound_effect, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &pause_sound_effect_id);
                                }

                                if (event.keyboard.keycode == ALLEGRO_KEY_S) {
                                        if (game_states->rumble_pause) {
                                                handle_selection(
                                                        &game_states->rumble_pause_select, NUM_PAUSE_OPTIONS, 
                                                        1, menu_select_sample, 
                                                        menu_select_sample_id
                                                );
                                        }
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_W) {
                                        if (game_states->rumble_pause) {
                                                handle_selection(
                                                        &game_states->rumble_pause_select, NUM_PAUSE_OPTIONS, 
                                                        0, menu_select_sample, 
                                                        menu_select_sample_id
                                                );
                                        }
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                                        handle_pause_selection(menu_confirm_sample, menu_confirm_sample_id, dark_forest_sample_id, abandoned_factory_sample_id, calm_forest_sample_id, game_states);
                                }

                                /* Botões on-press */
                                if (!game_states->rumble_pause) {
                                        if (event.keyboard.keycode == ALLEGRO_KEY_Z) {
                                                player1_viking->is_punching = 1;

                                                if ((player2_viking->hitbox_upper->hitbox_x - player1_viking->hitbox_upper->hitbox_x) <= 231.0 
                                                && !(player1_viking->is_running_right || player1_viking->is_running_left || player1_viking->is_blocking || player2_viking->is_blocking))
                                                        player2_viking->health -= 7.0;

                                                viking_current_frame_hi_punch_p1 = 0;
                                                viking_time_frame_hi_punch_p1 = 0;
                                                viking_current_frame_lo_punch_p1 = 0;
                                                viking_time_frame_lo_punch_p1 = 0;      
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_X) {
                                                player1_viking->is_kicking = 1;
        
                                                if ((player2_viking->hitbox_upper->hitbox_x - player1_viking->hitbox_upper->hitbox_x) <= 206.0 
                                                && !(player1_viking->is_running_right || player1_viking->is_running_left || player1_viking->is_blocking ||player2_viking->is_blocking))
                                                        player2_viking->health -= 8.0;
        
                                                viking_current_frame_kick_p1 = 0;
                                                viking_time_frame_kick_p1 = 0;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && player1_viking->on_ground) {
                                                player1_viking->velocity_y = JUMP_STRENGTH;
                                                player1_viking->on_ground = 0;
                                                player1_viking->controller->up = 1;
                                        }

                                        if (event.keyboard.keycode == ALLEGRO_KEY_K) {
                                                player2_viking->is_punching = 1;

                                                if ((player2_viking->hitbox_upper->hitbox_x - player1_viking->hitbox_upper->hitbox_x) <= 231.0 
                                                && !(player2_viking->is_running_right || player2_viking->is_running_left || player2_viking->is_blocking || player1_viking->is_blocking))
                                                        player1_viking->health -= 7.0;

                                                viking_current_frame_hi_punch_p2 = 0;
                                                viking_time_frame_hi_punch_p2 = 0;
                                                viking_current_frame_lo_punch_p2 = 0;
                                                viking_time_frame_lo_punch_p2 = 0;      
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_L) {
                                                player2_viking->is_kicking = 1;
        
                                                if ((player2_viking->hitbox_upper->hitbox_x - player1_viking->hitbox_upper->hitbox_x) <= 206.0 
                                                && !(player2_viking->is_running_right || player2_viking->is_running_left || player2_viking->is_blocking || player1_viking->is_blocking))
                                                        player1_viking->health -= 8.0;
        
                                                viking_current_frame_kick_p2 = 0;
                                                viking_time_frame_kick_p2 = 0;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_SLASH && player2_viking->on_ground) {
                                                player2_viking->velocity_y = JUMP_STRENGTH;
                                                player2_viking->on_ground = 0;
                                                player2_viking->controller->up = 1;
                                        }
                                }
                        }

                        if (!game_states->rumble_pause) {
                                game_states->rumble_pause_select = 0;

                                /* Botões on-hold */
                                if (event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_UP) {
                                        if (event.keyboard.keycode == ALLEGRO_KEY_D) {
                                                move_controller_right(player1_viking->controller);

                                                player1_viking->is_running_right ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_A) {
                                                move_controller_left(player1_viking->controller);

                                                player1_viking->is_running_left ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_S) {
                                                move_controller_down(player1_viking->controller);

                                                player1_viking->is_crouching ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_C) {
                                                if (player1_viking->stamina > 0) {
                                                        move_controller_block(player1_viking->controller);

                                                        player1_viking->is_blocking ^= 1;
                                                }
                                        }

                                        if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                                                move_controller_right(player2_viking->controller);

                                                player2_viking->is_running_right ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                                                move_controller_left(player2_viking->controller);

                                                player2_viking->is_running_left ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                                                move_controller_down(player2_viking->controller);

                                                player2_viking->is_crouching ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_J) {
                                                move_controller_block(player2_viking->controller);

                                                player2_viking->is_blocking ^= 1;
                                        }
                                }
                        }
                } else if (game_states->rumble_end) {
                        switch (game_states->stage_select_nav) {
                                case 0:
                                        al_stop_sample(&dark_forest_sample_id);

                                        break;
                                
                                case 1:
                                        al_stop_sample(&abandoned_factory_sample_id);

                                        break;

                                case 2:
                                                al_stop_sample(&calm_forest_sample_id);

                                        break;
                        }

                        if (game_states->play_rumble_end_sample)
                                al_play_sample(rumble_end_sample, 0.25, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &rumble_end_sample_id);

                        game_states->play_menu_sample = 1;
                        game_states->play_rumble_end_sample = 0;

                        if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                                al_play_sample(menu_confirm_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_confirm_sample_id);
                                al_stop_sample(&rumble_end_sample_id);

                                game_states->rumble_end = 0;
                                game_states->rumble = 0;
                                game_states->menu = 1;
                        }
                }
        }

        printf("\n[+] main(): exiting game...\n");
        destroy_fonts(menu_header_font, menu_options_font, character_select_header_font, character_select_display_name_font);
        destroy_bitmap_garbage_array(bitmap_garbage_array);
        destroy_fighter(player1_viking, game_states);
        destroy_game_states(game_states);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(event_queue);
        al_uninstall_audio();
        al_uninstall_keyboard();

        return 0;
}