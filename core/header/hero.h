#include "animation.h"
#include "character.h"

#define IDLE  0
#define WALK  1
#define PUNCH 2
#define KICK 3

typedef struct hero 
{
    int health;
    sprite_t sprite;
    character_t character;
    animation_t curr_anim;
    animation_t animations[KICK + 1];
} hero_t;

void hero_init(SDL_Renderer* renderer, hero_t* hero, SDL_Rect sprite_rect);
void hero_tick(hero_t* hero, double delta_time);
void hero_input(SDL_Renderer* renderer, hero_t* hero, SDL_Event* event);
void hero_draw(SDL_Renderer* renderer, hero_t* hero);
void hero_set_speed(hero_t*hero, int x, int y);

