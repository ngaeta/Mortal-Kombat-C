#include "header/dynarray.h"
#include <string.h>
#include <stdlib.h>

dynarray_t *dynarray_init(size_t item_size)
{
    dynarray_t *new_dynarray = malloc(sizeof(dynarray_t));
    if (!new_dynarray)
        return NULL;

    new_dynarray->item_size = item_size;
    new_dynarray->size = 0;
    new_dynarray->data = NULL;

    return new_dynarray;
}

void dynarray_destroy(dynarray_t *dynarray)
{
    if (dynarray->data)
    {
        free(dynarray->data);
    }
    free(dynarray);
}

void *dynarray_append(dynarray_t *dynarray)
{
    dynarray->size++;
    if (!dynarray->data)
    {
        dynarray->data = malloc(dynarray->item_size * dynarray->size);
        if (!dynarray->data)
        {
            return NULL;
        }
    }
    else
    {
        void *new_data = realloc(dynarray->data, dynarray->item_size * dynarray->size);
        if (new_data)
        {
            dynarray->data = new_data;
        }
        else
        {
            return NULL;
        }
    }

    unsigned char *raw_data = dynarray->data;

    return raw_data + (dynarray->item_size * (dynarray->size - 1));
}

void *dynarray_get(dynarray_t *dynarray, size_t index)
{
    if (index >= dynarray->size)
        return NULL;

    unsigned char *raw_data = dynarray->data;

    return raw_data + (dynarray->item_size * index);
}

int dynarray_remove(dynarray_t *dynarray, size_t index)
{
    if (index >= dynarray->size)
        return -1;

    unsigned char *new_data = malloc(dynarray->item_size * (dynarray->size - 1));
    unsigned char *old_data = dynarray->data;

    size_t j = 0; // j is the pointer in the current index of new_data array
    for (size_t i = 0; i < dynarray->size; i++)
    {
        if (i == index)
            continue;
        memcpy(new_data + (j * dynarray->item_size), new_data + (i * dynarray->item_size), dynarray->item_size);
        j++;
    }

    free(old_data);
    dynarray->data = new_data;
    dynarray->size--;

    return -1;
}

int dynarray_length(dynarray_t* dynarray)
{
    return dynarray->size;
}