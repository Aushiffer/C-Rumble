#include "load_sprites.h"

ALLEGRO_BITMAP **load_spriteset(unsigned short num_frames, char *sprite_dir_path_var, const char *sprite_dir_path_const, unsigned long path_length) {
        ALLEGRO_BITMAP **bitmap_array = (ALLEGRO_BITMAP **)malloc(num_frames * sizeof(ALLEGRO_BITMAP *));
        
        for (int i = 0; i < num_frames; i++) {
                snprintf(sprite_dir_path_var, path_length, "%s%d.png", sprite_dir_path_const, i + 1);
                bitmap_array[i] = al_load_bitmap(sprite_dir_path_var);

                if (!bitmap_array[i])
                        return NULL;
        }

        return bitmap_array;
}