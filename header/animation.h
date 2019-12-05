#include "sprite.h"

typedef struct animation
{
    int tot_frames;
    int curr_frame;
    int delay_between_frames;
    SDL_Rect* texture_rect;
} animation_t;

void animation_init(animation_t* animation, int frames, int delayPerFrame, SDL_Rect* texture_rect);
void animation_tick(sprite_t* sprite, animation_t* animation);
void animation_play(animation_t* animation, sprite_t* sprite);