#include <stdlib.h>

typedef struct list_s
{
    int n;
    struct list_s *next;
} list_t;

/* Correctly appends a node and handles allocation failure. */
list_t *add_node_end(list_t *head, const int n)
{
    list_t *new_node = malloc(sizeof(*new_node));
    list_t *current;

    if (new_node == NULL)
        return (NULL);

    new_node->n = n;
    new_node->next = NULL;

    if (head == NULL)
        return (new_node);

    current = head;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;

    return (head);
}
