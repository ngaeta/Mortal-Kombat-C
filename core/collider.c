#include "header/collider.h"

void collider_init(collider_t* collider, SDL_Rect sprite_rect, void*owner, void (*on_collision_ptr)()) 
{
    collider->rect = sprite_rect;
    collider->owner = owner;
    collider->on_collision_ptr = on_collision_ptr;
}

void collider_tick(collider_t* collider, SDL_Rect new_rect)
{
    collider->rect = new_rect;
}