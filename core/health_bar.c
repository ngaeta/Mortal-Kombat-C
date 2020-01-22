#include "header/health_bar.h"
#include "header/utility.h"

void health_bar_init(health_bar_t* health_bar, SDL_Rect sprite_rect, SDL_Renderer* renderer, const char* character_name_file)
{
    sprite_t full_bar, empty_bar, ui_character_name;
    sprite_init(&full_bar, sprite_rect);
    sprite_set_texture(renderer, &full_bar, "Assets/UI/full_bar.png", NULL);
    
    sprite_init(&empty_bar, sprite_rect);
    sprite_set_texture(renderer, &empty_bar, "Assets/UI/empty_bar.png", NULL);

    sprite_rect.y += 25;
    sprite_init(&ui_character_name, sprite_rect);
    sprite_set_texture(renderer, &ui_character_name, character_name_file, NULL);

    health_bar->full_bar = full_bar;
    health_bar->empty_bar = empty_bar;
    health_bar->character_name = ui_character_name;
}

void health_bar_draw(SDL_Renderer* renderer, health_bar_t* health_bar)
{
    sprite_draw(renderer, &health_bar->empty_bar);
    sprite_draw(renderer, &health_bar->full_bar);
    sprite_draw(renderer, &health_bar->character_name);
}

void health_bar_set_energy(health_bar_t* health_bar, int energy)
{
    if(energy < 0)
        energy = 0;
    health_bar->full_bar.sprite_rect.w = energy;
}

void health_bar_set_size(health_bar_t* health_bar, int size_multiplier) 
{
    health_bar->full_bar.scale_multiplier = size_multiplier;
    health_bar->empty_bar.scale_multiplier = size_multiplier;
    health_bar->character_name.scale_multiplier = size_multiplier;
}


