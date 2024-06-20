#ifndef __SELECTOR__
#define __SELECTOR__

#include <allegro5/allegro_audio.h>

void handle_selection(char *selector_ptr, char num_options, unsigned char increase, ALLEGRO_SAMPLE *select_sample, ALLEGRO_SAMPLE_ID select_sample_id);

#endif // __SELECTOR__