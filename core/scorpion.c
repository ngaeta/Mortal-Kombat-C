#include "header/scorpion.h"
#include <math.h>

void scorpion_hero_init(SDL_Renderer* renderer, hero_t* hero, SDL_Rect sprite_rect, enum Player player)
{
    hero_init(renderer, hero, sprite_rect, "Assets/Heroes/scorpion_sheet.png", "Assets/UI/scorpion_label.png", player);
    
    hero->collider.on_collision_ptr = scorpion_on_collision_enter;
    //override methods
    hero->do_fatality_ptr = scorpion_fatality;
    hero->child_tick_ptr = scorpion_hero_tick;
    hero->child_input_ptr = scorpion_hero_input;
    hero->child_draw_ptr = scorpion_hero_draw;

    animation_t idle_anim;
    animation_init(&idle_anim, 6, 150, create_rect(0, 0, 54, 112));
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

    animation_t die_anim;
    animation_init(&die_anim, 5, 100, create_rect(0, 560, 54, 112));
    die_anim.name = DIE;

    animation_t fatality_anim;
    animation_init(&fatality_anim, 5, 90, create_rect(0, 672, 86, 112));
    animation_set_loop(&fatality_anim, 0);
    fatality_anim.name = FATALITY;

    animation_t get_fatality_anim;
    animation_init(&get_fatality_anim, 1, 100, create_rect(0, 784, 54, 112));
    get_fatality_anim.name = GET_FATALITY;

    animation_t win_anim;
    animation_init(&win_anim, 2, 140, create_rect(0, 896, 54, 112));
    animation_set_loop(&win_anim, 0);
    win_anim.name = WIN;

    hero->animations[IDLE] = idle_anim;
    hero->animations[WALK] = walk_anim;
    hero->animations[PUNCH] = punch_anim;
    hero->animations[GET_PUNCH] = get_punch_anim;
    hero->animations[KICK] = kick_anim;
    hero->animations[FATALITY] = fatality_anim;
    hero->animations[GET_FATALITY] = get_fatality_anim;
    hero->animations[WIN] = win_anim;
    hero->animations[DIE] = die_anim;

    hero->curr_anim = idle_anim;
    animation_play(&hero->curr_anim, &hero->sprite);
}

void scorpion_hero_input(SDL_Renderer* renderer, hero_t* hero, int num_keys_pressed, const Uint8* keys) 
{
    hero_input(renderer, hero, num_keys_pressed, keys);  
}

void scorpion_hero_tick(hero_t* hero, double delta_time) 
{
    hero_tick(hero, delta_time);
    if(hero->curr_anim.name == FATALITY && hero->curr_anim.curr_frame == 3)
    {
        hero_get_fatality(hero->rival);
    }
}

void scorpion_hero_draw(SDL_Renderer* renderer, hero_t* hero)
{
    hero_draw(renderer, hero);
}

void scorpion_hero_flip_X(hero_t* hero)
{
    hero_flip_X(hero);
}

void scorpion_on_collision_enter(collider_t* my_collider, collider_t* other_collider)
{
    hero_t* my_hero = (hero_t*) my_collider->owner;
    hero_t* other_hero = (hero_t*) other_collider->owner;

    if(other_hero)
    {
        if(my_hero->curr_anim.name == PUNCH && my_hero->curr_anim.curr_frame == 2) 
        {
            hero_get_punch(other_hero, my_hero->punch_damage);
        }
        else if(my_hero->curr_anim.name == KICK && my_hero->curr_anim.curr_frame == 3) 
        {
            hero_get_kick(other_hero, my_hero->kick_damage);
        }
    }
}

void scorpion_hero_get_punch(hero_t* hero, int damage) 
{
    hero_get_punch(hero, damage);
}

void scorpion_hero_get_kick(hero_t* hero, int damage)
{
    hero_get_punch(hero, hero->kick_damage);
}

void scorpion_hero_get_fatality(hero_t* hero) 
{
    hero_get_fatality(hero); 
}

void scorpion_hero_die(hero_t* hero)
{
    hero_die(hero);  
}

void scorpion_fatality(hero_t* hero)
{
    if(abs(hero->sprite.x - hero->rival->sprite.x) < hero->sprite.sprite_rect.w && hero->rival->curr_anim.name != GET_FATALITY)
    {
        hero->curr_anim = hero->animations[FATALITY];
        animation_play(&hero->curr_anim, &hero->sprite);  
    }
}
