#include "header/match_mng.h"
#include "header/utility.h"

//It's a temp method to manage match, it's better use FSM or delegate methods
void match_mng_init(match_mng_t* match_mng, SDL_Renderer* renderer, hero_t* left_hero, hero_t* right_hero)
{
    match_mng->curr_state = START;
    match_mng->time_hide_labels = match_mng->curr_time = 2;

    sprite_t background;
    sprite_init(&background, create_rect(0, 0, 640, 480));
    SDL_Rect r= create_rect(80, 260, 710, 250);
    sprite_set_texture(renderer, &background, "Assets/background.png", &r);
    match_mng->background = background;

    sprite_t logo;
    sprite_init(&logo, create_rect(290, 40, 62, 57));
    sprite_set_texture(renderer, &logo, "Assets/UI/logo.png", NULL);
    match_mng->logo=logo;

    sprite_t round_text;
    sprite_init(&round_text, create_rect(290, 210, 67, 25));
    sprite_set_texture(renderer, &round_text, "Assets/UI/round.png", NULL);
    match_mng->round_textUI=round_text;

    sprite_t fight_text;
    sprite_init(&fight_text, create_rect(270, 210, 99, 33));
    sprite_set_texture(renderer, &fight_text, "Assets/UI/fight.png", NULL);
    match_mng->fight_textUI=fight_text;

    sprite_t finish_him_text;
    sprite_init(&finish_him_text, create_rect(235, 210, 182, 33));
    sprite_set_texture(renderer, &finish_him_text, "Assets/UI/finish.png", NULL);
    match_mng->finish_him_textUI=finish_him_text;

    sprite_t fatality_text;
    sprite_init(&fatality_text, create_rect(210, 250, 115, 29));
    sprite_set_texture(renderer, &fatality_text, "Assets/UI/fatality.png", NULL);
    fatality_text.is_active = 0;
    fatality_text.scale_multiplier=2;
    match_mng->fatality_textUI=fatality_text;

    sprite_t win_label;
    sprite_init(&win_label, create_rect(350, 218, 46, 19));
    sprite_set_texture(renderer, &win_label, "Assets/UI/wins_label.png", NULL);
    match_mng->win_label = win_label;
    
    left_hero->keycode_input[INPUT_WALK_LEFT] = SDL_SCANCODE_A;
    left_hero->keycode_input[INPUT_PUNCH] = SDL_SCANCODE_F;
    left_hero->keycode_input[INPUT_WALK_RIGHT] = SDL_SCANCODE_D;
    left_hero->keycode_input[INPUT_KICK] = SDL_SCANCODE_G;
    left_hero->keycode_input[INPUT_FATALITY] = SDL_SCANCODE_E;

    right_hero->keycode_input[INPUT_WALK_RIGHT] = SDL_SCANCODE_RIGHT;
    right_hero->keycode_input[INPUT_WALK_LEFT] = SDL_SCANCODE_LEFT;
    right_hero->keycode_input[INPUT_PUNCH] = SDL_SCANCODE_L;
    right_hero->keycode_input[INPUT_KICK] = SDL_SCANCODE_K;
    right_hero->keycode_input[INPUT_FATALITY] = SDL_SCANCODE_P;

    left_hero->rival = right_hero;
    right_hero->rival = left_hero;
    
    match_mng->left_hero = left_hero;
    match_mng->right_hero = right_hero;
}

//spaghetti code. It's better use FSM or delegate...
void match_mng_tick(match_mng_t* match_mng, float delta_time)
{
    if(match_mng->curr_state == START)
    {
        if(match_mng->curr_time < 0)
        {
            match_mng->curr_state = FIGHT;
            match_mng->curr_time = match_mng->time_hide_labels;
        }
        else
            match_mng->curr_time -= delta_time;  
    }
    else if(match_mng->curr_state == FIGHT)
    {
        if(match_mng->fight_textUI.is_active)
        {
            if(match_mng->curr_time < 0)
            {
                match_mng->fight_textUI.is_active= 0;
                match_mng->curr_time = match_mng->time_hide_labels;
            }
            else
                match_mng->curr_time -= delta_time;  
        }
        else if (match_mng->left_hero->health <= 0 || match_mng->right_hero->health <= 0)
        {
            match_mng->curr_state = FINISH_HIM;
        }
    }
    else if(match_mng->curr_state == FINISH_HIM)
    {
        if(match_mng->left_hero->curr_anim.name == FATALITY || match_mng->right_hero->curr_anim.name == FATALITY)
        {
            match_mng->finish_him_textUI.is_active = 0;
        }
        else if(match_mng->left_hero->curr_anim.name == WIN || match_mng->right_hero->curr_anim.name == WIN)
        {
            match_mng->curr_time = match_mng->time_hide_labels;
            match_mng->left_hero->hero_name.x = 255;
            match_mng->left_hero->hero_name.y = 215;
            match_mng->right_hero->hero_name.x = 255;
            match_mng->right_hero->hero_name.y = 215;
            match_mng->finish_him_textUI.is_active= 0;
            match_mng->curr_state = END;
        }
    }
    else if(match_mng->curr_state == END)
    {
        if(match_mng->curr_time < 0)
        {
            match_mng->fatality_textUI.is_active= 1;
        }
        else
            match_mng->curr_time -= delta_time;  
    }

    match_mng->left_hero->child_tick_ptr(match_mng->left_hero, delta_time);
    match_mng->right_hero->child_tick_ptr(match_mng->right_hero, delta_time);
}

void match_mng_input(match_mng_t* match_mng, SDL_Renderer* renderer, int num_keys_pressed, const Uint8* keys)
{
    if(match_mng->curr_state != START && match_mng->curr_state != END)
    {
        match_mng->left_hero->child_input_ptr(renderer, match_mng->left_hero, num_keys_pressed, keys);
        match_mng->right_hero->child_input_ptr(renderer, match_mng->right_hero, num_keys_pressed, keys);
    }
}

void match_mng_draw(match_mng_t* match_mng, SDL_Renderer* renderer)
{
    sprite_draw(renderer, &match_mng->background);
    sprite_draw(renderer, &match_mng->logo);

    if(match_mng->curr_state == START)
    {
        sprite_draw(renderer, &match_mng->round_textUI);
    }
    else if(match_mng->curr_state == FIGHT)
    {
        sprite_draw(renderer, &match_mng->fight_textUI);
    }
    else if(match_mng->curr_state == FINISH_HIM)
    {
        sprite_draw(renderer, &match_mng->finish_him_textUI);
    }
    else if(match_mng->curr_state == END)
    {
        if(match_mng->left_hero->curr_anim.name == WIN)
        {
            sprite_draw(renderer, &match_mng->left_hero->hero_name);
        }
        else
        {
            sprite_draw(renderer, &match_mng->right_hero->hero_name);
        }
        
        sprite_draw(renderer, &match_mng->win_label);
        sprite_draw(renderer, &match_mng->fatality_textUI);
    }
    
    hero_draw(renderer, match_mng->left_hero);
    hero_draw(renderer, match_mng->right_hero);
}


