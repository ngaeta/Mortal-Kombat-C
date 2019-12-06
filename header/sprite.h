#include <SDL.h>

typedef struct sprite 
{
    int x;
    int y;
    SDL_Texture* texture;
    SDL_Rect sprite_rect;
    SDL_Rect texture_rect;
} sprite_t;

void sprite_init(sprite_t* sprite, SDL_Rect sprite_rect);
int sprite_set_texture(SDL_Renderer* renderer, sprite_t* sprite, const char* file_name, SDL_Rect texture_rect);
void sprite_draw(SDL_Renderer* renderer, sprite_t* sprite);
