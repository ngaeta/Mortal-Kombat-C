#include "header/character.h"

void character_init(character_t* character, sprite_t* sprite, vector2_t speed) 
{
    character->sprite = sprite;
    character->speed = speed;
}

void character_tick(character_t* character, double delta_time)
{
    character->sprite->x += (int) (character->speed.x * delta_time);
    character->sprite->y += (int) (character->speed.y * delta_time);
}