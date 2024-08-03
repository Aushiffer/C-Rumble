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
#include "load_spriteset/load_spriteset.h"
#include "pause_menu/handle_pause.h"
#include "selector/selector.h"
#include "destroy_resources/destroy_resources.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define NUM_MENU_OPTIONS 2
#define NUM_CHARACTERS 4
#define NUM_STAGES 4
#define NUM_PAUSE_OPTIONS 3
#define FRAMES_PER_SECOND 30.0
#define FRAME_DURATION_IDLE 0.066666
#define FRAME_DURATION_JUMP 0.20
#define FRAME_DURATION_RUNNING 0.066666
#define FRAME_DURATION_HI_PUNCH 0.125
#define FRAME_DURATION_LO_PUNCH 0.125
#define FRAME_DURATION_AIR_PUNCH 0.150
#define FRAME_DURATION_HI_KICK 0.165
#define FRAME_DURATION_LO_KICK 0.165
#define FRAME_DURATION_AIR_KICK 0.145
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

        if (!bitmap_garbage_array) {
                fprintf(stderr, "[-] main(): failed to create the bitmap garbage array\n");
                exit(INVALID_GARBAGE_ARRAY);
        }

        SampleGarbageArray *sample_garbage_array = create_sample_garbage_array();

        if (!sample_garbage_array) {
                fprintf(stderr, "[-] main(): failed to create the sample garbage array\n");
                exit(INVALID_GARBAGE_ARRAY);
        }

        FontGarbageArray *font_garbage_array = create_font_garbage_array();

        if (!font_garbage_array) {
                fprintf(stderr, "[-] main(): failed to create the font garbage array\n");
                exit(INVALID_GARBAGE_ARRAY);
        }

        ALLEGRO_TIMER *timer = al_create_timer(1.0 / FRAMES_PER_SECOND);
        ALLEGRO_BITMAP *window_icon = al_load_bitmap("imgs/icons/window_icon.png");

        if (!window_icon) {
                fprintf(stderr, "[-] main(): failed to load the game icon\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, window_icon);
        al_set_display_icon(display, window_icon);

        ALLEGRO_BITMAP *ryu_icon = al_load_bitmap("imgs/icons/ryu_icon.png");

        if (!ryu_icon) {
                fprintf(stderr, "[-] main(): failed to load ryu_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);       
        }

        insert_bitmap_array(bitmap_garbage_array, ryu_icon);    

        ALLEGRO_BITMAP *ken_icon = al_load_bitmap("imgs/icons/ken_icon.png");

        if (!ken_icon) {
                fprintf(stderr, "[-] main(): failed to load ken_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, ken_icon);

        ALLEGRO_BITMAP *guile_icon = al_load_bitmap("imgs/icons/guile_icon.png");

        if (!guile_icon) {
                fprintf(stderr, "[-] main(): failed to load guile_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, guile_icon);

        ALLEGRO_BITMAP *vega_icon = al_load_bitmap("imgs/icons/vega_icon.png");

        if (!vega_icon) {
                fprintf(stderr, "[-] main(): failed to load vega_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, vega_icon);

        ALLEGRO_BITMAP *stage_select_arrow_icon = al_load_bitmap("imgs/icons/stage_select_arrow_icon.png");

        if (!stage_select_arrow_icon) {                 
                fprintf(stderr, "[-] main(): failed to load stage_select_arrow_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, stage_select_arrow_icon);
        
        ALLEGRO_BITMAP *stage_ryu = al_load_bitmap("imgs/stages/stage_ryu.png");

        if (!stage_ryu) {
                fprintf(stderr, "[-] main(): failed to load stage -> Suzaku Castle\n");
                exit(AL_LOAD_STAGE_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, stage_ryu);

        ALLEGRO_BITMAP *stage_ken = al_load_bitmap("imgs/stages/stage_ken.png");

        if (!stage_ken) {
                fprintf(stderr, "[-] main(): failed to load stage -> Battle Harbor\n");
                exit(AL_LOAD_STAGE_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, stage_ken);

        ALLEGRO_BITMAP *stage_guile = al_load_bitmap("imgs/stages/stage_guile.png");

        if (!stage_guile) {
                fprintf(stderr, "[-] main(): failed to load stage -> Air Force Base\n");
                exit(AL_LOAD_STAGE_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, stage_guile);

        ALLEGRO_BITMAP *stage_vega = al_load_bitmap("imgs/stages/stage_vega.png");

        if (!stage_vega) {
                fprintf(stderr, "[-] main(): failed to load stage -> Méson De La Taberna\n");
                exit(AL_LOAD_STAGE_ERROR);
        }

        insert_bitmap_array(bitmap_garbage_array, stage_vega);

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

        insert_font_array(font_garbage_array, menu_header_font);

        ALLEGRO_FONT *menu_options_font = al_load_font("fonts/osaka-re.ttf", 64, 0);

        if (!menu_options_font) {
                fprintf(stderr, "[-] main(): failed to load menu_options_font\n");
                exit(AL_LOAD_FONT_ERROR);
        }

        insert_font_array(font_garbage_array, menu_options_font);

        ALLEGRO_FONT *character_select_header_font = al_load_font("fonts/Osake.ttf", 64, 0);

        if (!character_select_header_font) {
                fprintf(stderr, "[-] main(): failed to load character_select_header_font\n");
                exit(AL_LOAD_FONT_ERROR);
        }

        insert_font_array(font_garbage_array, character_select_header_font);

        ALLEGRO_FONT *character_select_display_name_font = al_load_font("fonts/OsakaBrightDemoRegular.ttf", 32, 0);

        if (!character_select_display_name_font) {
                fprintf(stderr, "[-] main(): failed to load character_select_display_name_font\n");
                exit(AL_LOAD_FONT_ERROR);
        }

        insert_font_array(font_garbage_array, character_select_display_name_font);

        ALLEGRO_FONT *stage_display_name_font = al_load_font("fonts/osaka-re.ttf", 32, 0);

        if (!stage_display_name_font) {
                fprintf(stderr, "[-] main(): failed to load stage_display_name_font\n");
                exit(AL_LOAD_FONT_ERROR);
        }

        insert_font_array(font_garbage_array, stage_display_name_font);

        ALLEGRO_FONT *rumble_display_character_name_font = al_load_font("fonts/Osake.ttf", 32, 0);

        if (!rumble_display_character_name_font) {
                fprintf(stderr, "[-] main(): failed to load rumble display character name font\n");
                exit(AL_LOAD_FONT_ERROR);
        }

        insert_font_array(font_garbage_array, rumble_display_character_name_font);

        if (!al_install_audio() || !al_init_acodec_addon() || !al_reserve_samples(10)) {
                fprintf(stderr, "[-] main(): failed to set audio\n");
                exit(AL_SET_AUDIO_ERROR);
        }

        ALLEGRO_SAMPLE_ID menu_sample_id;
        ALLEGRO_SAMPLE *menu_sample = al_load_sample("music/Street Fighter II Turbo Snes Music - Opening Theme.ogg");

        if (!menu_sample) {
                fprintf(stderr, "[-] main(): failed to load menu music\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        insert_sample_array(sample_garbage_array, menu_sample);

        ALLEGRO_SAMPLE_ID menu_select_sample_id;
        ALLEGRO_SAMPLE *menu_select_sample = al_load_sample("sfx/menu_select_option.ogg");

        if (!menu_select_sample) {
                fprintf(stderr, "[-] main(): failed to load menu_select_sample.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        insert_sample_array(sample_garbage_array, menu_select_sample);

        ALLEGRO_SAMPLE_ID menu_confirm_sample_id;
        ALLEGRO_SAMPLE *menu_confirm_sample = al_load_sample("sfx/menu_confirm_option.ogg");

        if (!menu_confirm_sample) {
                fprintf(stderr, "[-] main(): failed to load menu_confirm_sample.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        insert_sample_array(sample_garbage_array, menu_confirm_sample);

        ALLEGRO_SAMPLE_ID character_select_sample_id;
        ALLEGRO_SAMPLE *character_select_sample = al_load_sample("music/Street Fighter II SNES-Player Select.ogg");

        if (!character_select_sample) {
                fprintf(stderr, "[-] main(): failed to load character select screen music\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        insert_sample_array(sample_garbage_array, character_select_sample);

        ALLEGRO_SAMPLE_ID character_select_welcome_sample_id;
        ALLEGRO_SAMPLE *character_select_welcome_sample = al_load_sample("sfx/choose_your_character.ogg");

        if (!character_select_welcome_sample) {
                fprintf(stderr, "[-] main(): failed to load choose_your_character.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        insert_sample_array(sample_garbage_array, character_select_welcome_sample);

        ALLEGRO_SAMPLE_ID cancel_sound_sample_id;
        ALLEGRO_SAMPLE *cancel_sound_sample = al_load_sample("sfx/cancel.ogg");

        if (!cancel_sound_sample) {
                fprintf(stderr, "[-] main(): failed to load cancel.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        insert_sample_array(sample_garbage_array, cancel_sound_sample);

        ALLEGRO_SAMPLE_ID character_confirm_sample_id;
        ALLEGRO_SAMPLE *character_select_confirm_sample = al_load_sample("sfx/character_confirm.ogg");

        if (!character_select_confirm_sample) {
                fprintf(stderr, "[-] main(): failed to load character_confirm.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        insert_sample_array(sample_garbage_array, character_select_confirm_sample);

        ALLEGRO_SAMPLE_ID pause_sound_effect_id;
        ALLEGRO_SAMPLE *pause_sound_effect = al_load_sample("sfx/pause.ogg");

        if (!pause_sound_effect) {
                fprintf(stderr, "[-] main(): failed to load pause sound effect\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        insert_sample_array(sample_garbage_array, pause_sound_effect);

        ALLEGRO_SAMPLE_ID ryu_theme_sample_id;
        ALLEGRO_SAMPLE *ryu_theme_sample = al_load_sample("music/ryu_theme.ogg");

        if (!ryu_theme_sample) {
                fprintf(stderr, "[-] main(): failed to load Ryu's\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        insert_sample_array(sample_garbage_array, ryu_theme_sample);

        ALLEGRO_SAMPLE_ID ken_theme_sample_id;
        ALLEGRO_SAMPLE *ken_theme_sample = al_load_sample("music/ken_theme.ogg");

        if (!ken_theme_sample) {
                fprintf(stderr, "[-] main(): failed to load Ken's theme\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        insert_sample_array(sample_garbage_array, ken_theme_sample);

        ALLEGRO_SAMPLE_ID guile_theme_sample_id;
        ALLEGRO_SAMPLE *guile_theme_sample = al_load_sample("music/guile_theme.ogg");

        if (!guile_theme_sample) {
                fprintf(stderr, "[-] main(): failed to load Guile's theme\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        insert_sample_array(sample_garbage_array, guile_theme_sample);

        ALLEGRO_SAMPLE_ID vega_theme_sample_id;
        ALLEGRO_SAMPLE *vega_theme_sample = al_load_sample("music/vega_theme.ogg");

        if (!vega_theme_sample) {
               fprintf(stderr, "[-] main(): failed to load Vega's theme\n");
               exit(AL_LOAD_SAMPLE_ERROR); 
        }

        insert_sample_array(sample_garbage_array, vega_theme_sample);

        ALLEGRO_SAMPLE_ID rumble_end_sample_id;
        ALLEGRO_SAMPLE *rumble_end_sample = al_load_sample("music/Final Fantasy VII - Victory Fanfare [HD].ogg");

        if (!rumble_end_sample) {
                fprintf(stderr, "[-] main(): failed to load rumble end sample\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        insert_sample_array(sample_garbage_array, rumble_end_sample);

        ALLEGRO_SAMPLE_ID hit_sound_effect_sample_id;
        ALLEGRO_SAMPLE *hit_sound_effect_sample = al_load_sample("sfx/hit_sfx.ogg");

        if (!hit_sound_effect_sample) {
                fprintf(stderr, "[-] main(): failed to load the hit sfx\n");
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
        ALLEGRO_BITMAP **ryu_idle_spriteset = load_spriteset(NUM_RYU_IDLE_FRAMES, sprite_path_buf, "imgs/sprites/Ryu/ryu_idle/ryu_idle", MAXLEN_SPRITE_PATH);

        if (!ryu_idle_spriteset) {
                fprintf(stderr, "[-] main(): failed to load Ryu's idle sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **ryu_running_spriteset = load_spriteset(NUM_RYU_RUNNING_FRAMES, sprite_path_buf, "imgs/sprites/Ryu/ryu_running/ryu_running", MAXLEN_SPRITE_PATH);

        if (!ryu_running_spriteset) {
                fprintf(stderr, "[-] main(): failed to load Ryu's running sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }                                               

        ALLEGRO_BITMAP **ryu_hi_kick_spriteset = load_spriteset(NUM_RYU_HI_KICK_FRAMES, sprite_path_buf, "imgs/sprites/Ryu/ryu_hi_kick/ryu_hi_kick", MAXLEN_SPRITE_PATH);

        if (!ryu_hi_kick_spriteset) {
                fprintf(stderr, "[-] main(): failed to load Ryu's hi kick sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }
        
        ALLEGRO_BITMAP **ryu_lo_kick_spriteset = load_spriteset(NUM_RYU_LO_KICK_FRAMES, sprite_path_buf, "imgs/sprites/Ryu/ryu_lo_kick/ryu_lo_kick", MAXLEN_SPRITE_PATH);

        if (!ryu_lo_kick_spriteset) {
                fprintf(stderr, "[-] main(): failed to load Ryu's lo kick sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **ryu_air_kick_spriteset = load_spriteset(NUM_RYU_AIR_KICK_FRAMES, sprite_path_buf, "imgs/sprites/Ryu/ryu_air_kick/ryu_air_kick", MAXLEN_SPRITE_PATH);

        if (!ryu_air_kick_spriteset) {
                fprintf(stderr, "[-] main(): failed to load Ryu's air kick sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **ryu_hi_block_spriteset = load_spriteset(NUM_RYU_BLOCK_FRAMES, sprite_path_buf, "imgs/sprites/Ryu/ryu_hi_block/ryu_hi_block", MAXLEN_SPRITE_PATH);

        if (!ryu_hi_block_spriteset) {
                fprintf(stderr, "[-] main(): failed to load Ryu's hi block spriteset\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **ryu_lo_block_spriteset = load_spriteset(NUM_RYU_BLOCK_FRAMES, sprite_path_buf, "imgs/sprites/Ryu/ryu_lo_block/ryu_lo_block", MAXLEN_SPRITE_PATH);

        if (!ryu_lo_block_spriteset) {
                fprintf(stderr, "[-] main(): failed to load Ryu's lo block spriteset\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **ryu_hi_punch_spriteset = load_spriteset(NUM_RYU_HI_PUNCH_FRAMES, sprite_path_buf, "imgs/sprites/Ryu/ryu_hi_punch/ryu_hi_punch", MAXLEN_SPRITE_PATH);

        if (!ryu_hi_punch_spriteset) {
                fprintf(stderr, "[-] main(): failed to load Ryu's hi punch sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **ryu_lo_punch_spriteset = load_spriteset(NUM_RYU_LO_PUNCH_FRAMES, sprite_path_buf, "imgs/sprites/Ryu/ryu_lo_punch/ryu_lo_punch", MAXLEN_SPRITE_PATH);

        if (!ryu_lo_punch_spriteset) {
                fprintf(stderr, "[-] main(): failed to load Ryu's lo punch sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **ryu_air_punch_spriteset = load_spriteset(NUM_RYU_AIR_PUNCH_FRAMES, sprite_path_buf, "imgs/sprites/Ryu/ryu_air_punch/ryu_air_punch", MAXLEN_SPRITE_PATH);

        if (!ryu_air_punch_spriteset) {
                fprintf(stderr, "[-] main(): failed to load Ryu's air punch sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **ryu_crouch_spriteset = load_spriteset(NUM_RYU_CROUCH_FRAMES, sprite_path_buf, "imgs/sprites/Ryu/ryu_crouch/ryu_crouch", MAXLEN_SPRITE_PATH);

        if (!ryu_crouch_spriteset) {
                fprintf(stderr, "[-] main(): failed to load Ryu's crouch sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **ryu_jump_spriteset = load_spriteset(NUM_RYU_JUMP_FRAMES, sprite_path_buf, "imgs/sprites/Ryu/ryu_jumping/ryu_jumping", MAXLEN_SPRITE_PATH);

        if (!ryu_jump_spriteset) {
                fprintf(stderr, "[-] main(): failed to load Ryu's jump spriteset\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        float player1_x = 94.5;
        float player2_x = al_get_display_width(display) - 94.5;
        float ryu_time_frame_idle = 0.0;
        float ryu_time_frame_hi_punch_p1 = 0.0;
        float ryu_time_frame_lo_punch_p1 = 0.0;
        float ryu_time_frame_air_punch_p1 = 0.0;
        float ryu_time_frame_hi_punch_p2 = 0.0;
        float ryu_time_frame_lo_punch_p2 = 0.0;
        float ryu_time_frame_air_punch_p2 = 0.0;
        float ryu_time_frame_hi_kick_p1 = 0.0;
        float ryu_time_frame_hi_kick_p2 = 0.0;
        float ryu_time_frame_lo_kick_p1 = 0.0;
        float ryu_time_frame_lo_kick_p2 = 0.0;
        float ryu_time_frame_air_kick_p1 = 0.0;
        float ryu_time_frame_air_kick_p2 = 0.0;
        float ryu_time_frame_running = 0.0;
        float ryu_time_frame_jump_p1 = 0.0;
        float ryu_time_frame_jump_p2 = 0.0;
        unsigned int ryu_current_frame_idle = 0;
        unsigned int ryu_current_frame_hi_punch_p1 = 0;
        unsigned int ryu_current_frame_lo_punch_p1 = 0;
        unsigned int ryu_current_frame_air_punch_p1 = 0;
        unsigned int ryu_current_frame_hi_punch_p2 = 0;
        unsigned int ryu_current_frame_lo_punch_p2 = 0;
        unsigned int ryu_current_frame_air_punch_p2 = 0;
        unsigned int ryu_current_frame_hi_kick_p1 = 0;
        unsigned int ryu_current_frame_lo_kick_p1 = 0;
        unsigned int ryu_current_frame_air_kick_p1 = 0;
        unsigned int ryu_current_frame_hi_kick_p2 = 0;
        unsigned int ryu_current_frame_lo_kick_p2 = 0;
        unsigned int ryu_current_frame_air_kick_p2 = 0;
        unsigned int ryu_current_frame_running = 0;
        unsigned int ryu_current_frame_jump_p1 = 0;
        unsigned int ryu_current_frame_jump_p2 = 0;
        char wins_text_p1[MAXLEN_PLAYER_WINS_STRING];
        char wins_text_p2[MAXLEN_PLAYER_WINS_STRING];

        Fighter *player1_ryu = create_fighter(
                166.0, 256.0, 
                player1_x, (float)al_get_display_height(display) - 295.0, 
                al_get_display_width(display), al_get_display_height(display), 
                ryu_idle_spriteset, ryu_hi_punch_spriteset, 
                ryu_lo_punch_spriteset, ryu_air_punch_spriteset,
                ryu_hi_kick_spriteset, ryu_lo_kick_spriteset,
                ryu_air_kick_spriteset, ryu_hi_block_spriteset, 
                ryu_lo_block_spriteset, ryu_running_spriteset, 
                ryu_crouch_spriteset, ryu_jump_spriteset, 
                0, (float)al_get_display_height(display) - 295.0
        );

        if (!player1_ryu) {
                fprintf(stderr, "[-] main(): failed to load player 1 (Ryu)\n");
                exit(INVALID_FIGHTER_ERROR);
        }

        Fighter *player2_ryu = create_fighter(
                166.0, 256.0, 
                player2_x, (float)al_get_display_height(display) - 295.0, 
                al_get_display_width(display), al_get_display_height(display), 
                ryu_idle_spriteset, ryu_hi_punch_spriteset, 
                ryu_lo_punch_spriteset, ryu_air_punch_spriteset,
                ryu_hi_kick_spriteset, ryu_lo_kick_spriteset,
                ryu_air_kick_spriteset, ryu_hi_block_spriteset, 
                ryu_lo_block_spriteset, ryu_running_spriteset, 
                ryu_crouch_spriteset, ryu_jump_spriteset, 
                1, (float)al_get_display_height(display) - 295.0
        );

        if (!player2_ryu) {
                fprintf(stderr, "[-] main(): failed to load player 2 (Ryu)\n");
                exit(INVALID_FIGHTER_ERROR);
        }

        printf("\n[+] main(): success, starting game...\n");

        while (1) {
                al_wait_for_event(event_queue, &event);

                if (event.type == ALLEGRO_EVENT_TIMER) {
                        if (game_states->rumble_end) {
                                draw_rumble_end(game_states, display, menu_header_font, menu_options_font, player1_ryu, player2_ryu);
                        } else {
                                if (game_states->menu) {
                                        draw_menu(menu_header_font, menu_options_font, display, game_states);
                                } else if (game_states->character_select) {
                                        draw_character_select(
                                                character_select_header_font, menu_options_font, 
                                                character_select_display_name_font, display, 
                                                ryu_icon, ken_icon,
                                                guile_icon, vega_icon, 
                                                game_states
                                        );
                                        reset_players_x(player1_ryu, player2_ryu, display);
                                } else if (game_states->stage_select) {
                                        draw_stage_select(character_select_header_font, stage_display_name_font, display, stage_select_arrow_icon, game_states);
                                } else if (game_states->rumble) {
                                        if (!game_states->rumble_pause) {
                                                if (game_states->rumble_fighter_p1 == 0 || game_states->rumble_fighter_p2 == 0) {
                                                        ryu_time_frame_idle += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_hi_punch_p1 += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_lo_punch_p1 += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_air_punch_p1 += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_air_kick_p2 += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_hi_punch_p2 += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_lo_punch_p2 += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_hi_kick_p1 += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_hi_kick_p2 += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_lo_kick_p1 += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_lo_kick_p2 += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_air_kick_p1 += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_air_kick_p2 += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_running += 1.0 / FRAMES_PER_SECOND;
                                                        ryu_time_frame_jump_p1 += 1.0 / FRAMES_PER_SECOND;

                                                        if (ryu_time_frame_idle >= FRAME_DURATION_IDLE) {
                                                                ryu_time_frame_idle = 0;
                                                                ryu_current_frame_idle = (ryu_current_frame_idle + 1) % NUM_RYU_IDLE_FRAMES;
                                                        }
                                                } else if (game_states->rumble_fighter_p1 == 1 || game_states->rumble_fighter_p2 == 1) {

                                                } else if (game_states->rumble_fighter_p1 == 2 || game_states->rumble_fighter_p2 == 2) {

                                                } else if (game_states->rumble_fighter_p1 == 3 || game_states->rumble_fighter_p2 == 3) {

                                                }

                                                if (player2_ryu->health <= 0) {
                                                        handle_rumble_end(player1_ryu, player2_ryu, game_states);
                                                        reset_players_x(player1_ryu, player2_ryu, display);
                                                }
                                                
                                                if (player1_ryu->health <= 0) {
                                                        handle_rumble_end(player2_ryu, player1_ryu, game_states);
                                                        reset_players_x(player1_ryu, player2_ryu, display);
                                                }

                                                if (player2_ryu->stamina <= 0 && player2_ryu->is_blocking)
                                                        player2_ryu->is_blocking = 0;

                                                if (player1_ryu->stamina <= 0 && player1_ryu->is_blocking)
                                                        player1_ryu->is_blocking = 0;
                                                
                                                compute_hit(
                                                        player1_ryu, player2_ryu, 
                                                        ryu_current_frame_hi_kick_p1, ryu_current_frame_lo_kick_p1, 
                                                        ryu_current_frame_air_kick_p1, ryu_current_frame_hi_punch_p1, 
                                                        ryu_current_frame_lo_punch_p1, ryu_current_frame_air_punch_p1, 
                                                        2, 1, 
                                                        2, 2, 
                                                        1, 2,
                                                        ryu_current_frame_hi_kick_p2, ryu_current_frame_lo_kick_p2,
                                                        ryu_current_frame_air_kick_p2, ryu_current_frame_hi_punch_p2,
                                                        ryu_current_frame_lo_punch_p2, ryu_current_frame_air_punch_p2,
                                                        2, 1,
                                                        2, 2,
                                                        1, 2,
                                                        hit_sound_effect_sample, hit_sound_effect_sample_id
                                                );

                                                draw_stages(display, stage_ryu, stage_ken, stage_guile, stage_vega, game_states);
                                                draw_health_bars(player1_ryu, player2_ryu, display);
                                                update_stamina(player1_ryu, player2_ryu);
                                                draw_stamina_bars(player1_ryu, player2_ryu, display);
                                                update_fighter_pos(player1_ryu, player2_ryu, al_get_display_width(display));
                                                snprintf(wins_text_p1, MAXLEN_PLAYER_WINS_STRING, "WINS: %d", player1_ryu->rounds_won);
                                                snprintf(wins_text_p2, MAXLEN_PLAYER_WINS_STRING, "WINS: %d", player2_ryu->rounds_won);
                                                draw_rumble_header(game_states, display, rumble_display_character_name_font, character_select_header_font, wins_text_p1, wins_text_p2);

                                                switch (game_states->rumble_fighter_p1) {
                                                        case 0:
                                                                if (player1_ryu->is_crouching && player1_ryu->is_blocking && player1_ryu->on_ground) {
                                                                        draw_lo_blocking_animation(player1_ryu);
                                                                } else if (player1_ryu->is_kicking && !player1_ryu->on_ground && ryu_current_frame_hi_kick_p1 == 0 && ryu_current_frame_lo_kick_p1 == 0) {
                                                                        draw_air_kick_animation(player1_ryu, FRAME_DURATION_AIR_KICK, &ryu_time_frame_air_kick_p1, &ryu_current_frame_air_kick_p1, NUM_RYU_AIR_KICK_FRAMES);
                                                                } else if (player1_ryu->is_kicking && player1_ryu->is_crouching && player1_ryu->on_ground && ryu_current_frame_hi_kick_p1 == 0) {
                                                                        draw_lo_kick_animation(player1_ryu, FRAME_DURATION_LO_KICK, &ryu_time_frame_hi_kick_p1, &ryu_current_frame_lo_kick_p1, NUM_RYU_LO_KICK_FRAMES);
                                                                } else if (player1_ryu->is_punching && !player1_ryu->on_ground) {
                                                                        draw_air_punch_animation(player1_ryu, FRAME_DURATION_AIR_PUNCH, &ryu_time_frame_air_punch_p1, &ryu_current_frame_air_punch_p1, NUM_RYU_AIR_PUNCH_FRAMES);
                                                                } else if (player1_ryu->is_punching && player1_ryu->is_crouching && player1_ryu->on_ground && ryu_current_frame_hi_punch_p1 == 0 && player1_ryu->on_ground && ryu_current_frame_air_punch_p1 == 0) {
                                                                        draw_lo_punch_animation(player1_ryu, FRAME_DURATION_LO_PUNCH, &ryu_time_frame_lo_punch_p1, &ryu_current_frame_lo_punch_p1, NUM_RYU_LO_PUNCH_FRAMES);
                                                                } else if (player1_ryu->is_punching && ryu_current_frame_lo_punch_p1 == 0 && player1_ryu->on_ground && ryu_current_frame_air_punch_p1 == 0) {
                                                                        draw_hi_punch_animation(player1_ryu, FRAME_DURATION_HI_PUNCH, &ryu_time_frame_hi_punch_p1, &ryu_current_frame_hi_punch_p1, NUM_RYU_HI_PUNCH_FRAMES);
                                                                } else if (player1_ryu->is_kicking && player1_ryu->on_ground) {
                                                                        draw_hi_kick_animation(player1_ryu, FRAME_DURATION_HI_KICK, &ryu_time_frame_hi_kick_p1, &ryu_current_frame_hi_kick_p1, NUM_RYU_HI_KICK_FRAMES);
                                                                } else if ((player1_ryu->is_running_right || player1_ryu->is_running_left) && player1_ryu->on_ground) {
                                                                        draw_running_animation(player1_ryu, FRAME_DURATION_RUNNING, &ryu_time_frame_running, &ryu_current_frame_running, &ryu_current_frame_idle, NUM_RYU_RUNNING_FRAMES);
                                                                } else if (player1_ryu->is_crouching && !player1_ryu->is_blocking && player1_ryu->on_ground) {
                                                                        draw_crouching_animation(player1_ryu);
                                                                } else if (player1_ryu->is_blocking && player1_ryu->on_ground) {
                                                                        draw_blocking_animation(player1_ryu);
                                                                } else if (!player1_ryu->on_ground && !(player1_ryu->is_punching || player1_ryu->is_kicking)) {
                                                                        draw_jumping_animation(player1_ryu, FRAME_DURATION_JUMP, &ryu_time_frame_jump_p1, &ryu_current_frame_jump_p1, NUM_RYU_JUMP_FRAMES);
                                                                } else {
                                                                        draw_idle_animation(player1_ryu, ryu_current_frame_idle);
                                                                }

                                                                break;
                                                }

                                                switch (game_states->rumble_fighter_p2) {
                                                        case 0:
                                                                if (player2_ryu->is_crouching && player2_ryu->is_blocking && player2_ryu->on_ground) {
                                                                        draw_lo_blocking_animation(player2_ryu);
                                                                } else if (player2_ryu->is_punching && player2_ryu->is_crouching && player2_ryu->on_ground) {
                                                                        draw_lo_punch_animation(player2_ryu, FRAME_DURATION_LO_PUNCH, &ryu_time_frame_lo_punch_p2, &ryu_current_frame_lo_punch_p2, NUM_RYU_LO_PUNCH_FRAMES);
                                                                } else if (player2_ryu->is_punching && ryu_current_frame_lo_punch_p2 == 0 && player2_ryu->on_ground) {
                                                                        draw_hi_punch_animation(player2_ryu, FRAME_DURATION_HI_PUNCH, &ryu_time_frame_hi_punch_p2, &ryu_current_frame_hi_punch_p2, NUM_RYU_HI_PUNCH_FRAMES);
                                                                } else if (player2_ryu->is_kicking && player2_ryu->on_ground) {
                                                                        draw_hi_kick_animation(player2_ryu, FRAME_DURATION_HI_KICK, &ryu_time_frame_hi_kick_p2, &ryu_current_frame_hi_kick_p2, NUM_RYU_HI_KICK_FRAMES);
                                                                } else if ((player2_ryu->is_running_right || player2_ryu->is_running_left) &&  player2_ryu->on_ground) {
                                                                        draw_running_animation(player2_ryu, FRAME_DURATION_RUNNING, &ryu_time_frame_running, &ryu_current_frame_running, &ryu_current_frame_idle, NUM_RYU_RUNNING_FRAMES);
                                                                } else if (player2_ryu->is_crouching && !player2_ryu->is_blocking && player2_ryu->on_ground) {
                                                                        draw_crouching_animation(player2_ryu);
                                                                } else if (player2_ryu->is_blocking && player2_ryu->on_ground) {
                                                                        draw_blocking_animation(player2_ryu);
                                                                } else if (!player2_ryu->on_ground) {
                                                                        draw_jumping_animation(player2_ryu, FRAME_DURATION_JUMP, &ryu_time_frame_jump_p1, &ryu_current_frame_jump_p1, NUM_RYU_JUMP_FRAMES);
                                                                } else {
                                                                        draw_idle_animation(player2_ryu, ryu_current_frame_idle);
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
                                al_play_sample(menu_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &menu_sample_id);
                        
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
                                                al_play_sample(menu_confirm_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_confirm_sample_id);

                                                game_states->menu = 0;
                                                game_states->menu_select = 0;
                                                game_states->character_select = 1;
                                        } else {
                                                al_play_sample(menu_confirm_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_confirm_sample_id);

                                                break;
                                        }
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_DELETE) {
                                        al_play_sample(cancel_sound_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);

                                        break;
                                }
                        }
                } else if (game_states->character_select) {
                        if (game_states->play_character_select_welcome_sample && game_states->play_character_select_sample) {
                                al_play_sample(character_select_welcome_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &character_select_welcome_sample_id);
                                al_play_sample(character_select_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &character_select_sample_id);
                        }

                        game_states->play_character_select_welcome_sample = 0;
                        game_states->play_character_select_sample = 0;
                        game_states->play_menu_sample = 1;
                        game_states->stage_select_nav = 0;
                        game_states->play_stage_select_sample = 1;
                        game_states->menu_select = 0;

                        switch (game_states->rumble_fighter_p1) {
                                case 0:
                                        player1_ryu->rounds_won = 0;
                                        player1_ryu->health = MAX_HEALTH;
                                        player1_ryu->stamina = MAX_STAMINA;

                                        break;
                        }

                        switch (game_states->rumble_fighter_p2) {
                                case 0:
                                        player2_ryu->rounds_won = 0;
                                        player2_ryu->health = MAX_HEALTH;
                                        player2_ryu->stamina = MAX_STAMINA;

                                        break;
                        }

                        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                                if (event.keyboard.keycode == ALLEGRO_KEY_DELETE) {
                                        game_states->menu = 1;
                                        game_states->character_select = 0;

                                        al_play_sample(cancel_sound_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);
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
                                        al_play_sample(character_select_confirm_sample, 3.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &character_confirm_sample_id);
                                        
                                        game_states->character_select_nav_p1_confirm = 1;
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
                                        al_play_sample(character_select_confirm_sample, 3.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &character_confirm_sample_id);
                                        
                                        game_states->character_select_nav_p2_confirm = 1;
                                }

                                update_fighter_selectors(game_states);
                        }

                        if (game_states->character_select_nav_p1_confirm && game_states->character_select_nav_p2_confirm) {
                                al_stop_sample(&character_select_sample_id);

                                game_states->stage_select = 1;
                                game_states->character_select = 0;
                        }
                } else if (game_states->stage_select) {
                        if (game_states->play_stage_select_sample)
                                al_play_sample(character_select_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &character_select_sample_id);
                        
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

                                        al_play_sample(cancel_sound_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);
                                        al_stop_sample(&character_select_sample_id);
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

                                        al_stop_sample(&character_select_sample_id);
                                }
                        }
                } else if (game_states->rumble) {
                        if (game_states->play_rumble_sample) {
                                switch (game_states->stage_select_nav) {
                                        case 0:
                                                al_play_sample(ryu_theme_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &ryu_theme_sample_id);

                                                break;

                                        case 1:
                                                al_play_sample(ken_theme_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &ken_theme_sample_id);

                                                break;

                                        case 2:
                                                al_play_sample(guile_theme_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &guile_theme_sample_id);

                                                break;

                                        case 3:
                                                al_play_sample(vega_theme_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &vega_theme_sample_id);

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
                                        
                                        al_play_sample(pause_sound_effect, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &pause_sound_effect_id);
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
                                        handle_pause_selection(
                                                menu_confirm_sample, menu_confirm_sample_id, 
                                                ryu_theme_sample_id, ken_theme_sample_id, 
                                                guile_theme_sample_id, vega_theme_sample_id, 
                                                player1_ryu, player2_ryu,
                                                game_states
                                        );
                                }

                                /* Botões on-press */
                                if (!game_states->rumble_pause) {
                                        /* P1 */
                                        if (event.keyboard.keycode == ALLEGRO_KEY_Z) {
                                                switch (game_states->rumble_fighter_p1) {
                                                        case 0:
                                                                player1_ryu->is_punching = 1;
                                                                ryu_current_frame_hi_punch_p1 = 0;
                                                                ryu_time_frame_hi_punch_p1 = 0;
                                                                ryu_current_frame_lo_punch_p1 = 0;
                                                                ryu_time_frame_lo_punch_p1 = 0;    
                                                                ryu_current_frame_air_punch_p1 = 0;
                                                                ryu_time_frame_air_punch_p1 = 0;

                                                                break;
                                                }  
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_X) {
                                                switch (game_states->rumble_fighter_p1) {
                                                        case 0:
                                                                player1_ryu->is_kicking = 1;
                                                                ryu_current_frame_hi_kick_p1 = 0;
                                                                ryu_time_frame_hi_kick_p1 = 0;
                                                                ryu_current_frame_lo_kick_p1 = 0;
                                                                ryu_time_frame_lo_kick_p1 = 0;
                                                                ryu_current_frame_air_kick_p1 = 0;
                                                                ryu_time_frame_air_kick_p1 = 0;

                                                                break;
                                                }
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_W && player1_ryu->on_ground) {
                                                switch (game_states->rumble_fighter_p1) {
                                                        case 0:
                                                                player1_ryu->velocity_y = JUMP_STRENGTH;
                                                                player1_ryu->on_ground = 0;
                                                                ryu_current_frame_jump_p1 = 0;
                                                                ryu_time_frame_jump_p1 = 0;

                                                                break;
                                                }
                                        }

                                        /* P2 */
                                        if (event.keyboard.keycode == ALLEGRO_KEY_K) {
                                                switch (game_states->rumble_fighter_p2) {
                                                        case 0:
                                                                player2_ryu->is_punching = 1;
                                                                ryu_current_frame_hi_punch_p2 = 0;
                                                                ryu_time_frame_hi_punch_p2 = 0;
                                                                ryu_current_frame_lo_punch_p2 = 0;
                                                                ryu_time_frame_lo_punch_p2 = 0;    
                                                                ryu_current_frame_air_punch_p2 = 0;
                                                                ryu_time_frame_air_punch_p2 = 0;

                                                                break;
                                                }   
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_L) {
                                                switch (game_states->rumble_fighter_p2) {
                                                        case 0:
                                                                player2_ryu->is_kicking = 1;
                                                                ryu_current_frame_hi_kick_p2 = 0;
                                                                ryu_time_frame_hi_kick_p2 = 0;
                                                                ryu_current_frame_lo_kick_p2 = 0;
                                                                ryu_time_frame_lo_kick_p2 = 0;
                                                                ryu_current_frame_air_kick_p2 = 0;
                                                                ryu_time_frame_air_kick_p2 = 0;

                                                                break;
                                                }
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_UP && player2_ryu->on_ground) {
                                                switch (game_states->rumble_fighter_p2) {
                                                        case 0:
                                                                player2_ryu->velocity_y = JUMP_STRENGTH;
                                                                player2_ryu->on_ground = 0;
                                                                ryu_current_frame_jump_p2 = 0;
                                                                ryu_time_frame_jump_p2 = 0;

                                                                break;
                                                }
                                        }
                                }
                        }

                        if (!game_states->rumble_pause) {
                                game_states->rumble_pause_select = 0;

                                /* Botões on-hold */
                                if (event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_UP) {
                                        if (event.keyboard.keycode == ALLEGRO_KEY_D) {
                                                move_controller_right(player1_ryu->controller);

                                                player1_ryu->is_running_right ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_A) {
                                                move_controller_left(player1_ryu->controller);

                                                player1_ryu->is_running_left ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_S) {
                                                move_controller_down(player1_ryu->controller);

                                                player1_ryu->is_crouching ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_C) {
                                                if (player1_ryu->stamina > 0) {
                                                        move_controller_block(player1_ryu->controller);

                                                        player1_ryu->is_blocking ^= 1;
                                                }
                                        }

                                        if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                                                move_controller_right(player2_ryu->controller);

                                                player2_ryu->is_running_right ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                                                move_controller_left(player2_ryu->controller);

                                                player2_ryu->is_running_left ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                                                move_controller_down(player2_ryu->controller);

                                                player2_ryu->is_crouching ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_J) {
                                                player2_ryu->is_blocking ^= 1;
                                        }
                                }
                        }
                } else if (game_states->rumble_end) {
                        switch (game_states->stage_select_nav) {
                                case 0:
                                        al_stop_sample(&ryu_theme_sample_id);

                                        break;
                                
                                case 1:
                                        al_stop_sample(&ken_theme_sample_id);

                                        break;

                                case 2:
                                        al_stop_sample(&guile_theme_sample_id);

                                        break;

                                case 3:
                                        al_stop_sample(&vega_theme_sample_id);

                                        break;
                        }

                        if (game_states->play_rumble_end_sample)
                                al_play_sample(rumble_end_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &rumble_end_sample_id);

                        game_states->play_menu_sample = 1;
                        game_states->play_rumble_end_sample = 0;

                        if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                                al_play_sample(menu_confirm_sample, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_confirm_sample_id);
                                al_stop_sample(&rumble_end_sample_id);

                                game_states->rumble_end = 0;
                                game_states->rumble = 0;
                                game_states->menu = 1;
                        }
                }
        }

        printf("\n[+] main(): exiting game...\n");
        destroy_font_garbage_array(font_garbage_array);
        destroy_bitmap_garbage_array(bitmap_garbage_array);
        destroy_sample_garbage_array(sample_garbage_array);
        destroy_fighter_sprites(player1_ryu);
        destroy_game_states(game_states);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(event_queue);
        al_uninstall_audio();
        al_uninstall_keyboard();

        return 0;
}