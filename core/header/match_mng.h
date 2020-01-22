#include "hero.h"

enum Match_state {START, FIGHT, FINISH_HIM, END};

typedef struct  match_mng
{
    enum Match_state curr_state;
    hero_t* left_hero;
    hero_t* right_hero;
    sprite_t background, logo;
    sprite_t round_textUI, fight_textUI;
    sprite_t finish_him_textUI;
    sprite_t win_label;
    sprite_t fatality_textUI;
    float time_hide_labels;
    float curr_time;
} match_mng_t;

void match_mng_init(match_mng_t* match_mng, SDL_Renderer* renderer, hero_t* left_hero, hero_t* right_hero);  //assign character
void match_mng_input(match_mng_t* match_mng, SDL_Renderer* renderer, int num_keys_pressed, const Uint8* keys);
void match_mng_tick(match_mng_t* match_mng, float delta_time);
void match_mng_draw(match_mng_t* match_mng, SDL_Renderer* renderer);
