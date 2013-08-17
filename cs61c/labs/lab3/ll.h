#ifndef LL_H_
#define LL_H_

/* Circular doubly-linked list of strings.

   The first element of a list_t serves to represent the entire list.

   A NULL list_t represents an empty list.
   */

typedef struct list list_t;

const char *list_node_value(list_t *node);
list_t *list_first(list_t *list);
list_t *list_last(list_t *list);
list_t *list_next(list_t *node);
list_t *list_previous(list_t *node);

/* Insert value before 'node'. Return the new first element of the list. */
list_t *list_insert_before(list_t *list, list_t *node, const char *value);
/* Insert value at the end of the list. Returns the new first element of the list. */
list_t *list_append(list_t *list, const char *value);
/* Insert value at the beginning of the list. Returns the new last element of the list. */
list_t *list_prepend(list_t *list, const char *value);

/* Remove an element from the list. Return the new head of the list. */
list_t *list_remove(list_t *list, list_t *node);

/* Free a list entirely. */
void list_free(list_t *list);

/* Call a function for each element in the list. */
void list_foreach(list_t *list, void (*function)(const char *));

#endif
