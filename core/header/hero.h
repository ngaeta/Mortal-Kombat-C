#include "animation.h"

#define IDLE  0
#define WALK  1

typedef struct hero 
{
    int health;
    sprite_t sprite;
    animation_t curr_anim;
    animation_t animations[WALK + 1];
} hero_t;

void hero_init(SDL_Renderer* renderer, hero_t* hero, SDL_Rect sprite_rect);
void hero_tick(hero_t* hero);
void hero_input(SDL_Renderer* renderer, hero_t* hero, SDL_Event* event);
void hero_draw(SDL_Renderer* renderer, hero_t* hero);

