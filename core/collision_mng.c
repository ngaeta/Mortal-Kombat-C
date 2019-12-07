#include "header/collision_mng.h"

void collision_mng_init(collision_mng* collision_mng)
{
    collision_mng->colliders_list = dynarray_init(sizeof(collider_t*));
}

void collision_mng_tick(collision_mng* collision_mng)
{
    size_t num_colliders = dynarray_length(collision_mng->colliders_list);
    
    for (size_t i = 0; i < num_colliders; i++)
    {
        collider_t** first_collider = dynarray_get(collision_mng->colliders_list, i);
        SDL_Log("first rect= %d", (*first_collider)->rect.x);

        for (size_t j = i+1 ; j < num_colliders; j++)
        {
            collider_t** second_collider = dynarray_get(collision_mng->colliders_list, j);
            // SDL_Log("first rect= %d %d %d %d", first_collider->rect.x, first_collider->rect.y, first_collider->rect.w, first_collider->rect.h);
            // SDL_Log("second rect= %d %d %d %d", second_collider->rect.x, second_collider->rect.y, second_collider->rect.w, second_collider->rect.h);

            if(SDL_HasIntersection(&(*first_collider)->rect, &(*second_collider)->rect)) 
            {
                (*first_collider)->on_collision_ptr();
                (*second_collider)->on_collision_ptr();
            }
            else
            {
                //SDL_Log("No intersection");
            }    
        }
    }    
}

void collision_mng_add_collider(collision_mng* collision_mng, collider_t* collider) 
{
    collider_t** collider_ptr = dynarray_append(collision_mng->colliders_list);
    *collider_ptr = collider;

    collider_t* first_collider = dynarray_get(collision_mng->colliders_list, 0);
    SDL_Log("collider argument= %d", collider->rect.x);
    SDL_Log("collider in list= %d", (*collider_ptr)->rect.x);
}