#ifdef LOCKFREE

#include "queue_lockfree.h"
#include "stdatomic.h"
#include "pthread.h"

int queue_init(queue_t **queue_ptr) {
    queue_t *new_queue = calloc(sizeof(queue_t), 1);
    if (new_queue == NULL) {
        return -1;
    }

    void *dummy_element = calloc(sizeof(node_t), 1);
    if (dummy_element == NULL) {
        free(new_queue);
        return -1;
    }

    *queue_ptr = new_queue;
    new_queue->head = dummy_element;
    new_queue->tail = new_queue->head;

    return 0;
}

int queue_push(queue_t *queue, void *obj) {
    node_t *new_node = calloc(sizeof(node_t), 1);
    if (new_node == NULL) {
        return -1;
    }
    new_node->obj = obj;

    node_t *tail_node;

    while (true) {
        tail_node = queue->tail;

        if (__sync_bool_compare_and_swap(&(queue->tail), tail_node,
                                             new_node)) {
            if (__sync_bool_compare_and_swap(&(tail_node->next), NULL, new_node)) {
                break;
            }
        }

    }

    return 0;
}

int queue_pop(queue_t *queue, void **poped) {
    node_t *dummy_node;
    node_t *old_node;
    void *content;

    while (true) {
        dummy_node = queue->head;
        old_node = dummy_node->next;
        if (queue->head == queue->tail) {  //dummy element
            return 1;
        }

        if (__sync_bool_compare_and_swap(&(queue->head), dummy_node, old_node)) {
            content = old_node->obj;
            break;
        }
    }

    if (poped != NULL) {
        *poped = content;
    }

    free(dummy_node);

    return 0;
}

bool queue_is_empty(queue_t *queue) {
    return (queue->head == queue->tail);
}

int queue_destroy(queue_t **queue_ptr) {
    while (!queue_is_empty(*queue_ptr)) {
        queue_pop(*queue_ptr, NULL);
    }
    free((*queue_ptr)->head);
    free(*queue_ptr);
    *queue_ptr = NULL;

    return 0;
}


void queue_print(queue_t *queue) {
    node_t *act_node = queue->head->next;

    printf("Queue at %p:", queue);

    while (act_node != NULL) {
        printf(" <- %d", *((int *) act_node->obj));
        act_node = act_node->next;
    }
    printf("\n");
}

unsigned long long queue_size(queue_t *queue) {
    node_t *act_node = queue->head->next;
    unsigned long long count = 0;

    while (act_node != NULL) {
        count++;
        act_node = act_node->next;
    }

    return count;
}

#endif