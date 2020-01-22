#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>

typedef struct sprite 
{
    int x;
    int y;
    int scale_multiplier;
    int is_active;
    SDL_Texture* texture;
    SDL_Rect sprite_rect;
    SDL_Rect texture_rect;
    SDL_RendererFlip flip;
} sprite_t;

void sprite_init(sprite_t* sprite, SDL_Rect sprite_rect);
int sprite_set_texture(SDL_Renderer* renderer, sprite_t* sprite, const char* file_name, SDL_Rect* texture_rect);
void sprite_draw(SDL_Renderer* renderer, sprite_t* sprite);
void sprite_flip(sprite_t* sprite, int flip_mode);

#endif
