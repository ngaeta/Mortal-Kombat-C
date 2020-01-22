#include "header/utility.h"
#include "header/hero.h"

void hero_init(SDL_Renderer* renderer, hero_t* hero, SDL_Rect sprite_rect, const char* texture_name, const char* character_name_file, 
    enum Player player)
{
    hero->health = 100;
    hero->punch_damage = 10;
    hero->kick_damage = 15;
    hero->player = player;
    
    sprite_t sprite;
    sprite_init(&sprite, sprite_rect);
    SDL_Rect texture_rect = create_rect(0, 0, 54, 112);
    sprite_set_texture(renderer, &sprite, texture_name, &texture_rect);
    hero->sprite = sprite;
    if(player == Player_Two) sprite_flip(&hero->sprite, SDL_FLIP_HORIZONTAL);

    sprite_t hero_name;
    sprite_init(&hero_name, create_rect(0, 0, 90, 25));
    sprite_set_texture(renderer, &hero_name, character_name_file, NULL);
    hero->hero_name = hero_name;

    health_bar_t health_bar;
    health_bar_init(&health_bar, player == Player_One ? create_rect(45, 80, 100, 12) : create_rect(380,80, 100, 12), renderer, character_name_file);
    health_bar_set_size(&health_bar, 2);
    hero->health_bar = health_bar;
    
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
}

void hero_input(SDL_Renderer* renderer, hero_t* hero, int num_keys_pressed, const Uint8* keys) 
{
    if(hero->health > 0 && hero->curr_anim.name != WIN)
    {
        if(num_keys_pressed > 0 && (hero->curr_anim.name == IDLE || hero->curr_anim.name == WALK))
        {
            if(keys[hero->keycode_input[INPUT_PUNCH]]) 
            {
                hero->character.speed.x = 0;
                hero->curr_anim = hero->animations[PUNCH];
                animation_play(&hero->curr_anim, &hero->sprite);
            }
            else if(keys[hero->keycode_input[INPUT_KICK]])
            {
                hero->character.speed.x = 0;
                hero->curr_anim = hero->animations[KICK];
                animation_play(&hero->curr_anim, &hero->sprite);                                                                             
            }
            else if(keys[hero->keycode_input[INPUT_WALK_LEFT]])
            {
                hero->character.speed.x = -(hero->move_speed.x);
                animation_set_reversed(&hero->curr_anim, hero->player == Player_One ? 1 : 0);
                if(hero->curr_anim.name != WALK)
                {
                    hero->curr_anim = hero->animations[WALK];
                    animation_play(&hero->curr_anim, &hero->sprite);   
                }
            }
            else if(keys[hero->keycode_input[INPUT_WALK_RIGHT]]) 
            {
                hero->character.speed.x = hero->move_speed.x;        
                animation_set_reversed(&hero->curr_anim, hero->player == Player_Two ? 1 : 0);
                if(hero->curr_anim.name != WALK)
                {
                    hero->curr_anim = hero->animations[WALK];
                    animation_play(&hero->curr_anim, &hero->sprite);  
                }
            }
            else if(keys[hero->keycode_input[INPUT_FATALITY]])
            {
                if(hero->rival->health <= 0)
                    hero->do_fatality_ptr(hero); 
                else
                {
                    SDL_Log("Rival is not dead");
                }    
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
}

void hero_tick(hero_t* hero, double delta_time) 
{
    if((hero->character.speed.x < 0 && hero->sprite.x > 20) || (hero->character.speed.x > 0 && hero->sprite.x < 560))
        character_tick(&hero->character, delta_time);

    collider_tick(&hero->collider, hero->sprite.sprite_rect);
    animation_tick(&hero->sprite, &hero->curr_anim);
    
    if(hero->curr_anim.name != WIN)
    {
        if(hero->curr_anim.name == FATALITY)
        {
            if(!hero->curr_anim.is_playing) 
            {
                hero->curr_anim = hero->animations[WIN];
                animation_play(&hero->curr_anim, &hero->sprite); 
            } 
        }
        else if(hero->health > 0 && !hero->curr_anim.is_playing) 
        {
            hero->curr_anim = hero->animations[IDLE];
            animation_play(&hero->curr_anim, &hero->sprite);  
        }
    }
}

void hero_draw(SDL_Renderer* renderer, hero_t* hero)
{
    sprite_draw(renderer, &hero->sprite);
    health_bar_draw(renderer, &hero->health_bar);
    //debug collider
    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
    // SDL_RenderFillRect(renderer, &hero->collider.rect);
}

void hero_flip_X(hero_t* hero)
{
    sprite_flip(&hero->sprite, SDL_FLIP_HORIZONTAL);
}

void on_collision_enter(collider_t* my_collider, collider_t* other_collider)
{
}

void hero_get_punch(hero_t* hero, int damage) 
{
    if(hero->curr_anim.name != GET_PUNCH) 
    {
        hero->health-=damage;
        health_bar_set_energy(&hero->health_bar, hero->health);
        
        if(hero->health > 0)
        {
            hero->curr_anim = hero->animations[GET_PUNCH];
            animation_play(&hero->curr_anim, &hero->sprite);   
        }
        else
            hero_die(hero);
    }
}

void hero_get_kick(hero_t* hero, int damage)
{
    //to modify
    hero_get_punch(hero, hero->kick_damage);
}

void hero_get_fatality(hero_t* hero) 
{
    hero->curr_anim = hero->animations[GET_FATALITY];
    animation_play(&hero->curr_anim, &hero->sprite);   
}

void hero_die(hero_t* hero)
{
    hero->character.speed.x = 0;
    hero->curr_anim = hero->animations[DIE];
    animation_play(&hero->curr_anim, &hero->sprite);   
}


