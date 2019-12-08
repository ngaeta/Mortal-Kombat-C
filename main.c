#define SDL_MAIN_HANDLED  

#include "core/header/hero.h"
#include "core/header/collision_mng.h"

int main(int argc, char** args)
{
    if(SDL_Init(SDL_INIT_VIDEO)) 
    {
        SDL_Log("error initializing SDL2: %s", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("Game", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //before hero
    collision_mng collision_mng;
    collision_mng_init(&collision_mng);

    SDL_Rect sprite_rect;
    sprite_rect.x = 150;
    sprite_rect.y = 300;
    sprite_rect.w = 70;
    sprite_rect.h = 132;
    hero_t hero, hero2;
    hero_init(renderer, &hero, sprite_rect);
    sprite_rect.x *= 2;  //era *3
    hero_init(renderer, &hero2, sprite_rect);
    hero_flip_X(&hero2);

    collision_mng_add_collider(&collision_mng, &hero.collider);
    collision_mng_add_collider(&collision_mng, &hero2.collider);
    
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    double delta_time = 1;

    for(;;)
    {                    
        last = now;
        now = SDL_GetPerformanceCounter();

        delta_time = ((double)((now - last)* 1000) / SDL_GetPerformanceFrequency()) * 0.001;
		
        SDL_Event event;
        while(SDL_PollEvent(&event)) 
        {
            if(event.type == SDL_QUIT) 
            {
                SDL_Quit();
                return 0;
            }

            //all inputs
            hero_input(renderer, &hero, &event);
        }

        //all ticks
        hero_tick(&hero, delta_time);
        hero_tick(&hero2, delta_time);
        collision_mng_tick(&collision_mng);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //all draw
        hero_draw(renderer, &hero);
        hero_draw(renderer, &hero2);
        //sprite_draw(renderer, &sprite);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}