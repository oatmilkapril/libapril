#include <stdio.h>
#include <stdlib.h>
#include <april/data/linked_list.h>

void print_list(april_ll *ll) {
    april_ll_iter iter;
    april_ll_iter_init(ll, &iter);
    printf("\n\nprinting linked list...\n");
    while(april_ll_iter_has_next(&iter)) {
        long *data = (long *) april_ll_iter_next(&iter);

        size_t index = april_ll_iter_get_index(&iter);
        printf("data at index %zu: %ld\n", index, *data);
    }
    printf("stop! reverse...\n");
    while(april_ll_iter_has_prev(&iter)) {
        long *data = (long *) april_ll_iter_prev(&iter);

        size_t index = april_ll_iter_get_index(&iter);
        printf("data at index %zu, %ld\n", index, *data);
    }
    printf("\n\n");
}

int main() {
    long data1 = 1;
    long data2 = 2;
    long data3 = 3;

    april_ll *ll = april_ll_init();
    april_ll_add(ll, &data1);
    april_ll_add_at(ll, 0, &data2);
    april_ll_add(ll, &data3);

    print_list(ll);

    long *data = april_ll_remove_at(ll, 0);
    printf("removed %ld at index 0\n", *data);

    data = april_ll_remove_at(ll, 1);
    printf("removed %ld at index 1\n", *data);

    april_ll_add_at(ll, 0, &data3);
    printf("added %ld at index 0\n", data3);

    april_ll_add_at(ll, 2, &data2);
    printf("added %ld at index 2\n", data2);

    print_list(ll);

    april_ll_deinit(ll);

    exit(EXIT_SUCCESS);
}

