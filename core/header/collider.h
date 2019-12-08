 #ifndef COLLIDER_H
 #define COLLIDER_H

 #include <SDL.h>

typedef struct collider
{
    SDL_Rect rect;
    const char* owner_name;
    void* owner;
    void (*on_collision_ptr)();
} collider_t;

void collider_init(collider_t* collider, SDL_Rect new_rect, void*owner, void (*on_collision_ptr)());
void collider_tick(collider_t* collider, SDL_Rect new_rect);

#endif
 