#include "utility.h"
#include "hero.h"

void scorpion_hero_init(SDL_Renderer* renderer, hero_t* hero, SDL_Rect sprite_rect, enum Player player);
void scorpion_hero_input(SDL_Renderer* renderer, hero_t* hero, int num_keys_pressed, const Uint8* keys); 
void scorpion_hero_tick(hero_t* hero, double delta_time);
void scorpion_hero_draw(SDL_Renderer* renderer, hero_t* hero);
void scorpion_hero_flip_X(hero_t* hero);
void scorpion_on_collision_enter(collider_t* my_collider, collider_t* other_collider);
void scorpion_hero_get_punch(hero_t* hero, int damage);
void scorpion_hero_get_kick(hero_t* hero, int damage);
void scorpion_hero_get_fatality(hero_t* hero);
void scorpion_hero_die(hero_t* hero);
void scorpion_fatality(hero_t* hero);

