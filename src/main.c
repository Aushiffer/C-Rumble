#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "../enums/main_func_flags.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MENU_OPTIONS 2

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
                fprintf(stderr, "[-] main(): failed to init font addons\n");
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

        ALLEGRO_BITMAP *game_icon = al_load_bitmap("imgs/icons/game_icon.png");

        if (!game_icon) {
                fprintf(stderr, "[-] main(): failed to load the game icon\n");
                exit(AL_LOAD_GAME_ICON_ERROR);
        } else {
                printf("[+] main(): loaded game icon\n");
        }

        al_set_display_icon(display, game_icon);

        ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);

        if (!timer) {
                fprintf(stderr, "[-] main(): failed to initialize timer\n");
                exit(AL_CREATE_TIMER_ERROR);
        } else {
                printf("[+] main(): initialized timer\n");
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
                fprintf(stderr, "[-] main(): failed to load menu header font\n");
                exit(AL_LOAD_FONT_ERROR);
        } else {
                printf("[+] main(): loaded menu header font\n");
        }

        ALLEGRO_FONT *menu_options_font = al_load_font("fonts/osaka-re.ttf", 64, 0);

        if (!menu_options_font) {
                fprintf(stderr, "[-] main(): failed to load menu options font\n");
                exit(AL_LOAD_FONT_ERROR);
        } else {
                printf("[+] main(): loaded menu options font\n");
        }

        ALLEGRO_FONT *character_select_header_font = al_load_font("fonts/Osake.ttf", 64, 0);

        if (!character_select_header_font) {
                fprintf(stderr, "[-] main(): failed to load character select header font\n");
                exit(AL_LOAD_FONT_ERROR);
        } else {
                printf("[+] main(): loaded character select header font\n");
        }

        if (!al_install_audio() || !al_init_acodec_addon() || !al_reserve_samples(5)) {
                fprintf(stderr, "[-] main(): failed to set audio\n");
                exit(AL_SET_AUDIO_ERROR);
        } else {
                printf("[+] main(): set audio\n");
        }

        ALLEGRO_SAMPLE_ID menu_sample_id;
        ALLEGRO_SAMPLE *menu_sample = al_load_sample("music/menu_music.ogg");

        if (!menu_sample) {
                fprintf(stderr, "[-] main(): failed to load menu sample\n");
                exit(AL_LOAD_SAMPLE_ERROR);
        } else {
                printf("[+] main(): loaded menu sample\n");
        }

        ALLEGRO_SAMPLE_ID menu_select_sample_id;
        ALLEGRO_SAMPLE *menu_select_sample = al_load_sample("sfx/menu_select_option.ogg");
        ALLEGRO_SAMPLE_ID menu_confirm_sample_id;
        ALLEGRO_SAMPLE *menu_confirm_sample = al_load_sample("sfx/menu_confirm_option.ogg");
        ALLEGRO_SAMPLE_ID character_select_sample_id;
        ALLEGRO_SAMPLE *character_select_sample = al_load_sample("music/character_select_music.ogg");
        ALLEGRO_SAMPLE_ID character_select_welcome_sample_id;
        ALLEGRO_SAMPLE *character_select_welcome_sample = al_load_sample("sfx/choose_your_character.ogg");
        ALLEGRO_SAMPLE_ID cancel_sound_sample_id;
        ALLEGRO_SAMPLE *cancel_sound_sample = al_load_sample("sfx/cancel.ogg");
        
        ALLEGRO_EVENT evt;

        al_register_event_source(evt_queue, al_get_keyboard_event_source());
        al_register_event_source(evt_queue, al_get_timer_event_source(timer));
        al_register_event_source(evt_queue, al_get_display_event_source(display));
        al_start_timer(timer);
        al_set_window_title(display, "C-Rumble");
        printf("[+] main(): loading game...\n");

        unsigned char menu = 1; /* default */
        unsigned char play_menu_sample = 1; /* default */
        char menu_select = 0; /* default */
        unsigned char character_select = 0; /* default */
        unsigned char play_character_select_welcome_sample = 0; /* default */
        unsigned char play_character_select_sample = 0; /* default */
        unsigned char one_player_game = 0; /* default */
        unsigned char stage_select = 0; /* default */
        unsigned char rumble = 0; /* default */

        while (1) {
                al_wait_for_event(evt_queue, &evt);

                if (evt.type == ALLEGRO_EVENT_TIMER) {
                        if (menu) {
                                al_clear_to_color(al_map_rgb(0, 25, 51));
                                al_draw_text(menu_header_font, al_map_rgb(255, 255, 255), (float)al_get_display_width(display) / 2, (float)WIN_HEIGHT / 2 - 250, ALLEGRO_ALIGN_CENTRE, "C-RUMBLE");

                                if (menu_select == 0) {
                                        al_draw_text(menu_options_font, al_map_rgb(255, 255, 255), (float)al_get_display_width(display) / 2, (float)WIN_HEIGHT / 2 + 64, ALLEGRO_ALIGN_CENTRE, "1P VS. CPU");
                                        al_draw_text(menu_options_font, al_map_rgb(120, 120, 120), (float)al_get_display_width(display) / 2, (float)WIN_HEIGHT / 2 + 128, ALLEGRO_ALIGN_CENTRE, "1P VS. 2P");
                                } else if (menu_select == 1) {
                                        al_draw_text(menu_options_font, al_map_rgb(120, 120, 120), (float)al_get_display_width(display) / 2, (float)WIN_HEIGHT / 2 + 64, ALLEGRO_ALIGN_CENTRE, "1P VS. CPU");
                                        al_draw_text(menu_options_font, al_map_rgb(255, 255, 255), (float)al_get_display_width(display) / 2, (float)WIN_HEIGHT / 2 + 128, ALLEGRO_ALIGN_CENTRE, "1P VS. 2P");
                                }
                        } else if (character_select) {
                                al_clear_to_color(al_map_rgb(0, 25, 51));
                                al_draw_text(character_select_header_font, al_map_rgb(255, 255, 255), (float)al_get_display_width(display) / 2, (float)WIN_HEIGHT / 2 - 250, ALLEGRO_ALIGN_CENTRE, "CHOOSE YOUR CHARACTER");
                                al_draw_text(menu_options_font, al_map_rgb(255, 255, 255), 128, (float)WIN_HEIGHT / 2, ALLEGRO_ALIGN_LEFT, "1P");

                                if (one_player_game)
                                        al_draw_text(menu_options_font, al_map_rgb(255, 255, 255), (float)al_get_display_width(display) - 128, (float)WIN_HEIGHT / 2, ALLEGRO_ALIGN_RIGHT, "CPU");
                                else
                                        al_draw_text(menu_options_font, al_map_rgb(255, 255, 255), (float)al_get_display_width(display) - 128, (float)WIN_HEIGHT / 2, ALLEGRO_ALIGN_RIGHT, "2P");
                        } else if (stage_select) {

                        } else if (rumble) {
                                
                        }

                        al_flip_display();
                } else if (evt.type == ALLEGRO_EVENT_DISPLAY_CLOSE || (evt.type == ALLEGRO_EVENT_KEY_DOWN && evt.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
                        al_play_sample(cancel_sound_sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);
                        al_rest(0.5);

                        break;
                }
                
                if (menu) {
                        if (play_menu_sample)
                                al_play_sample(menu_sample, 0.35, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &menu_sample_id);
                        
                        play_menu_sample = 0;
                        play_character_select_welcome_sample = 1;
                        play_character_select_sample = 1;

                        if (evt.type == ALLEGRO_EVENT_KEY_DOWN) {
                                if (evt.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                                        menu_select++;
                                
                                        al_play_sample(menu_select_sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (menu_select > MENU_OPTIONS - 1)
                                                menu_select = 0;
                                } else if (evt.keyboard.keycode == ALLEGRO_KEY_UP) {
                                        menu_select--;

                                        al_play_sample(menu_select_sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_select_sample_id);

                                        if (menu_select < 0)
                                                menu_select = MENU_OPTIONS - 1;
                                } else if (evt.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                                        al_stop_sample(&menu_sample_id);
                                        al_play_sample(menu_confirm_sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &menu_confirm_sample_id);

                                        menu = 0;
                                        character_select = 1;

                                        if (menu_select == 0)
                                                one_player_game = 1;
                                        else if (menu_select == 1)
                                                one_player_game = 0;
                                } else if (evt.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                                        al_play_sample(cancel_sound_sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);
                                        al_rest(0.5);

                                        break;
                                }
                        }
                } else if (character_select) {
                        if (play_character_select_welcome_sample && play_character_select_sample) {
                                al_rest(1.0);
                                al_play_sample(character_select_welcome_sample, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &character_select_welcome_sample_id);
                                al_play_sample(character_select_sample, 0.35, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &character_select_sample_id);
                        }

                        play_character_select_welcome_sample = 0;
                        play_character_select_sample = 0;
                        play_menu_sample = 1;

                        if (evt.type == ALLEGRO_EVENT_KEY_DOWN && evt.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                                menu = 1;
                                character_select = 0;

                                al_stop_sample(&character_select_sample_id);
                                al_play_sample(cancel_sound_sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &cancel_sound_sample_id);
                        }
                }
        }
        
        al_destroy_font(menu_header_font);
        al_destroy_font(menu_options_font);
        al_destroy_font(character_select_header_font);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(evt_queue);
        al_destroy_sample(menu_sample);
        al_destroy_sample(menu_confirm_sample);
        al_destroy_sample(menu_select_sample);
        al_destroy_sample(cancel_sound_sample);
        al_destroy_sample(character_select_welcome_sample);
        al_destroy_bitmap(game_icon);
        al_uninstall_audio();
        al_uninstall_keyboard();

        return 0;
}