#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
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
#include "selector/selector.h"
#include "destroy_resources/destroy_resources.h"

/* As macros de frames valem PARA O VIKING APENAS, definir um valor para cada sprite de CADA personagem */
#define WIN_WIDTH 1028
#define WIN_HEIGHT 720
#define NUM_MENU_OPTIONS 2
#define NUM_CHARACTERS 4
#define NUM_STAGES 2
#define NUM_PAUSE_OPTIONS 3
#define FRAMES_PER_SECOND 60.0
#define FRAME_DURATION_IDLE 0.09
#define FRAME_DURATION_PUNCH 0.06666
#define FRAME_DURATION_KICK 0.04444
#define NUM_IDLE_FRAMES 8
#define NUM_DAMAGE_FRAMES 3
#define NUM_DEATH_FRAMES 11
#define NUM_SPECIAL_FRAMES 10
#define NUM_KICK_FRAMES 7
#define NUM_HI_PUNCH_FRAMES 4
#define NUM_LO_PUNCH_FRAMES 5
#define NUM_CROUCH_FRAMES 2
#define MAXLEN_SPRITE_PATH 65

int main(void) {
        al_init();
        al_install_keyboard();
        al_init_font_addon();
        al_init_ttf_addon();
        al_init_primitives_addon();
        al_init_image_addon();
        al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

        ALLEGRO_DISPLAY *display = al_create_display(WIN_WIDTH, WIN_HEIGHT);

        al_hide_mouse_cursor(display);

        ALLEGRO_TIMER *timer = al_create_timer(1.0 / FRAMES_PER_SECOND);
        ALLEGRO_BITMAP *window_icon = al_load_bitmap("imgs/icons/window_icon.png");

        if (!window_icon) {
                fprintf(stderr, "[-] main(): failed to load the game icon\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        al_set_display_icon(display, window_icon);

        ALLEGRO_BITMAP *viking_icon = al_load_bitmap("imgs/icons/viking_icon.png");

        if (!viking_icon) {
                fprintf(stderr, "[-] main(): failed to load viking_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        ALLEGRO_BITMAP *knight_icon = al_load_bitmap("imgs/icons/knight_icon.png");

        if (!knight_icon) {
                fprintf(stderr, "[-] main(): failed to load knight_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        ALLEGRO_BITMAP *spearwoman_icon = al_load_bitmap("imgs/icons/spearwoman_icon.png");

        if (!spearwoman_icon) {
                fprintf(stderr, "[-] main(): failed to load spearwoman_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        ALLEGRO_BITMAP *fire_warrior_icon = al_load_bitmap("imgs/icons/fire_warrior_icon.png");

        if (!fire_warrior_icon) {
                fprintf(stderr, "[-] main(): failed to load fire_warrior_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }

        ALLEGRO_BITMAP *stage_select_arrow_icon = al_load_bitmap("imgs/icons/stage_select_arrow_icon.png");

        if (!stage_select_arrow_icon) {
                fprintf(stderr, "[-] main(): failed to load stage_select_arrow_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        }
        
        ALLEGRO_BITMAP *stage_dark_forest = al_load_bitmap("imgs/stages/stage_dark_forest.png");

        if (!stage_dark_forest) {
                fprintf(stderr, "[-] main(): failed to load stage -> dark forest\n");
                exit(AL_LOAD_STAGE_ERROR);
        }

        ALLEGRO_BITMAP *stage_abandoned_factory = al_load_bitmap("imgs/stages/stage_abandoned_factory.png");

        if (!stage_abandoned_factory) {
                fprintf(stderr, "[-] main(): failed to load stage -> abandoned factory\n");
                exit(AL_LOAD_STAGE_ERROR);
        }

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
                fprintf(stderr, "[-] main(): failed to load character selection screen music\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

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
                fprintf(stderr, "[-] main(): failed to load stage -> dark forest soundtrack\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        }

        ALLEGRO_SAMPLE_ID abandoned_factory_sample_id;
        ALLEGRO_SAMPLE *abandoned_factory_sample = al_load_sample("music/abandoned_factory_soundtrack.ogg");

        if (!abandoned_factory_sample) {
                fprintf(stderr, "[-] main(): loaded stage -> abandoned factory soundtrack\n");
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
        ALLEGRO_BITMAP **viking_idle_spriteset = load_spriteset(NUM_IDLE_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_idle/viking_idle", MAXLEN_SPRITE_PATH);

        if (!viking_idle_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's idle sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_running_spriteset = load_spriteset(NUM_IDLE_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_running/viking_running", MAXLEN_SPRITE_PATH);

        if (!viking_running_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's running sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_damage_spriteset = load_spriteset(NUM_DAMAGE_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_damage/viking_damage", MAXLEN_SPRITE_PATH);

        if (!viking_damage_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's damage sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_death_spriteset = load_spriteset(NUM_DEATH_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_death/viking_death", MAXLEN_SPRITE_PATH);

        if (!viking_death_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's death sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_kick_spriteset = load_spriteset(NUM_KICK_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_kick/viking_kick", MAXLEN_SPRITE_PATH);

        if (!viking_kick_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's kick sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_special_spriteset = load_spriteset(NUM_SPECIAL_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_special/viking_special", MAXLEN_SPRITE_PATH);

        if (!viking_special_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's special sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_block_spriteset = load_spriteset(NUM_IDLE_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_block/viking_block", MAXLEN_SPRITE_PATH);

        if (!viking_block_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's block spriteset\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_hi_punch_spriteset = load_spriteset(NUM_HI_PUNCH_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_hi_punch/viking_hi_punch", MAXLEN_SPRITE_PATH);

        if (!viking_hi_punch_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's hi punch sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_lo_punch_spriteset = load_spriteset(NUM_LO_PUNCH_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_lo_punch/viking_lo_punch", MAXLEN_SPRITE_PATH);

        if (!viking_lo_punch_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's lo punch sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        ALLEGRO_BITMAP **viking_crouch_spriteset = load_spriteset(NUM_CROUCH_FRAMES, sprite_path_buf, "imgs/sprites/Viking/viking_crouch/viking_crouch", MAXLEN_SPRITE_PATH);

        if (!viking_crouch_spriteset) {
                fprintf(stderr, "[-] main(): failed to load the viking's crouch sprite set\n");
                exit(AL_LOAD_SPRITE_ERROR);
        }

        float player1_x = 94.5;
        float player2_x = al_get_display_width(display) - 94.5;
        float time_frame = 0.0;
        unsigned int current_frame = 0;

        Fighter *player1_viking = create_fighter(
                189.0, 256.0, 
                player1_x, (float)al_get_display_height(display) - 256.0, 
                al_get_display_width(display), al_get_display_height(display), 
                viking_idle_spriteset, viking_hi_punch_spriteset, 
                viking_lo_punch_spriteset, viking_kick_spriteset, 
                viking_damage_spriteset, viking_death_spriteset, 
                viking_block_spriteset, viking_special_spriteset, 
                viking_running_spriteset, viking_crouch_spriteset,
                0
        );

        if (!player1_viking) {
                fprintf(stderr, "[-] main(): failed to load player 1\n");
                exit(INVALID_FIGHTER_ERROR);
        }

        Fighter *player2_viking = create_fighter(
                189.0, 256.0, 
                player2_x, (float)al_get_display_height(display) - 256.0, 
                al_get_display_width(display), al_get_display_height(display), 
                viking_idle_spriteset, viking_hi_punch_spriteset, 
                viking_lo_punch_spriteset, viking_kick_spriteset, 
                viking_damage_spriteset, viking_death_spriteset, 
                viking_block_spriteset, viking_special_spriteset, 
                viking_running_spriteset, viking_crouch_spriteset,
                1
        );

        printf("\n[+] main(): success, starting game...\n");

        while (1) {
                al_wait_for_event(event_queue, &event);

                if (event.type == ALLEGRO_EVENT_TIMER) {
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
                        } else if (game_states->stage_select) {
                                draw_stage_select(character_select_header_font, stage_display_name_font, display, stage_select_arrow_icon, game_states);
                        } else if (game_states->rumble) {
                                time_frame += 1.0 / FRAMES_PER_SECOND;

                                if (time_frame >= FRAME_DURATION_IDLE) {
                                        time_frame = 0.0;
                                        current_frame = (current_frame + 1) % NUM_IDLE_FRAMES;
                                }

                                if (game_states->rumble_pause == 0) {
                                        draw_stage(display, stage_dark_forest, stage_abandoned_factory, game_states);
                                        al_draw_rectangle(
                                                player1_viking->hitbox->hitbox_x - player1_viking->hitbox->hitbox_width / 2, (player1_viking->hitbox->hitbox_y - player1_viking->hitbox->hitbox_height / 2) + ((float)al_get_bitmap_height(viking_idle_spriteset[current_frame])) / 2,
                                                player1_viking->hitbox->hitbox_x + player1_viking->hitbox->hitbox_width / 2, (player1_viking->hitbox->hitbox_y + player1_viking->hitbox->hitbox_height / 2) + (float)al_get_display_height(display) - 256.0,
                                                al_map_rgb(255, 0, 0), 2.0
                                        );
                                        al_draw_rectangle(
                                                player2_viking->hitbox->hitbox_x - player2_viking->hitbox->hitbox_width / 2, (player2_viking->hitbox->hitbox_y - player2_viking->hitbox->hitbox_height / 2) + ((float)al_get_bitmap_height(viking_idle_spriteset[current_frame])) / 2,
                                                player2_viking->hitbox->hitbox_x + player2_viking->hitbox->hitbox_width / 2, (player2_viking->hitbox->hitbox_y + player2_viking->hitbox->hitbox_height / 2) + (float)al_get_display_height(display) - 256.0,
                                                al_map_rgb(255, 0, 0), 2.0
                                        );
                                        update_fighter_pos(player1_viking, player2_viking, al_get_display_width(display), al_get_display_height(display));

                                        if (player1_viking->is_running_right) {
                                                if (time_frame >= FRAME_DURATION_IDLE) {
                                                        time_frame = 0;
                                                        current_frame = (current_frame + 1) % NUM_IDLE_FRAMES;
                                                }

                                                if (!player1_viking->is_running_left)
                                                        al_draw_bitmap(
                                                                viking_running_spriteset[current_frame], player1_viking->hitbox->hitbox_x - (float)al_get_bitmap_width(viking_running_spriteset[current_frame]) / 2, 
                                                                player1_viking->hitbox->hitbox_y, 0
                                                        );
                                                else if (player1_viking->is_running_left)
                                                        al_draw_bitmap(
                                                                viking_idle_spriteset[current_frame], player1_viking->hitbox->hitbox_x - (float)al_get_bitmap_width(viking_idle_spriteset[current_frame]) / 2, 
                                                                player1_viking->hitbox->hitbox_y, 0
                                                        );
                                        } else if (player1_viking->is_running_left) {
                                                if (time_frame >= FRAME_DURATION_IDLE) {
                                                        time_frame = 0;
                                                        current_frame = (current_frame + 1) % NUM_IDLE_FRAMES;
                                                }

                                                if (!player1_viking->is_running_right)
                                                        al_draw_bitmap(
                                                                viking_running_spriteset[current_frame], player1_viking->hitbox->hitbox_x - (float)al_get_bitmap_width(viking_running_spriteset[current_frame]) / 2, 
                                                                player1_viking->hitbox->hitbox_y, ALLEGRO_FLIP_HORIZONTAL
                                                        );
                                                else if (player1_viking->is_running_right)
                                                        al_draw_bitmap(
                                                                viking_idle_spriteset[current_frame], player1_viking->hitbox->hitbox_x - (float)al_get_bitmap_width(viking_idle_spriteset[current_frame]) / 2, 
                                                                player1_viking->hitbox->hitbox_y, 0
                                                        );   
                                        } else if (player1_viking->is_punching) {
                                                if (time_frame >= FRAME_DURATION_PUNCH) {
                                                        time_frame = 0;
                                                        current_frame = (current_frame + 1) % NUM_HI_PUNCH_FRAMES;

                                                        if (current_frame == 0)
                                                                player1_viking->is_punching = 0;
                                                }

                                                al_draw_bitmap(
                                                        viking_hi_punch_spriteset[current_frame], player1_viking->hitbox->hitbox_x - (float)al_get_bitmap_width(viking_hi_punch_spriteset[current_frame]) / 2 + 64,
                                                        player1_viking->hitbox->hitbox_y, 0
                                                );
                                        } else if (player1_viking->is_blocking) {
                                                if (time_frame >= FRAME_DURATION_IDLE) {
                                                        time_frame = 0;
                                                        current_frame = (current_frame + 1) % NUM_IDLE_FRAMES;
                                                }

                                                al_draw_bitmap(
                                                        viking_block_spriteset[current_frame], player1_viking->hitbox->hitbox_x - (float)al_get_bitmap_width(viking_block_spriteset[current_frame]) / 2, 
                                                        player1_viking->hitbox->hitbox_y, 0
                                                );
                                        } else if (player1_viking->is_kicking) {
                                                if (time_frame >= FRAME_DURATION_KICK) {
                                                        time_frame = 0;
                                                        current_frame = (current_frame + 1) % NUM_KICK_FRAMES;

                                                        if (current_frame == 0)
                                                                player1_viking->is_kicking = 0;
                                                }

                                                al_draw_bitmap(
                                                        viking_kick_spriteset[current_frame], player1_viking->hitbox->hitbox_x - (float)al_get_bitmap_width(viking_kick_spriteset[current_frame]) / 2,
                                                        player1_viking->hitbox->hitbox_y, 0
                                                );
                                        } else {
                                                if (time_frame >= FRAME_DURATION_IDLE) {
                                                        time_frame = 0;
                                                        current_frame = (current_frame + 1) % NUM_IDLE_FRAMES;
                                                }

                                                al_draw_bitmap(
                                                        viking_idle_spriteset[current_frame], player1_viking->hitbox->hitbox_x - (float)al_get_bitmap_width(viking_idle_spriteset[current_frame]) / 2, 
                                                        player1_viking->hitbox->hitbox_y, 0
                                                );
                                        }
                                } else if (game_states->rumble_pause == 1) {
                                        draw_pause(menu_header_font, menu_options_font, display, game_states);
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
                        player1_viking->hitbox->hitbox_x = 94.5;
                        player2_viking->hitbox->hitbox_x = (float)al_get_display_width(display) - 94.5;

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
                                        game_states->character_select_nav_p2_confirm = 1;

                                        al_play_sample(character_select_confirm_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &character_confirm_sample_id);

                                        switch (game_states->character_select_nav_p2) {
                                                case 0:
                                                        game_states->rumble_fighter_p2 = 0;

                                                        break;

                                                case 1:
                                                        game_states->rumble_fighter_p2 = 1;

                                                        break;

                                                case 2:
                                                        game_states->rumble_fighter_p2 = 2;

                                                        break;

                                                case 3:
                                                        game_states->rumble_fighter_p2 = 3;

                                                        break;
                                        }
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
                                        if (game_states->rumble_pause) {
                                                al_play_sample(menu_confirm_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_confirm_sample_id);

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
                                                                        al_stop_sample(&dark_forest_sample_id);

                                                                        break;

                                                                case 1:
                                                                        al_stop_sample(&abandoned_factory_sample_id);

                                                                        break;
                                                        } 
                                                }
                                        }
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_Z) {
                                        player1_viking->is_punching = 1;
                                        player1_viking->is_kicking = 0;
                                        player1_viking->is_blocking = 0;
                                        current_frame = 0;
                                        time_frame = 0;
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_X) {
                                        player1_viking->is_kicking = 1;
                                        player1_viking->is_punching = 0;
                                        player1_viking->is_blocking = 0;
                                        current_frame = 0;
                                        time_frame = 0;
                                }
                        }

                        if (!game_states->rumble_pause) {
                                game_states->rumble_pause_select = 0;

                                if (event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_UP) {
                                        if (event.keyboard.keycode == ALLEGRO_KEY_D) {
                                                move_controller_right(player1_viking->controller);

                                                player1_viking->is_running_right ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_A) {
                                                move_controller_left(player1_viking->controller);

                                                player1_viking->is_running_left ^= 1;
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_S) {
                                                move_controller_down(player1_viking->controller);
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_C) {
                                                move_controller_block(player1_viking->controller);

                                                player1_viking->is_blocking ^= 1;
                                        }

                                        if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                                                move_controller_right(player2_viking->controller);
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                                                move_controller_left(player2_viking->controller);
                                        } else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                                                move_controller_down(player2_viking->controller);
                                        }
                                }
                        }
                }
        }

        printf("\n[+] main(): exiting game...\n");
        destroy_game_states(game_states);
        destroy_fonts(menu_header_font, menu_options_font, character_select_header_font, character_select_display_name_font);
        destroy_samples(
                menu_sample, menu_confirm_sample, 
                menu_select_sample, cancel_sound_sample, 
                character_select_welcome_sample, character_select_sample, 
                character_select_confirm_sample, pause_sound_effect, 
                dark_forest_sample, abandoned_factory_sample
        );
        destroy_bitmaps(
                window_icon, viking_icon, 
                knight_icon, spearwoman_icon, 
                fire_warrior_icon, stage_select_arrow_icon, 
                stage_dark_forest, stage_abandoned_factory
        );
        destroy_spriteset(viking_idle_spriteset, NUM_IDLE_FRAMES);
        destroy_spriteset(viking_running_spriteset, NUM_IDLE_FRAMES);
        destroy_spriteset(viking_special_spriteset, NUM_DEATH_FRAMES);
        destroy_spriteset(viking_block_spriteset, NUM_IDLE_FRAMES);
        destroy_spriteset(viking_hi_punch_spriteset, NUM_HI_PUNCH_FRAMES);
        destroy_spriteset(viking_lo_punch_spriteset, NUM_LO_PUNCH_FRAMES);
        destroy_spriteset(viking_crouch_spriteset, NUM_CROUCH_FRAMES);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(event_queue);
        al_uninstall_audio();
        al_uninstall_keyboard();

        return 0;
}