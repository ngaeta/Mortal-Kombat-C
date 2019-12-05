#define STB_IMAGE_IMPLEMENTATION

#include "../header/sprite.h"
#include "stb_image.h"
#include <stdlib.h>
#include <string.h>

/*
    @param sprite sprite to fill 
    @param sprite_rect sprite position/size on screen
*/
void sprite_init(sprite_t* sprite, SDL_Rect* sprite_rect)
{
    sprite->x = sprite_rect->x;
    sprite->y = sprite_rect->y;
    sprite->sprite_rect = sprite_rect;    
}

int sprite_set_texture(SDL_Renderer* renderer, sprite_t* sprite, const char* file_name, SDL_Rect* texture_rect) 
{
    int width, height, channel;
    unsigned char* image = stbi_load(file_name, &width, &height, &channel, 4);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);
    Uint8 *pixels = NULL;
    int pitch=0;   
    if(SDL_LockTexture(texture, NULL, (void**) &pixels, &pitch))
    {
        return -1;
    }
    sprite->texture = texture;
    
    if(texture_rect) 
    {
        SDL_Log("Texture rect defined");
        sprite->texture_rect = texture_rect;
    }
    else 
    {
        SDL_Log("Texture rect NOT defined");
        SDL_Rect texture_rect;
        SDL_QueryTexture(texture, NULL, NULL, &texture_rect.w, &texture_rect.h);
        texture_rect.x = texture_rect.y = 0;
        sprite->texture_rect = &texture_rect;
    }
    
    memcpy(pixels, image, pitch * height);
    free(image);
    SDL_UnlockTexture(texture);
    return 0;
}

void sprite_draw(SDL_Renderer* renderer, sprite_t* sprite) 
{
    SDL_RenderCopy(renderer, sprite->texture, sprite->texture_rect, sprite->sprite_rect);
}
