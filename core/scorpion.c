#include "header/utility.h"
#include "header/hero.h"

void hero_init(SDL_Renderer* renderer, hero_t* hero, SDL_Rect sprite_rect)
{
    sprite_t sprite;
    sprite_init(&sprite, sprite_rect);

    SDL_Rect texture_rect = create_rect(0, 0, 54, 112);
    sprite_set_texture(renderer, &sprite, "Assets/Heroes/scorpion_sheet.png", &texture_rect);
    hero->sprite = sprite;
    
    character_t character;
    vector2_t speed;
    speed.x = 160;
    speed.y = 0;
    character_init(&character, &hero->sprite, speed);
    hero->character = character;

    animation_t idle_anim;
    animation_init(&idle_anim, 6, 100, texture_rect);
    animation_t walk_anim;
    animation_init(&walk_anim, 9, 100, create_rect(0, 112, 54, 112));
    animation_t punch_anim;
    animation_init(&punch_anim, 3, 120, create_rect(0, 224, 63, 112));
    animation_t kick_anim;
    animation_init(&kick_anim, 4, 200, create_rect(0, 448, 80, 112));

    hero->animations[IDLE] = idle_anim;
    hero->animations[WALK] = walk_anim;
    hero->animations[PUNCH] = punch_anim;
    hero->animations[KICK] = kick_anim;

    hero->curr_anim = idle_anim;
}

void hero_input(SDL_Renderer* renderer, hero_t* hero, SDL_Event* event) 
{
    if(event->type == SDL_KEYDOWN)
    {
        if(event->key.keysym.sym == SDLK_p) 
        {
            hero->curr_anim = hero->animations[PUNCH];
            animation_play(&hero->curr_anim, &hero->sprite);
        }
        else if(event->key.keysym.sym == SDLK_k)
        {
            hero->curr_anim = hero->animations[KICK];
            animation_play(&hero->curr_anim, &hero->sprite);                                                                             
        }
        else if(event->key.keysym.sym == SDLK_w)
        {
            hero->curr_anim = hero->animations[WALK];
            animation_play(&hero->curr_anim, &hero->sprite);                                                                              
        }
        if(event->key.keysym.sym == SDLK_p) 
        {
            hero->curr_anim = hero->animations[PUNCH];
            animation_play(&hero->curr_anim, &hero->sprite);
        }
        else if(event->key.keysym.sym == SDLK_k)
        {
            hero->curr_anim = hero->animations[KICK];
            animation_play(&hero->curr_anim, &hero->sprite);                                                                             
        }
        else if(event->key.keysym.sym == SDLK_i)
        {
            hero->curr_anim = hero->animations[IDLE];
            animation_play(&hero->curr_anim, &hero->sprite);                                                                              
        }
    }
}

void hero_tick(hero_t* hero, double delta_time) 
{
    character_tick(&hero->character, delta_time);
    animation_tick(&hero->sprite, &hero->curr_anim);
}

void hero_draw(SDL_Renderer* renderer, hero_t* hero)
{
    sprite_draw(renderer, &hero->sprite);
}

void hero_set_speed(hero_t*hero, int x, int y)
{
    hero->character.speed.x = x;
    hero->character.speed.y = y;
}