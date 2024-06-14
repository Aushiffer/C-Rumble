#include <allegro5/keycodes.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "../error_enums/main_func_flags.h"
#include "game_states/game_states.h"
#include "draw/draw.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MENU_OPTIONS 2
#define NUM_CHARACTERS 4

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

        al_init_image_addon();
        al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

        ALLEGRO_DISPLAY *display = al_create_display(WIN_WIDTH, WIN_HEIGHT);

        if (!display) {
                fprintf(stderr, "[-] main(): failed to initialize display\n");
                exit(AL_CREATE_DISPLAY_ERROR);
        } else {
                printf("[+] main(): initialized display\n");
        }

        ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);

        if (!timer) {
                fprintf(stderr, "[-] main(): failed to initialize timer\n");
                exit(AL_CREATE_TIMER_ERROR);
        } else {
                printf("[+] main(): initialized timer\n");
        }

        ALLEGRO_BITMAP *game_icon = al_load_bitmap("imgs/icons/game_icon.png");

        if (!game_icon) {
                fprintf(stderr, "[-] main(): failed to load the game icon\n");
                exit(AL_LOAD_GAME_ICON_ERROR);
        } else {
                printf("[+] main(): loaded game icon\n");
        }

        al_set_display_icon(display, game_icon);

        ALLEGRO_BITMAP *viking_icon = al_load_bitmap("imgs/icons/viking_icon.png");

        if (!viking_icon) {
                fprintf(stderr, "[-] main(): failed to load viking_icon.png\n");
                exit(AL_LOAD_GAME_ICON_ERROR);
        } else {
                printf("[+] main(): loaded viking_icon.png\n");
        }

        ALLEGRO_BITMAP *knight_icon = al_load_bitmap("imgs/icons/knight_icon.png");

        if (!knight_icon) {
                fprintf(stderr, "[-] main(): failed to load knight_icon.png\n");
                exit(AL_LOAD_GAME_ICON_ERROR);
        } else {
                printf("[+] main(): loaded knight_icon.png\n");
        }

        ALLEGRO_BITMAP *spearwoman_icon = al_load_bitmap("imgs/icons/spearwoman_icon.png");

        if (!spearwoman_icon) {
                fprintf(stderr, "[-] main(): failed to load spearwoman_icon.png\n");
                exit(AL_LOAD_GAME_ICON_ERROR);
        } else {
                printf("[+] main(): loaded spearwoman_icon.png\n");
        }

        ALLEGRO_BITMAP *fire_warrior_icon = al_load_bitmap("imgs/icons/fire_warrior_icon.png");

        if (!fire_warrior_icon) {
                fprintf(stderr, "[-] main(): failed to load fire_warrior_icon.png\n");
                exit(AL_LOAD_GAME_ICON_ERROR);
        } else {
                printf("[+] main(): loaded fire_warrior_icon.png\n");
        }

        ALLEGRO_EVENT_QUEUE *evt_queue = al_create_event_queue();

        if (!evt_queue) {
                fprintf(stderr, "[-] main(): failed to initialize event queue\n");
                exit(AL_CREATE_EVENT_QUEUE_ERROR);
        } else {
                printf("[+] main(): initialized event queue\n");
        }

        ALLEGRO_FONT *menu_header_font = al_load_font("fonts/Osake.ttf", 256, 0);

        if (!menu_header_font) {
                fprintf(stderr, "[-] main(): failed to load Osake.ttf (menu) font\n");
                exit(AL_LOAD_FONT_ERROR);
        } else {
                printf("[+] main(): loaded Osake.ttf (menu) font\n");
        }

        ALLEGRO_FONT *menu_options_font = al_load_font("fonts/osaka-re.ttf", 64, 0);

        if (!menu_options_font) {
                fprintf(stderr, "[-] main(): failed to load osaka-re.ttf font\n");
                exit(AL_LOAD_FONT_ERROR);
        } else {
                printf("[+] main(): loaded osaka-re.ttf font\n");
        }

        ALLEGRO_FONT *character_select_header_font = al_load_font("fonts/Osake.ttf", 64, 0);

        if (!character_select_header_font) {
                fprintf(stderr, "[-] main(): failed to load Osake.ttf (character selection) font\n");
                exit(AL_LOAD_FONT_ERROR);
        } else {
                printf("[+] main(): loaded Osake.ttf (character selection) font\n");
        }

        ALLEGRO_FONT *character_select_display_name_font = al_load_font("fonts/OsakaBrightDemoRegular.ttf", 32, 0);

        if (!character_select_display_name_font) {
                fprintf(stderr, "[-] main(): failed to load OsakaBrightDemoRegular.ttf\n");
                exit(AL_LOAD_FONT_ERROR);
        } else {
                printf("[+] main(): loaded OsakaBrightDemoRegular.ttf font\n");
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

        ALLEGRO_SAMPLE_ID menu_confirm_sample_id;
        ALLEGRO_SAMPLE *menu_confirm_sample = al_load_sample("sfx/menu_confirm_option.ogg");

        ALLEGRO_SAMPLE_ID character_select_sample_id;
        ALLEGRO_SAMPLE *character_select_sample = al_load_sample("music/DavidKBD - See You in Hell Pack - 13 - Without Me.ogg");

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
        ALLEGRO_SAMPLE *character_confirm_sample = al_load_sample("sfx/character_confirm.ogg");

        ALLEGRO_SAMPLE_ID stage_select_sample_id;
        ALLEGRO_SAMPLE *stage_select_sample = al_load_sample("music/DavidKBD - See You in Hell Pack - 15 - Fear.ogg");

        if (!stage_select_sample) {
                fprintf(stderr, "[-] main(): failed to load stage select music\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded stage select music\n");
        }
        
        ALLEGRO_EVENT evt;

        al_register_event_source(evt_queue, al_get_keyboard_event_source());
        al_register_event_source(evt_queue, al_get_timer_event_source(timer));
        al_register_event_source(evt_queue, al_get_display_event_source(display));
        al_start_timer(timer);
        al_set_window_title(display, "C-Rumble");
        printf("[+] main(): success, starting game...\n");

        GameStates *game_states = create_game_states(); // estrutura com as flags relativas aos diversos estados do jogo

        while (1) {
                al_wait_for_event(evt_queue, &evt);

                if (evt.type == ALLEGRO_EVENT_TIMER) {
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
                                al_clear_to_color(al_map_rgb(0, 0, 0));
                                al_draw_text(character_select_header_font, al_map_rgb(255, 255, 255), (float)al_get_display_width(display) / 2, 128, ALLEGRO_ALIGN_CENTRE, "STAGE SELECTION");
                        } else if (game_states->rumble) {
                                
                        }

                        al_flip_display();
                } else if (evt.type == ALLEGRO_EVENT_DISPLAY_CLOSE || (evt.type == ALLEGRO_EVENT_KEY_DOWN && evt.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
                        al_play_sample(cancel_sound_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);
                        al_rest(0.5);

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

                        if (evt.type == ALLEGRO_EVENT_KEY_DOWN) {
                                if (evt.keyboard.keycode == ALLEGRO_KEY_S || evt.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                                        game_states->menu_select++;
                                
                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->menu_select > MENU_OPTIONS - 1)
                                                game_states->menu_select = 0;
                                } else if (evt.keyboard.keycode == ALLEGRO_KEY_W || evt.keyboard.keycode == ALLEGRO_KEY_UP) {
                                        game_states->menu_select--;

                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->menu_select < 0)
                                                game_states->menu_select = MENU_OPTIONS - 1;
                                } else if (evt.keyboard.keycode == ALLEGRO_KEY_ENTER) {
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
                                } else if (evt.keyboard.keycode == ALLEGRO_KEY_DELETE) {
                                        al_play_sample(cancel_sound_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);
                                        al_rest(0.5);

                                        break;
                                }
                        }
                } else if (game_states->character_select) {
                        if (game_states->play_character_select_welcome_sample && game_states->play_character_select_sample) {
                                al_rest(0.25);
                                al_play_sample(character_select_welcome_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &character_select_welcome_sample_id);
                                al_play_sample(character_select_sample, 0.25, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &character_select_sample_id);
                        }

                        game_states->play_character_select_welcome_sample = 0;
                        game_states->play_character_select_sample = 0;
                        game_states->play_menu_sample = 1;
                        game_states->play_stage_select_sample = 1;
                        game_states->menu_select = 0;

                        if (evt.type == ALLEGRO_EVENT_KEY_DOWN) {
                                if (evt.keyboard.keycode == ALLEGRO_KEY_DELETE) {
                                        game_states->menu = 1;
                                        game_states->character_select = 0;

                                        al_play_sample(cancel_sound_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);
                                        al_stop_sample(&character_select_sample_id);
                                        al_rest(0.25);
                                }
                                
                                if (evt.keyboard.keycode == ALLEGRO_KEY_D && !game_states->character_select_nav_p1_confirm) {
                                        game_states->character_select_nav_p1++;
                                
                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->character_select_nav_p1 > NUM_CHARACTERS - 1)
                                                game_states->character_select_nav_p1 = 0;
                                } else if (evt.keyboard.keycode == ALLEGRO_KEY_A && !game_states->character_select_nav_p1_confirm) {
                                        game_states->character_select_nav_p1--;

                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->character_select_nav_p1 < 0)
                                                game_states->character_select_nav_p1 = NUM_CHARACTERS - 1;
                                } else if (evt.keyboard.keycode == ALLEGRO_KEY_ENTER && !game_states->character_select_nav_p1_confirm) {
                                        game_states->character_select_nav_p1_confirm = 1;

                                        al_play_sample(character_confirm_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &character_confirm_sample_id);

                                        switch (game_states->character_select_nav_p1) {
                                                case 0:
                                                printf("\nP1 SELECTED VIKING\n");

                                                break;

                                                case 1:
                                                printf("\nP1 SELECTED KNIGHT\n");

                                                break;

                                                case 2:
                                                printf("\nP1 SELECTED SPEARWOMAN\n");

                                                break;

                                                case 3:
                                                printf("\nP1 SELECTED FIRE WARRIOR\n");

                                                break;
                                        }
                                }

                                if (evt.keyboard.keycode == ALLEGRO_KEY_RIGHT && !game_states->character_select_nav_p2_confirm) {
                                        game_states->character_select_nav_p2++;
                                
                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->character_select_nav_p2 > NUM_CHARACTERS - 1)
                                                game_states->character_select_nav_p2 = 0;
                                } else if (evt.keyboard.keycode == ALLEGRO_KEY_LEFT && !game_states->character_select_nav_p2_confirm) {
                                        game_states->character_select_nav_p2--;

                                        al_play_sample(menu_select_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (game_states->character_select_nav_p2 < 0)
                                                game_states->character_select_nav_p2 = NUM_CHARACTERS - 1;
                                } else if (evt.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && !game_states->character_select_nav_p2_confirm) {
                                        game_states->character_select_nav_p2_confirm = 1;

                                        al_play_sample(character_confirm_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &character_confirm_sample_id);

                                        switch (game_states->character_select_nav_p2) {
                                                case 0:
                                                printf("\nP2 SELECTED VIKING\n");

                                                break;

                                                case 1:
                                                printf("\nP2 SELECTED KNIGHT\n");

                                                break;

                                                case 2:
                                                printf("\nP2 SELECTED SPEARWOMAN\n");

                                                break;

                                                case 3:
                                                printf("\nP2 SELECTED FIRE WARRIOR\n");

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
                        if (game_states->play_stage_select_sample) {
                                al_play_sample(stage_select_sample, 0.25, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &stage_select_sample_id);
                                al_rest(0.25);
                        }
                        
                        game_states->play_stage_select_sample = 0;
                        game_states->character_select_nav_p1 = 0;
                        game_states->character_select_nav_p2 = 0;
                        game_states->character_select_nav_p1_confirm = 0;
                        game_states->character_select_nav_p2_confirm = 0;
                        game_states->play_character_select_sample = 1;
                        game_states->play_character_select_welcome_sample = 1;

                        if (evt.type == ALLEGRO_EVENT_KEY_DOWN) {
                                if (evt.keyboard.keycode == ALLEGRO_KEY_DELETE) {
                                        game_states->stage_select = 0;
                                        game_states->character_select = 1;

                                        al_play_sample(cancel_sound_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);
                                        al_stop_sample(&stage_select_sample_id);
                                        al_rest(0.25);
                                }
                        }
                } else if (game_states->rumble) {

                }
        }

        printf("[+] main(): exiting game...\n");
        destroy_game_states(game_states);

        al_destroy_font(menu_header_font);
        al_destroy_font(menu_options_font);
        al_destroy_font(character_select_header_font);
        al_destroy_font(character_select_display_name_font);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(evt_queue);
        al_destroy_sample(menu_sample);
        al_destroy_sample(menu_confirm_sample);
        al_destroy_sample(menu_select_sample);
        al_destroy_sample(cancel_sound_sample);
        al_destroy_sample(character_select_welcome_sample);
        al_destroy_sample(character_select_sample);
        al_destroy_sample(character_confirm_sample);
        al_destroy_bitmap(game_icon);
        al_destroy_bitmap(viking_icon);
        al_destroy_bitmap(knight_icon);
        al_destroy_bitmap(spearwoman_icon);
        al_destroy_bitmap(fire_warrior_icon);
        al_uninstall_audio();
        al_uninstall_keyboard();

        return 0;
}