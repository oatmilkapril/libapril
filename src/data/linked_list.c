#include <malloc.h>
#include <assert.h>
#include <stdbool.h>
#include "april/data/linked_list.h"

april_ll *april_ll_init() {
    april_ll *ll = (april_ll *) malloc(sizeof(april_ll));
    ll->start_node = NULL;
    ll->end_node = NULL;
    ll->size = 0;
    return ll;
}

void april_ll_deinit(april_ll *ll) {
    if (ll->size >= 0) {
        april_ll_node *node = ll->start_node;
        while (node != NULL) {
            struct april_ll_node_s *next_node = node->next_node;
            free(node);
            node = next_node;
        }
    }
}

size_t april_ll_get_size(april_ll *ll) {
    assert(ll != NULL);
    return ll->size;
}

bool april_ll_is_empty(april_ll *ll) {
    assert(ll != NULL);
    return ll->size == 0;
}

void april_ll_add(april_ll *ll, void *data) {
    assert(ll != NULL);

    april_ll_node *node = (april_ll_node *) malloc(sizeof(april_ll_node));
    node->data = data;

    if (april_ll_is_empty(ll)) {
        ll->start_node = node;
        ll->end_node = node;
        ll->size++;
        return;
    }

    ll->end_node->next_node = node;
    node->prev_node = ll->end_node;
    node->next_node = NULL;
    ll->end_node = node;
    ll->size++;
}

void april_ll_add_at(april_ll *ll, size_t index, void *data) {
    assert(ll != NULL);

    // append if index outside of list
    if (index >= ll->size) {
        april_ll_add(ll, data);
        return;
    }

    // find node to evict
    april_ll_node *node = ll->start_node;
    for (size_t i = 0; i < index; i++) {
        assert(node != NULL); // assertion valid given above size check
        node = node->next_node;
    }

    april_ll_node *new_node = (april_ll_node *) malloc(sizeof(april_ll_node));
    new_node->data = data;
    new_node->prev_node = node->prev_node;
    new_node->next_node = node;

    if (node->prev_node != NULL) { // evicted node isn't start node
        node->prev_node->next_node = new_node;
    } else { // evicted node is start node
        ll->start_node = new_node;
    }
    node->prev_node = new_node;

    ll->size++;
}

void *april_ll_remove(april_ll *ll) {
    assert(ll != NULL);

    if (april_ll_is_empty(ll)) {
        return NULL;
    }

    april_ll_node *end_node = ll->end_node;

    april_ll_node *new_end_node = end_node->prev_node;
    if (new_end_node != NULL) {
        new_end_node->next_node = NULL;
    }

    ll->end_node = new_end_node;
    ll->size--;

    void *data = end_node->data;
    free(end_node);
    return data;
}

void *april_ll_remove_at(april_ll *ll, size_t index) {
    assert(ll != NULL);

    // node with given index not in list
    if (index >= ll->size) {
        return NULL;
    }

    // find node to remove
    april_ll_node *node = ll->start_node;
    for (size_t i = 0; i < index; i++) {
        assert(node != NULL); // assertion valid given above size check
        node = node->next_node;
    }

    // update previous node
    if (node->prev_node != NULL) { // removed node isn't start node
        node->prev_node->next_node = node->next_node;
    } else {
        ll->start_node = node->next_node;
    }

    // update next node
    if (node->next_node != NULL) { // removed node isn't end node
        node->next_node->prev_node = node->prev_node;
    } else {
        ll->end_node = node->prev_node;
    }

    ll->size--;

    void *data = node->data;
    free(node);
    return data;
}


///
/// iteration
///

// this should parallel listiterator
// todo: clarify functions that break when element removed

void april_ll_iter_init(april_ll *ll, april_ll_iter *iter) {
    iter->ll = ll;
    iter->node = NULL;
    iter->index = -1;
    iter->next_node = ll->start_node;
}

size_t april_ll_iter_get_index(april_ll_iter *iter) {
    assert(iter != NULL);

    return iter->index;
}

bool april_ll_iter_has_next(april_ll_iter *iter) {
    assert(iter != NULL);

    return iter->next_node != NULL;
}

void *april_ll_iter_next(april_ll_iter *iter) {
    assert(iter != NULL);

    iter->node = iter->next_node;
    iter->prev_node = iter->node->prev_node;
    iter->next_node = iter->node->next_node;
    iter->index++;

    return iter->node->data;
}

bool april_ll_iter_has_prev(april_ll_iter *iter) {
    assert(iter != NULL);

    return iter->prev_node != NULL;
}

void *april_ll_iter_prev(april_ll_iter *iter) {
    assert(iter != NULL);

    iter->node = iter->prev_node;
    iter->prev_node = iter->node->prev_node;
    iter->next_node = iter->node->next_node;
    iter->index--;

    return iter->node->data;
}

void *april_ll_iter_remove(april_ll_iter *iter) {
    assert(iter != NULL && iter->node != NULL);

    april_ll_node *next_node = iter->node->next_node;
    april_ll_node *prev_node = iter->node->prev_node;

    if (next_node != NULL) {
        next_node->prev_node = iter->prev_node;
    }

    if (prev_node != NULL) {
        prev_node->next_node = iter->next_node;
    }

    void *data = iter->node->data;
    free(iter->node);
    iter->node = NULL;
    iter->index--;
    return data;
}

void april_ll_iter_add(april_ll_iter *iter, void *data) {
    assert(iter != NULL);

    april_ll_node *new_node = (april_ll_node *) malloc(sizeof(april_ll_node));
    new_node->data = data;
    new_node->prev_node = iter->prev_node;
    new_node->next_node = iter->next_node;

    iter->node->prev_node = new_node;
    iter->prev_node = new_node;

    iter->ll->size++;
}
