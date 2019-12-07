#include <stdint.h>

typedef struct dynarray
{
    size_t item_size;
    size_t size;
    void *data;
} dynarray_t;

dynarray_t *dynarray_init(size_t item_size);

void dynarray_destroy(dynarray_t *dynarray);

void* dynarray_append(dynarray_t *dynarray);

void* dynarray_get(dynarray_t *dynarray, size_t index);

int dynarray_remove(dynarray_t *dynarray, size_t index);

int dynarray_length(dynarray_t* dynarray);
