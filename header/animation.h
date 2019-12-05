#include "sprite.h"

typedef struct animation
{
    int tot_frames;
    int curr_frame;
    int delay_between_frames;
} animation_t;

void animation_init(animation_t* animation, int frames, int delayPerFrame);
void animation_tick(sprite_t* sprite, animation_t* animation);