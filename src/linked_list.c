#include "linked_list.h"

#include <stdlib.h>

node_t *create_node(void *data)
{
    node_t *node = malloc(sizeof(node_t));
    if( !node )
        return NULL;

    node->data = data;
    node->next = NULL;
    return node;
}

void free_node(node_t *node)
{
    if( node )
        free(node);
}

linked_list_t *create_linked_list()
{
    linked_list_t *list = malloc(sizeof(linked_list_t));
    if( !list )
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void free_linked_list(linked_list_t *list)
{
    if( list )
        free(list);
}

void add_to_linked_list(linked_list_t *list, void *data)
{
    if( !list )
        return;

    node_t *node = create_node(data);
    if( !node )
        return;

    if( list->tail )
        list->tail->next = node;
    list->tail = node;

    if( !list->head )
        list->head = node;

    list->size++;
}
