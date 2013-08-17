#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ll.h"

static int print_index = 0;
static void print_element(const char *value) {
    printf("%d:%s   ", print_index++, value);
}

static void print_list(list_t *list, const char *label) {
    print_index = 0;
    printf("%s: ", label);
    list_foreach(list, print_element);
    printf("\n");
}

int main(int argc, const char **argv) {
    list_t *list = NULL;

    /* This test appears to work correctly: */
    list = list_prepend(list, "fourth");
    list = list_prepend(list, "third");
    list = list_prepend(list, "second");
    list = list_prepend(list, "first");

    print_list(list, "Initially");

    list_t *second = list_next(list_first(list));
    list_t *third = list_next(second);
    list = list_insert_before(list, second, "before second");
    list = list_remove(list, list_previous(list_previous(second)));
    list = list_insert_before(list, third, "new third");
    list = list_remove(list, third);
    list = list_append(list, "fifth");

    print_list(list, "After manipulations");

    list_free(list);
    printf("----\n");

    /* This second test appears not to work correctly: */
    list = NULL;

    list = list_append(list, "First Test Value");
    list = list_append(list, "Second Test Value");
    list = list_append(list, "Third Test Value");
   
    print_list(list, "Second list");
    list_free(list);
    printf("----\n");

    /* This third test crashes: */
    list = NULL;
    for (int i = 0; i < 1000000; ++i) {
        list = list_append(list, "Some Test Value");
    }
    for (int i = 0; i < 100000; ++i) {
        list = list_remove(list, list_first(list));
    }
    list_free(list);

    return EXIT_SUCCESS;
}
