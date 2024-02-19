#ifndef LIBAPRIL_LINKED_LIST_H
#define LIBAPRIL_LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct april_ll_node_s {
    void *data;
    struct april_ll_node_s *prev_node;
    struct april_ll_node_s *next_node;
} april_ll_node;

typedef struct {
    april_ll_node *start_node;
    april_ll_node *end_node;
    size_t size;
} april_ll;

typedef struct {
    april_ll *ll;
    april_ll_node *node;
    size_t index;
    april_ll_node *next_node;
    april_ll_node *prev_node;
} april_ll_iter;

april_ll *april_ll_init();

void april_ll_deinit(april_ll *ll);

size_t april_ll_get_size(april_ll *ll);

bool april_ll_is_empty(april_ll *ll);

void april_ll_add(april_ll *ll, void *data);

void april_ll_add_at(april_ll *ll, size_t index, void *data);

void *april_ll_remove(april_ll *ll);

void *april_ll_remove_at(april_ll *ll, size_t index);

///
/// iteration
///

void april_ll_iter_init(april_ll *ll, april_ll_iter *iter);

size_t april_ll_iter_get_index(april_ll_iter *iter);

bool april_ll_iter_has_next(april_ll_iter *iter);

void *april_ll_iter_next(april_ll_iter *iter);

bool april_ll_iter_has_prev(april_ll_iter *iter);

void *april_ll_iter_prev(april_ll_iter *iter);

void *april_ll_iter_remove(april_ll_iter *iter);

void april_ll_iter_add(april_ll_iter *iter, void *data);

#endif // LIBAPRIL_LINKED_LIST_H
