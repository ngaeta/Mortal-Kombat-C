 #ifndef COLLIDER_H
 #define COLLIDER_H
 #include <SDL.h>
 
typedef struct collider
{
    SDL_Rect rect;
    void (*on_collision_ptr)();
} collider_t;

#endif
 