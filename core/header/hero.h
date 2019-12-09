#ifndef HERO_H
#define HERO_H

#include "animation.h"
#include "character.h"
#include "collider.h"

#define IDLE  0
#define WALK  1
#define PUNCH 2
#define GET_PUNCH 3
#define KICK 4
#define GET_KICK 5
#define FATALITY 6
#define GET_FATALITY 7
#define WIN 8
#define DIE 9

#define INPUT_WALK_RIGHT  0
#define INPUT_WALK_LEFT  1
#define INPUT_PUNCH 2
#define INPUT_KICK 3
#define INPUT_FATALITY 4

enum Player {Player_One = 1, Player_Two = 2};

typedef struct hero 
{
    int health;
    int punch_damage;
    int kick_damage;
    enum Player player;
    sprite_t sprite;
    vector2_t move_speed;
    character_t character;
    collider_t collider;
    animation_t curr_anim;
    animation_t animations[DIE + 1];
    SDL_Keycode keycode_input[INPUT_FATALITY + 1]; 
    struct hero* rival;
    void (*do_fatality_ptr)();
} hero_t;

void hero_init(SDL_Renderer* renderer, hero_t* hero, SDL_Rect sprite_rect, const char* texture_name, enum Player player);
void hero_tick(hero_t* hero, double delta_time);
void hero_input(SDL_Renderer* renderer, hero_t* hero, int num_keys_pressed, const Uint8* keys);
void hero_draw(SDL_Renderer* renderer, hero_t* hero);
void hero_flip_X(hero_t* hero);
void hero_get_punch(hero_t* hero, int damage);
void hero_get_kick(hero_t* hero, int damage);
void hero_get_fatality(hero_t* hero);
void hero_die(hero_t*hero);
void on_collision_enter(collider_t* my_collider, collider_t* other_collider);

#endif


