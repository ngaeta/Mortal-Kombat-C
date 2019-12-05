#include "../header/hero.h"

void hero_init(SDL_Renderer* renderer, hero_t* hero, SDL_Rect* sprite_rect)
{
    sprite_t sprite;
    sprite_init(&sprite, sprite_rect);

    SDL_Rect* texture_rect;
    texture_rect->x = texture_rect->y = 0;
    texture_rect->w= 50;
    texture_rect->h = 112;
    sprite_set_texture(renderer, &sprite, "Assets/Heroes/scorpion_walk.png", texture_rect);
    hero->sprite = sprite;

    animation_t walk_anim;
    animation_init(&walk_anim, 9, 100);
    hero->curr_anim = walk_anim;
}

void hero_tick(hero_t* hero) 
{
    animation_tick(&hero->sprite, &hero->curr_anim);
}

void hero_draw(SDL_Renderer* renderer, hero_t* hero)
{
    sprite_draw(renderer, &hero->sprite);
}