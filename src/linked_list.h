#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct _node node_t;
struct _node {
    void *data;
    node_t *next;
};

node_t *create_node(void *data);
void free_node(node_t *node);

typedef struct _linked_list {
    node_t *head;
    node_t *tail;
    size_t size;
} linked_list_t;

linked_list_t *create_linked_list();
void free_linked_list(linked_list_t *list);
void add_to_linked_list(linked_list_t *list, void *data);

#endif /* LINKED_LIST_H */