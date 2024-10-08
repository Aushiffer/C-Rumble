#ifndef __MAIN_FUNC_FLAGS__
#define __MAIN_FUNC_FLAGS__

enum AllegroFlags {
        AL_INIT_ERROR = 1,
        AL_KEYBOARD_INSTALL_ERROR,
        AL_INIT_FONT_ADDONS_ERROR,
        AL_INIT_IMAGE_ADDON_ERROR,
        AL_INIT_PRIMITIVES_ADDON_ERROR,
        AL_LOAD_ICON_ERROR,
        AL_LOAD_STAGE_ERROR,
        AL_LOAD_SPRITE_ERROR,
        AL_CREATE_DISPLAY_ERROR,
        AL_LOAD_FONT_ERROR,
        AL_LOAD_SAMPLE_ERROR,
        AL_SET_AUDIO_ERROR,
        AL_CREATE_EVENT_QUEUE_ERROR,
        AL_CREATE_TIMER_ERROR
};

enum MiscFlags {
        INVALID_GAME_STATES_ERROR = 14,
        INVALID_FIGHTER_ERROR,
        INVALID_GARBAGE_ARRAY
};

#endif // __MAIN_FUNC_FLAGS__