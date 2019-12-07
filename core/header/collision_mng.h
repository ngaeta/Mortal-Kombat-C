#include "collider.h"
#include "dynarray.h"

typedef struct collision_mng
{
    dynarray_t* colliders_list;
} collision_mng;

void collision_mng_init(collision_mng* collision_mng);
void collision_mng_tick(collision_mng* collision_mng);
void collision_mng_add_collider(collision_mng* collision_mng, collider_t* collider);