#include <allegro5/bitmap_draw.h>
#include <allegro5/display.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "../error_enums/main_func_flags.h"
#include "destroy_resources.h"
#include "game_states/game_states.h"
#include "draw/draw.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define NUM_MENU_OPTIONS 2
#define NUM_CHARACTERS 4
#define NUM_STAGES 2
#define NUM_PAUSE_OPTIONS 3
#define FRAMES_PER_SECOND 60.0

int main(void) {
        if (!al_init()) {
                fprintf(stderr, "[-] main(): failed to initialize Allegro\n");
                exit(AL_INIT_ERROR);
        } else {
                printf("[+] main(): initialized Allegro\n");
        }

        if (!al_install_keyboard()) {
                fprintf(stderr, "[-] main(): failed keyboard installation\n");
                exit(AL_KEYBOARD_INSTALL_ERROR);
        } else {
                printf("[+] main(): installed keyboard\n");
        }

        if (!al_init_font_addon() || !al_init_ttf_addon()) {
                fprintf(stderr, "[-] main(): failed to initialize font addons\n");
                exit(AL_INIT_FONT_ADDONS_ERROR);
        } else {
                printf("[+] main(): set font addons\n");
        }

        if (!al_init_image_addon()) {
                fprintf(stderr, "[-] main(): failed to initialize image addon\n");
                exit(AL_INIT_IMAGE_ADDON_ERROR);
        } else {
                printf("[+] main(): initialized image addon\n");
        }

        al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

        ALLEGRO_DISPLAY *display = al_create_display(WIN_WIDTH, WIN_HEIGHT);

        if (!display) {
                fprintf(stderr, "[-] main(): failed to initialize display\n");
                exit(AL_CREATE_DISPLAY_ERROR);
        } else {
                printf("[+] main(): initialized display\n");
        }

        ALLEGRO_TIMER *timer = al_create_timer(1.0 / FRAMES_PER_SECOND);

        if (!timer) {
                fprintf(stderr, "[-] main(): failed to initialize timer\n");
                exit(AL_CREATE_TIMER_ERROR);
        } else {
                printf("[+] main(): initialized timer\n");
        }

        ALLEGRO_BITMAP *window_icon = al_load_bitmap("imgs/icons/window_icon.png");

        if (!window_icon) {
                fprintf(stderr, "[-] main(): failed to load the game icon\n");
                exit(AL_LOAD_ICON_ERROR);
        } else {
                printf("[+] main(): loaded game icon\n");
        }

        al_set_display_icon(display, window_icon);

        ALLEGRO_BITMAP *viking_icon = al_load_bitmap("imgs/icons/viking_icon.png");

        if (!viking_icon) {
                fprintf(stderr, "[-] main(): failed to load viking_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        } else {
                printf("[+] main(): loaded viking_icon.png\n");
        }

        ALLEGRO_BITMAP *knight_icon = al_load_bitmap("imgs/icons/knight_icon.png");

        if (!knight_icon) {
                fprintf(stderr, "[-] main(): failed to load knight_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        } else {
                printf("[+] main(): loaded knight_icon.png\n");
        }

        ALLEGRO_BITMAP *spearwoman_icon = al_load_bitmap("imgs/icons/spearwoman_icon.png");

        if (!spearwoman_icon) {
                fprintf(stderr, "[-] main(): failed to load spearwoman_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        } else {
                printf("[+] main(): loaded spearwoman_icon.png\n");
        }

        ALLEGRO_BITMAP *fire_warrior_icon = al_load_bitmap("imgs/icons/fire_warrior_icon.png");

        if (!fire_warrior_icon) {
                fprintf(stderr, "[-] main(): failed to load fire_warrior_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        } else {
                printf("[+] main(): loaded fire_warrior_icon.png\n");
        }

        ALLEGRO_BITMAP *stage_select_arrow_icon = al_load_bitmap("imgs/icons/stage_select_arrow_icon.png");

        if (!stage_select_arrow_icon) {
                fprintf(stderr, "[-] main(): failed to load stage_select_arrow_icon.png\n");
                exit(AL_LOAD_ICON_ERROR);
        } else {
                printf("[+] main(): loaded stage_select_arrow_icon.png\n");
        }
        
        ALLEGRO_BITMAP *stage_dark_forest = al_load_bitmap("imgs/stages/stage_dark_forest.png");

        if (!stage_dark_forest) {
                fprintf(stderr, "[-] main(): failed to load stage -> dark forest\n");
                exit(AL_LOAD_STAGE_ERROR);
        } else {
                printf("[+] main(): loaded stage -> dark forest\n");
        }

        ALLEGRO_BITMAP *stage_abandoned_factory = al_load_bitmap("imgs/stages/stage_abandoned_factory.png");

        if (!stage_abandoned_factory) {
                fprintf(stderr, "[-] main(): failed to load stage -> abandoned factory\n");
                exit(AL_LOAD_STAGE_ERROR);
        } else {
                printf("[+] main(): loaded stage -> abandoned factory\n");
        }

        ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

        if (!event_queue) {
                fprintf(stderr, "[-] main(): failed to initialize event queue\n");
                exit(AL_CREATE_EVENT_QUEUE_ERROR);
        } else {
                printf("[+] main(): initialized event queue\n");
        }

        ALLEGRO_FONT *menu_header_font = al_load_font("fonts/Osake.ttf", 256, 0);

        if (!menu_header_font) {
                fprintf(stderr, "[-] main(): failed to load menu_header_font\n");
                exit(AL_LOAD_FONT_ERROR);
        } else {
                printf("[+] main(): loaded menu_header_font\n");
        }

        ALLEGRO_FONT *menu_options_font = al_load_font("fonts/osaka-re.ttf", 64, 0);

        if (!menu_options_font) {
                fprintf(stderr, "[-] main(): failed to load menu_options_font\n");
                exit(AL_LOAD_FONT_ERROR);
        } else {
                printf("[+] main(): loaded menu_options_font\n");
        }

        ALLEGRO_FONT *character_select_header_font = al_load_font("fonts/Osake.ttf", 64, 0);

        if (!character_select_header_font) {
                fprintf(stderr, "[-] main(): failed to load character_select_header_font\n");
                exit(AL_LOAD_FONT_ERROR);
        } else {
                printf("[+] main(): loaded character_select_header_font\n");
        }

        ALLEGRO_FONT *character_select_display_name_font = al_load_font("fonts/OsakaBrightDemoRegular.ttf", 32, 0);

        if (!character_select_display_name_font) {
                fprintf(stderr, "[-] main(): failed to load character_select_display_name_font\n");
                exit(AL_LOAD_FONT_ERROR);
        } else {
                printf("[+] main(): loaded character_select_display_name_font\n");
        }

        ALLEGRO_FONT *stage_display_name_font = al_load_font("fonts/osaka-re.ttf", 32, 0);

        if (!stage_display_name_font) {
                fprintf(stderr, "[-] main(): failed to load stage_display_name_font\n");
                exit(AL_LOAD_FONT_ERROR);
        } else {
                printf("[+] main(): loaded stage_display_name_font\n");
        }

        if (!al_install_audio() || !al_init_acodec_addon() || !al_reserve_samples(10)) {
                fprintf(stderr, "[-] main(): failed to set audio\n");
                exit(AL_SET_AUDIO_ERROR);
        } else {
                printf("[+] main(): set audio\n");
        }

        ALLEGRO_SAMPLE_ID menu_sample_id;
        ALLEGRO_SAMPLE *menu_sample = al_load_sample("music/DavidKBD - See You in Hell Pack - 02 - The Eternal Fight.ogg");

        if (!menu_sample) {
                fprintf(stderr, "[-] main(): failed to load menu music\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded menu music\n");
        }

        ALLEGRO_SAMPLE_ID menu_select_sample_id;
        ALLEGRO_SAMPLE *menu_select_sample = al_load_sample("sfx/menu_select_option.ogg");

        if (!menu_select_sample) {
                fprintf(stderr, "[-] main(): failed to load menu_select_sample.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded menu_select_sample.ogg\n");
        }

        ALLEGRO_SAMPLE_ID menu_confirm_sample_id;
        ALLEGRO_SAMPLE *menu_confirm_sample = al_load_sample("sfx/menu_confirm_option.ogg");

        if (!menu_confirm_sample) {
                fprintf(stderr, "[-] main(): failed to load menu_confirm_sample.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded menu_confirm_sample.ogg\n");
        }

        ALLEGRO_SAMPLE_ID character_select_sample_id;
        ALLEGRO_SAMPLE *character_select_sample = al_load_sample("music/DavidKBD - See You in Hell Pack - 13 - Without Me.ogg");

        if (!character_select_sample) {
                fprintf(stderr, "[-] main(): failed to load character selection screen music\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded character selection screen music\n");
        }

        if (!character_select_sample) {
                fprintf(stderr, "[-] main(): failed to load character select screen music\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded character select screen music\n");
        }

        ALLEGRO_SAMPLE_ID character_select_welcome_sample_id;
        ALLEGRO_SAMPLE *character_select_welcome_sample = al_load_sample("sfx/choose_your_character.ogg");

        if (!character_select_welcome_sample) {
                fprintf(stderr, "[-] main(): failed to load choose_your_character.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded choose_your_character.ogg\n");
        }

        ALLEGRO_SAMPLE_ID cancel_sound_sample_id;
        ALLEGRO_SAMPLE *cancel_sound_sample = al_load_sample("sfx/cancel.ogg");

        if (!cancel_sound_sample) {
                fprintf(stderr, "[-] main(): failed to load cancel.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded cancel.ogg\n");
        }

        ALLEGRO_SAMPLE_ID character_confirm_sample_id;
        ALLEGRO_SAMPLE *character_select_confirm_sample = al_load_sample("sfx/character_confirm.ogg");

        if (!character_select_confirm_sample) {
                fprintf(stderr, "[-] main(): failed to load character_confirm.ogg\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded character_confirm.ogg\n");
        }

        ALLEGRO_SAMPLE_ID stage_select_sample_id;
        ALLEGRO_SAMPLE *stage_select_sample = al_load_sample("music/DavidKBD - See You in Hell Pack - 15 - Fear.ogg");

        if (!stage_select_sample) {
                fprintf(stderr, "[-] main(): failed to load stage select music\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded stage select music\n");
        }

        ALLEGRO_SAMPLE_ID pause_sound_effect_id;
        ALLEGRO_SAMPLE *pause_sound_effect = al_load_sample("sfx/pause.ogg");

        if (!pause_sound_effect) {
                fprintf(stderr, "[-] main(): failed to load pause sound effect\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded pause sound effect\n");
        }

        ALLEGRO_SAMPLE_ID dark_forest_sample_id;
        ALLEGRO_SAMPLE *dark_forest_sample = al_load_sample("music/dark_forest_soundtrack.ogg");

        if (!dark_forest_sample) {
                fprintf(stderr, "[-] main(): failed to load stage -> dark forest soundtrack\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded stage -> dark forest soundtrack\n");
        }

        ALLEGRO_SAMPLE_ID abandoned_factory_sample_id;
        ALLEGRO_SAMPLE *abandoned_factory_sample = al_load_sample("music/abandoned_factory_soundtrack.ogg");

        if (!abandoned_factory_sample) {
                fprintf(stderr, "[-] main(): loaded stage -> abandoned factory soundtrack\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded stage -> abandoned factory soundtrack\n");
        }

        ALLEGRO_BITMAP *viking_idle_spritesheet = al_load_bitmap("imgs/sprites/Viking/viking_idle.png");

        if (!viking_idle_spritesheet) {
                fprintf(stderr, "[-] main(): failed to load the viking's idle animation spritesheet\n");
                exit(AL_LOAD_SPRITE_ERROR);
        } else {
                printf("[+] main(): loaded the viking's idle animation spritesheet\n");
        }
        
        ALLEGRO_EVENT event;

        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_timer_event_source(timer));
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_start_timer(timer);
        al_set_window_title(display, "C-Rumble");

        GameStates *game_states = create_game_states(); // estrutura com as flags relativas aos diversos estados do jogo

        if (!game_states) {
                fprintf(stderr, "[-] main(): failed to create game states structure\n");
                exit(CREATE_GAME_STATES_ERROR);
        } else {
                printf("[+] main(): loaded game states structure\n");
        }

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
                                if (game_states->rumble_pause == 0) {
                                        switch (game_states->stage_select_nav) {
                                                case 0:
                                                        al_draw_scaled_bitmap(stage_dark_forest, 0.0, 0.0, al_get_bitmap_width(stage_dark_forest), al_get_bitmap_height(stage_dark_forest), 0.0, 0.0, al_get_display_width(display), al_get_display_height(display), 0);

                                                        break;

                                                case 1:
                                                        al_draw_scaled_bitmap(stage_abandoned_factory, 0.0, 0.0, al_get_bitmap_width(stage_abandoned_factory), al_get_bitmap_height(stage_abandoned_factory), 0.0, 0.0, al_get_display_width(display), al_get_display_height(display), 0);

                                                        break;
                                        }

                                        if (game_states->rumble_fighter_p1 == 0) {
                                                al_draw_scaled_bitmap(viking_idle_spritesheet, 0.0, 0.0, 47, 66, 32, (float)al_get_display_height(display) - 182, 237, 256, 0);
                                        }

                                        if (game_states->rumble_fighter_p2 == 0) {
                                                al_draw_scaled_bitmap(viking_idle_spritesheet, 0.0, 0.0, 47, 66, al_get_display_width(display) - 256, (float)al_get_display_height(display) - 182, 237, 256, ALLEGRO_FLIP_HORIZONTAL);
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
                                        game_states->menu_select++;
                                
                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->menu_select > NUM_MENU_OPTIONS - 1)
                                                game_states->menu_select = 0;
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_W || event.keyboard.keycode == ALLEGRO_KEY_UP) {
                                        game_states->menu_select--;

                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->menu_select < 0)
                                                game_states->menu_select = NUM_MENU_OPTIONS - 1;
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                                        if (game_states->menu_select == 0) {
                                                al_stop_sample(&menu_sample_id);
                                                al_play_sample(menu_confirm_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_confirm_sample_id);

                                                game_states->menu = 0;
                                                game_states->menu_select = 0;
                                                game_states->character_select = 1;
                                        } else {
                                                al_play_sample(menu_confirm_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_confirm_sample_id);
                                                al_rest(0.5);

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

                        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                                if (event.keyboard.keycode == ALLEGRO_KEY_DELETE) {
                                        game_states->menu = 1;
                                        game_states->character_select = 0;

                                        al_play_sample(cancel_sound_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);
                                        al_stop_sample(&character_select_sample_id);
                                }
                                
                                if (event.keyboard.keycode == ALLEGRO_KEY_D && !game_states->character_select_nav_p1_confirm) {
                                        game_states->character_select_nav_p1++;
                                
                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->character_select_nav_p1 > NUM_CHARACTERS - 1)
                                                game_states->character_select_nav_p1 = 0;
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_A && !game_states->character_select_nav_p1_confirm) {
                                        game_states->character_select_nav_p1--;

                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->character_select_nav_p1 < 0)
                                                game_states->character_select_nav_p1 = NUM_CHARACTERS - 1;
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && !game_states->character_select_nav_p1_confirm) {
                                        game_states->character_select_nav_p1_confirm = 1;

                                        al_play_sample(character_select_confirm_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &character_confirm_sample_id);

                                        switch (game_states->character_select_nav_p1) {
                                                case 0:
                                                        printf("\nP1 SELECTED VIKING\n");
                                                        game_states->rumble_fighter_p1 = 0;

                                                        break;

                                                case 1:
                                                        printf("\nP1 SELECTED KNIGHT\n");
                                                        game_states->rumble_fighter_p1 = 1;

                                                        break;

                                                case 2:
                                                        printf("\nP1 SELECTED SPEARWOMAN\n");
                                                        game_states->rumble_fighter_p1 = 2;

                                                        break;

                                                case 3:
                                                        printf("\nP1 SELECTED FIRE WARRIOR\n");
                                                        game_states->rumble_fighter_p1 = 3;

                                                        break;
                                        }
                                }

                                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && !game_states->character_select_nav_p2_confirm) {
                                        game_states->character_select_nav_p2++;
                                
                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->character_select_nav_p2 > NUM_CHARACTERS - 1)
                                                game_states->character_select_nav_p2 = 0;
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && !game_states->character_select_nav_p2_confirm) {
                                        game_states->character_select_nav_p2--;

                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->character_select_nav_p2 < 0)
                                                game_states->character_select_nav_p2 = NUM_CHARACTERS - 1;
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && !game_states->character_select_nav_p2_confirm) {
                                        game_states->character_select_nav_p2_confirm = 1;

                                        al_play_sample(character_select_confirm_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &character_confirm_sample_id);

                                        switch (game_states->character_select_nav_p2) {
                                                case 0:
                                                        printf("\nP2 SELECTED VIKING\n");
                                                        game_states->rumble_fighter_p2 = 0;

                                                        break;

                                                case 1:
                                                        printf("\nP2 SELECTED KNIGHT\n");
                                                        game_states->rumble_fighter_p2 = 1;

                                                        break;

                                                case 2:
                                                        printf("\nP2 SELECTED SPEARWOMAN\n");
                                                        game_states->rumble_fighter_p2 = 2;

                                                        break;

                                                case 3:
                                                        printf("\nP2 SELECTED FIRE WARRIOR\n");
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
                                        game_states->stage_select_nav++;

                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->stage_select_nav > NUM_STAGES - 1)
                                                game_states->stage_select_nav = 0;
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_A || event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                                        game_states->stage_select_nav--;

                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->stage_select_nav < 0)
                                                game_states->stage_select_nav = NUM_STAGES - 1;
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER || event.keyboard.keycode == ALLEGRO_KEY_DELETE) {
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
                                                game_states->rumble_pause_select++;

                                                al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                                if (game_states->rumble_pause_select > NUM_PAUSE_OPTIONS - 1)
                                                        game_states->rumble_pause_select = 0;
                                        } else {

                                        }
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_W) {
                                        if (game_states->rumble_pause) {
                                                game_states->rumble_pause_select--;

                                                al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                                if (game_states->rumble_pause_select < 0)
                                                        game_states->rumble_pause_select = NUM_PAUSE_OPTIONS - 1;
                                        } else {

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
                                }
                        }
                }
        }

        printf("\n[+] main(): exiting game...\n");
        destroy_game_states(game_states);
        destroy_fonts(menu_header_font, menu_options_font, character_select_header_font, character_select_display_name_font);
        destroy_samples(menu_sample, menu_confirm_sample, menu_select_sample, cancel_sound_sample, character_select_welcome_sample, character_select_sample, character_select_confirm_sample, pause_sound_effect, dark_forest_sample, abandoned_factory_sample);
        destroy_bitmaps(window_icon, viking_icon, knight_icon, spearwoman_icon, fire_warrior_icon, stage_select_arrow_icon, stage_dark_forest, stage_abandoned_factory, viking_idle_spritesheet);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(event_queue);
        al_uninstall_audio();
        al_uninstall_keyboard();

        return 0;
}