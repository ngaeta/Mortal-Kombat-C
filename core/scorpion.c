#include "../header/hero.h"
#include "../header/utility.h"

void hero_init(SDL_Renderer* renderer, hero_t* hero, SDL_Rect* sprite_rect)
{
    sprite_t sprite;
    sprite_init(&sprite, sprite_rect);

    SDL_Rect* texture_rect;
    texture_rect->x = texture_rect->y = 0;
    texture_rect->w= 54;
    texture_rect->h = 112;
    sprite_set_texture(renderer, &sprite, "Assets/Heroes/scorpionNonbuona.png", texture_rect);
    hero->sprite = sprite;

    animation_t idle_anim;
    animation_init(&idle_anim, 6, 100, texture_rect);

    
    animation_t walk_anim;
    animation_init(&walk_anim, 9, 100, texture_rect);

    hero->animations[IDLE] = &idle_anim;
    hero->animations[WALK] = &walk_anim;

    hero->curr_anim = walk_anim;
}

void hero_input(SDL_Renderer* renderer, hero_t* hero, SDL_Event* event) 
{
    if(event->type == SDL_KEYDOWN)
    {
        if(event->key.keysym.sym == SDLK_x) 
        {
            SDL_Log("X pressed");
            hero->curr_anim = *(hero->animations[WALK]);
            animation_play(&hero->curr_anim, &hero->sprite);
        }
    }
}

void hero_tick(hero_t* hero) 
{
    //animation_tick(&hero->sprite, &hero->curr_anim);
}

void hero_draw(SDL_Renderer* renderer, hero_t* hero)
{
    sprite_draw(renderer, &hero->sprite);
}