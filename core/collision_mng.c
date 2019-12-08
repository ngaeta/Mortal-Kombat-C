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
        
        for (size_t j = i+1 ; j < num_colliders; j++)
        {
            collider_t** second_collider = dynarray_get(collision_mng->colliders_list, j);

            if(SDL_HasIntersection(&(*first_collider)->rect, &(*second_collider)->rect)) 
            {
                (*first_collider)->on_collision_ptr(*first_collider, *second_collider);
                (*second_collider)->on_collision_ptr(*second_collider, *first_collider);
            }
        }
    }    
}

void collision_mng_add_collider(collision_mng* collision_mng, collider_t* collider) 
{
    collider_t** collider_ptr = dynarray_append(collision_mng->colliders_list);
    *collider_ptr = collider;

    collider_t* first_collider = dynarray_get(collision_mng->colliders_list, 0);
}