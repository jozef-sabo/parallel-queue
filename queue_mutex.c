#ifdef MUTEX
#include "queue_mutex.h"

int queue_init(queue_t **queue_ptr) {
    queue_t *new_queue = NULL;

    new_queue = calloc(sizeof (queue_t), 1);
    if (new_queue == NULL) {
        goto destroy_init;
    }

    if (pthread_mutex_init(&(new_queue->mutex), NULL) != 0) {
        goto destroy_init;
    }

    *queue_ptr = new_queue;
    return 0;

destroy_init:
    free(new_queue);
    return -1;
}

int queue_push(queue_t *queue, void* obj) {
    node_t *new_node = calloc(sizeof (node_t), 1);
    if (new_node == NULL) {
        return -1;
    }
    new_node->obj = obj;

    pthread_mutex_lock(&queue->mutex);
    if (queue->head == NULL) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
    pthread_mutex_unlock(&queue->mutex);

    return 0;
}

int queue_pop(queue_t *queue, void **poped) {
    if (queue->head == NULL) {
        return 1;
    }

    pthread_mutex_lock(&queue->mutex);
    if (queue->head == NULL) {
        pthread_mutex_unlock(&queue->mutex);
        return 1;
    }

    node_t *old_node = queue->head;
    if (queue->head == queue->tail) {  // only one element
        queue->head = NULL;
        queue->tail = NULL;

    } else {
        queue->head = old_node->next;
    }
    pthread_mutex_unlock(&queue->mutex);

    if (poped != NULL) {
        *poped = old_node->obj;
    }

    free(old_node);

    return 0;
}

bool queue_is_empty(queue_t *queue) {
    return queue->head == NULL && queue->tail == NULL;
}

int queue_destroy(queue_t **queue_ptr) {
    while ((*queue_ptr)->head != NULL) {
        queue_pop(*queue_ptr, NULL);
    }

    pthread_mutex_destroy(&(*queue_ptr)->mutex);

    free(*queue_ptr);
    *queue_ptr = NULL;

    return 0;
}


void queue_print(queue_t *queue) {
    node_t *act_node = queue->head;

    printf("Queue at %p:", queue);

    while (act_node != NULL) {
        printf(" <- %d", *((int*) act_node->obj));
        act_node = act_node->next;
    }
    printf("\n");
}

unsigned long long queue_size(queue_t *queue) {
    node_t *act_node = queue->head;
    unsigned long long count = 0;

    while (act_node != NULL) {
        count++;
        act_node = act_node->next;
    }

    return count;
}
#endif