#ifndef __LOAD_SPRITES__
#define __LOAD_SPRITES__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/bitmap_io.h>

/* IMPORTANTE: 'bitmap_array' PRECISA estar com todos os seus espaços livres. */
ALLEGRO_BITMAP **load_spriteset(unsigned short num_frames, char *sprite_dir_path_var, const char *sprite_dir_path_const, unsigned long path_length);

#endif // __LOAD_SPRITES__