#define STB_IMAGE_IMPLEMENTATION

#include "header/utility.h"
#include "stb_image.h"
#include <string.h>

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file_name) 
{
    int width, height, channel;
    unsigned char* image = stbi_load(file_name, &width, &height, &channel, 4);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    Uint8 *pixels = NULL;
    int pitch=0;   
    if(SDL_LockTexture(texture, NULL, (void**) &pixels, &pitch))
    {
        return NULL;
    }    
    
    memcpy(pixels, image, pitch * height);
    free(image);
    SDL_UnlockTexture(texture);
    return texture;
}

SDL_Rect create_rect(int x, int y, int w, int h) 
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    return rect;
}