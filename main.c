#define SDL_MAIN_HANDLED  

#include "core/header/collision_mng.h"
#include "core/header/input.h"
#include "core/header/scorpion.h"
#include "core/header/sub_zero.h"

int main(int argc, char** args)
{
    if(SDL_Init(SDL_INIT_VIDEO)) 
    {
        SDL_Log("error initializing SDL2: %s", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("Game", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //before scorpion
    collision_mng collision_mng;
    collision_mng_init(&collision_mng);

    SDL_Rect sprite_rect;
    sprite_rect.x = 120;
    sprite_rect.y = 320;
    sprite_rect.w = 100;
    sprite_rect.h = 150;

    hero_t scorpion, sub_zero;
    scorpion_hero_init(renderer, &scorpion, sprite_rect, Player_One);
    scorpion.keycode_input[INPUT_WALK_RIGHT] = SDL_SCANCODE_D;
    scorpion.keycode_input[INPUT_WALK_LEFT] = SDL_SCANCODE_A;
    scorpion.keycode_input[INPUT_PUNCH] = SDL_SCANCODE_F;
    scorpion.keycode_input[INPUT_KICK] = SDL_SCANCODE_G;
    scorpion.keycode_input[INPUT_FATALITY] = SDL_SCANCODE_E;

    sprite_rect.x = 440;  
    sub_zero_hero_init(renderer, &sub_zero, sprite_rect, Player_Two);
    sub_zero.keycode_input[INPUT_WALK_RIGHT] = SDL_SCANCODE_RIGHT;
    sub_zero.keycode_input[INPUT_WALK_LEFT] = SDL_SCANCODE_LEFT;
    sub_zero.keycode_input[INPUT_PUNCH] = SDL_SCANCODE_L;
    sub_zero.keycode_input[INPUT_KICK] = SDL_SCANCODE_K;
    sub_zero.keycode_input[INPUT_FATALITY] = SDL_SCANCODE_P;
    
    scorpion.rival = &sub_zero;
    sub_zero.rival = &scorpion;

    sprite_t background;
    sprite_init(&background, create_rect(0, 0, 640, 480));
    SDL_Rect r= create_rect(80, 260, 710, 250);
    sprite_set_texture(renderer, &background, "Assets/background.png", &r);

    collision_mng_add_collider(&collision_mng, &scorpion.collider);
    collision_mng_add_collider(&collision_mng, &sub_zero.collider);
    
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

            int num_keys_pressed;
            const Uint8* keys_pressed = get_button_pressed(&num_keys_pressed);

            //all inputs
            scorpion_hero_input(renderer, &scorpion, num_keys_pressed, keys_pressed);
            sub_zero_hero_input(renderer, &sub_zero, num_keys_pressed, keys_pressed);
        }

        //all ticks
        scorpion_hero_tick(&scorpion, delta_time);
        sub_zero_hero_tick(&sub_zero, delta_time);
        collision_mng_tick(&collision_mng);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //all draw
        sprite_draw(renderer, &background);
        sub_zero_hero_draw(renderer, &sub_zero);
        scorpion_hero_draw(renderer, &scorpion);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}