#include "header/input.h"

const Uint8* get_button_pressed(int* num_button_pressed)
{
    int keys_size = 0;
    const Uint8* keys_pressed = SDL_GetKeyboardState(&keys_size); 

    *num_button_pressed=0;     
    for (size_t i = 0; i < keys_size; i++)
    {
        *num_button_pressed+= keys_pressed[i];
    }

    return keys_pressed;
}
