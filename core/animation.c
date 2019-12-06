#include "header/animation.h"

void animation_init(animation_t* animation, int frames, int delayPerFrame, SDL_Rect texture_rect)
{
    animation->tot_frames = frames;
    animation->delay_between_frames = delayPerFrame;
    animation->curr_frame = 0;
    animation->loop=1;
    animation->is_playing=0;
    animation->texture_rect = texture_rect;
}

void animation_tick(sprite_t* sprite, animation_t* animation) 
{  
    uint32_t currentTime = SDL_GetTicks();
    if (currentTime > animation->timer + animation->delay_between_frames) 
    {
        animation->curr_frame++;
        if(animation->curr_frame >= animation->tot_frames) 
        {
            if(animation->loop) 
            {
                animation->curr_frame = 0;
            }
            else
            {
                animation->is_playing = 0;
                return;
            }          
        }
        animation->timer = currentTime;
        sprite->texture_rect.x = animation->curr_frame * sprite->texture_rect.w;
    }
}

void animation_play(animation_t* animation, sprite_t* sprite) 
{
    animation->is_playing=1;
    animation->timer = SDL_GetTicks();
    animation->curr_frame = 0;
    sprite->texture_rect = animation->texture_rect;
}

void animation_set_loop(animation_t* animation, int bool)
{
    animation->loop = bool;
}
