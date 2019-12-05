#include "../header/animation.h"

void animation_init(animation_t* animation, int frames, int delayPerFrame)
{
    animation->tot_frames = frames;
    animation->delay_between_frames = delayPerFrame;
    animation->curr_frame = 0;
}

void animation_tick(sprite_t* sprite, animation_t* animation) 
{
    int frame = (SDL_GetTicks() / animation->delay_between_frames) % animation->tot_frames;
    animation->curr_frame = frame;
    sprite->texture_rect->x = frame * sprite->texture_rect->w;
}