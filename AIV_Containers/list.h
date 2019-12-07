#include <stdint.h>

typedef struct list
{
    void *data;
    struct list *next;
} list_t;

list_t *list_append(list_t** list, size_t item_size);