#include "dynarray.h"
#include "list.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int ret = -1;

    list_t* head = NULL;
    list_append(&head, 10);

    dynarray_t *dynarray_of_ints = dynarray_init(sizeof(int));
    if (!dynarray_of_ints)
        return -1;

    printf("size = %llu\n", dynarray_of_ints->size);

    int *first_value = dynarray_append(dynarray_of_ints);
    if (!first_value)
        goto destroy;

    *first_value = 100;

    printf("size = %llu\n", dynarray_of_ints->size);

    int *second_value = dynarray_append(dynarray_of_ints);
    if (!second_value)
        goto destroy;

    *second_value = 200;

    printf("size = %llu\n", dynarray_of_ints->size);

    int *value = dynarray_get(dynarray_of_ints, 1);
    if (!value)
        goto destroy;

    printf("value = %d\n", *value);

    dynarray_remove(dynarray_of_ints, 0);

    printf("value = %d\n", *value);

    ret = 0;

destroy:
    dynarray_destroy(dynarray_of_ints);
    return ret;
}