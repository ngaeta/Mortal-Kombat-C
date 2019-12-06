#ifndef CHARACTER_H
#define CHARACTER_H

#include "sprite.h"

typedef struct vector2
{
    float x;
    float y;
}vector2_t;

typedef struct character
{
    sprite_t* sprite;
    vector2_t speed;
} character_t;

void character_init(character_t* character, sprite_t* sprite, vector2_t speed);
void character_tick(character_t* character, double delta_time);

#endif