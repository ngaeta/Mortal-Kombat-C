#include "list.h"

list_t *list_append(list_t **list, size_t item_size)
{
    list_t *new_list;
    if (!*list)
    {
        *list = malloc(sizeof(list_t));
        new_list = *list;
    }
    else
    {
        list_t * current_list = *list;
        while (current_list->next)
        {
            current_list = current_list->next;
        }
        current_list->next = malloc(sizeof(list_t));
        new_list = current_list->next;
    }

    new_list->data = malloc(item_size);
    new_list->next = NULL;
    return new_list;
}