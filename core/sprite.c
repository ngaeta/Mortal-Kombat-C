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
}

int sprite_set_texture(SDL_Renderer* renderer, sprite_t* sprite, const char* file_name, SDL_Rect* texture_rect) 
{
    SDL_Texture* texture = load_texture(renderer, file_name);
    sprite->texture = texture;
    
    //modify
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
    sprite->sprite_rect.x = sprite->x;
    sprite->sprite_rect.y = sprite->y;
    //SDL_Log("%d", sprite->x);                                                                            
    SDL_RenderCopy(renderer, sprite->texture, &sprite->texture_rect, &sprite->sprite_rect);
}
