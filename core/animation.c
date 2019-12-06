#include "header/animation.h"

void animation_init(animation_t* animation, int frames, int delayPerFrame, SDL_Rect texture_rect)
{
    animation->tot_frames = frames;
    animation->delay_between_frames = delayPerFrame;
    animation->curr_frame = 0;
    animation->texture_rect = texture_rect;
}

void animation_tick(sprite_t* sprite, animation_t* animation) 
{  
    int frame = (SDL_GetTicks() / animation->delay_between_frames) % animation->tot_frames;
    animation->curr_frame = frame;
    sprite->texture_rect.x = frame * sprite->texture_rect.w;
}

void animation_play(animation_t* animation, sprite_t* sprite) 
{
    animation->curr_frame = 0;
    sprite->texture_rect.y = animation->texture_rect.y;
}