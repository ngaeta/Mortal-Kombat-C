#define SDL_MAIN_HANDLED  

#include "header/hero.h"

int main(int argc, char** args)
{
    if(SDL_Init(SDL_INIT_VIDEO)) 
    {
        SDL_Log("error initializing SDL2: %s", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("Game", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Rect sprite_rect;
    sprite_rect.x = 0;
    sprite_rect.y = 0;
    sprite_rect.w = 50;
    sprite_rect.h = 112;

    hero_t hero;
    hero_init(renderer, &hero, &sprite_rect);
    //sprite_t sprite;
    //sprite_init(&sprite, &sprite_rect);
    //sprite_set_texture(renderer, &sprite, "Assets/Heroes/test.png", NULL);

    for(;;)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)) 
        {
            if(event.type == SDL_QUIT) 
            {
                SDL_Quit();
                return 0;
            }
        }

        hero_tick(&hero);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        hero_draw(renderer, &hero);
        //sprite_draw(renderer, &sprite);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}