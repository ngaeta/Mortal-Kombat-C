#include "header/utility.h"
#include "header/sprite.h"
#include <string.h>
#include <stdlib.h>

/*
    @param sprite sprite to fill 
    @param sprite_rect sprite position/size on screen
*/
void sprite_init(sprite_t* sprite, SDL_Rect sprite_rect)
{
    sprite->x = sprite_rect.x;
    sprite->y = sprite_rect.y;
    sprite->sprite_rect = sprite_rect; 
    sprite->scale_multiplier = 1;   
    sprite->is_active=1;
    sprite->flip = SDL_FLIP_NONE;
}

int sprite_set_texture(SDL_Renderer* renderer, sprite_t* sprite, const char* file_name, SDL_Rect* texture_rect) 
{
    SDL_Texture* texture = load_texture(renderer, file_name);
    sprite->texture = texture;
    
    if(texture_rect) 
    {
        SDL_Log("Texture rect defined");
        sprite->texture_rect = *texture_rect;
    }
    else 
    {
        SDL_Log("Texture rect NOT defined");
        SDL_Rect texture_rect;
        SDL_QueryTexture(texture, NULL, NULL, &texture_rect.w, &texture_rect.h);
        texture_rect.x = texture_rect.y = 0;
        sprite->texture_rect = texture_rect;
    }
    
    return 0;
}

void sprite_draw(SDL_Renderer* renderer, sprite_t* sprite) 
{
    if(sprite->is_active)
    {
        sprite->sprite_rect.x = sprite->x;
        sprite->sprite_rect.y = sprite->y;                                                                      
        SDL_Rect new_sprite_rect = create_rect(sprite->x, sprite->y, sprite->sprite_rect.w * sprite->scale_multiplier, sprite->sprite_rect.h * sprite->scale_multiplier);
        SDL_RenderCopyEx(renderer, sprite->texture, &sprite->texture_rect, &new_sprite_rect, 0, NULL, sprite->flip);
    }
}

/*
    @param sprite sprite to flip
    @param flip_mode use (SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL);
*/
void sprite_flip(sprite_t* sprite, int flip_mode) 
{
    if(flip_mode >= 0 && flip_mode < 3)
        sprite->flip = flip_mode; 
}
