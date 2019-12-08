#include "header/utility.h"
#include "header/hero.h"

void hero_init(SDL_Renderer* renderer, hero_t* hero, SDL_Rect sprite_rect)
{
    hero->health = 100;
    hero->punch_damage = 10;
    hero->kick_damage = 20;

    sprite_t sprite;
    sprite_init(&sprite, sprite_rect);

    SDL_Rect texture_rect = create_rect(0, 0, 54, 112);
    sprite_set_texture(renderer, &sprite, "Assets/Heroes/scorpion_sheet.png", &texture_rect);
    hero->sprite = sprite;
    
    collider_t collider;
    collider_init(&collider, sprite.sprite_rect, hero, &on_collision_enter);
    collider.owner_name = "hero";
    hero->collider = collider;

    vector2_t speed;
    speed.x = 150;
    speed.y = 0;
    hero->move_speed = speed;

    character_t character;
    speed.x = speed.y = 0;
    character_init(&character, &hero->sprite, speed);
    hero->character = character;

    animation_t idle_anim;
    animation_init(&idle_anim, 6, 100, texture_rect);
    idle_anim.name = IDLE;

    animation_t walk_anim;
    animation_init(&walk_anim, 9, 80, create_rect(0, 112, 54, 112));
    walk_anim.name = WALK;

    animation_t punch_anim;
    animation_init(&punch_anim, 5, 110, create_rect(0, 224, 63, 112));
    animation_set_loop(&punch_anim, 0);
    punch_anim.name = PUNCH;

    animation_t get_punch_anim;
    animation_init(&get_punch_anim, 3, 100, create_rect(0, 336, 54, 112));
    animation_set_loop(&get_punch_anim, 0);
    get_punch_anim.name = GET_PUNCH;

    animation_t kick_anim;
    animation_init(&kick_anim, 7, 130, create_rect(0, 448, 80, 112));
    animation_set_loop(&kick_anim, 0);
    kick_anim.name = KICK;

    hero->animations[IDLE] = idle_anim;
    hero->animations[WALK] = walk_anim;
    hero->animations[PUNCH] = punch_anim;
    hero->animations[GET_PUNCH] = get_punch_anim;
    hero->animations[KICK] = kick_anim;

    hero->curr_anim = idle_anim;
    animation_play(&hero->curr_anim, &hero->sprite);
}

void hero_input(SDL_Renderer* renderer, hero_t* hero, SDL_Event* event) 
{
    if(event->type == SDL_KEYDOWN && (hero->curr_anim.name == IDLE || hero->curr_anim.name == WALK))
    {
        if(event->key.keysym.sym == SDLK_p) 
        {
            hero->character.speed.x = 0;
            hero->curr_anim = hero->animations[PUNCH];
            animation_play(&hero->curr_anim, &hero->sprite);
        }
        else if(event->key.keysym.sym == SDLK_k)
        {
            hero->character.speed.x = 0;
            hero->curr_anim = hero->animations[KICK];
            animation_play(&hero->curr_anim, &hero->sprite);                                                                             
        }
        else if(event->key.keysym.sym == SDLK_LEFT)
        {
            hero->character.speed.x = -(hero->move_speed.x);
            if(hero->curr_anim.name != WALK)
            {
                hero->curr_anim = hero->animations[WALK];
                animation_set_reversed(&hero->curr_anim);
                animation_play(&hero->curr_anim, &hero->sprite);   
            }
        }
        else if(event->key.keysym.sym == SDLK_RIGHT) 
        {
            hero->character.speed.x = hero->move_speed.x;
            if(hero->curr_anim.name != WALK)
            {
                hero->curr_anim = hero->animations[WALK];
                animation_play(&hero->curr_anim, &hero->sprite);   
            }
        }//debug else
        else if(event->key.keysym.sym == SDLK_d) 
        {
            hero->curr_anim = hero->animations[GET_PUNCH];
            animation_play(&hero->curr_anim, &hero->sprite);   
        }
    }
    else 
    {
        hero->character.speed.x = 0;
        if(hero->curr_anim.is_playing == 0 || hero->curr_anim.name == WALK)
        {
           hero->curr_anim = hero->animations[IDLE];
           animation_play(&hero->curr_anim, &hero->sprite);  
        }
    }
}

void hero_tick(hero_t* hero, double delta_time) 
{
    character_tick(&hero->character, delta_time);
    collider_tick(&hero->collider, hero->sprite.sprite_rect);

    animation_tick(&hero->sprite, &hero->curr_anim);
    if(!hero->curr_anim.is_playing) 
    {
        hero->curr_anim = hero->animations[IDLE];
        animation_play(&hero->curr_anim, &hero->sprite);  
    }
}

void hero_draw(SDL_Renderer* renderer, hero_t* hero)
{
    sprite_draw(renderer, &hero->sprite);
    //debug collider
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
    SDL_RenderFillRect(renderer, &hero->collider.rect);
}

void hero_flip_X(hero_t* hero)
{
    sprite_flip(&hero->sprite, SDL_FLIP_HORIZONTAL);
}

void on_collision_enter(collider_t* my_collider, collider_t* other_collider)
{
    hero_t* my_hero = (hero_t*) my_collider->owner;
    hero_t* other_hero = (hero_t*) other_collider->owner;
    //SDL_Log("my_hero health %d", my_hero->health);
    //SDL_Log("other_hero health %d", other_hero->health);

    if(other_hero)
    {
        if(my_hero->curr_anim.name == PUNCH && my_hero->curr_anim.curr_frame == 2) 
        {
            hero_get_punch(other_hero, my_hero->punch_damage);
        }
    }
}

void hero_get_punch(hero_t* hero, int damage) 
{
    if(hero->curr_anim.name != GET_PUNCH) 
    {
        hero->health-=damage;
        if(hero->health > 0)
        {
            hero->curr_anim = hero->animations[GET_PUNCH];
            animation_play(&hero->curr_anim, &hero->sprite);   
        }
        else
            hero_die(hero);
    }
}

void hero_die(hero_t*hero)
{
    SDL_Log("Die");
}

