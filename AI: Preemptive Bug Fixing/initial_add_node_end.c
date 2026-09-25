#include <stdlib.h>

typedef struct list_s
{
    int n;
    struct list_s *next;
} list_t;

/* Vulnerable implementation supplied for review. */
list_t *add_node_end(list_t *head, const int n)
{
    list_t *new_node = malloc(sizeof(list_t));
    list_t *current = head;

    if (!head)
        return (new_node);
    while (current)
        current = current->next;
    current = new_node;
    new_node->n = n;
    new_node->next = NULL;
    return (head);
}
