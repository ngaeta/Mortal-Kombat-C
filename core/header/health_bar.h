#include "sprite.h"

typedef struct health_bar
{
    sprite_t empty_bar;
    sprite_t full_bar;
    sprite_t character_name;
} health_bar_t;

void health_bar_init(health_bar_t* health_bar, SDL_Rect sprite_rect, SDL_Renderer* renderer, const char* character_name_file);
void health_bar_set_energy(health_bar_t* health_bar, int energy);
void health_bar_draw(SDL_Renderer* renderer, health_bar_t* health_bar);
void health_bar_set_size(health_bar_t* health_bar, int size_multiplier);
