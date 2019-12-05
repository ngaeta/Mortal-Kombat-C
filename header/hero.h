#include "animation.h"

typedef struct hero 
{
    sprite_t sprite;
    int health;
    animation_t curr_anim;
    animation_t* animations[];
    
} hero_t;

void hero_init(SDL_Renderer* renderer, hero_t* hero, SDL_Rect* sprite_rect);
void hero_tick(hero_t* hero);
void hero_input(hero_t* hero, SDL_Event* event);
void hero_draw(SDL_Renderer* renderer, hero_t* hero);

