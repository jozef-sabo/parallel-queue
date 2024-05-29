#ifndef IB109_QUEUE_MONOTHREAD_H
#define IB109_QUEUE_MONOTHREAD_H

#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <stdbool.h>

struct node_t {
    void *obj;
    struct node_t *next;
} typedef node_t;

struct queue_t {
    node_t *head;
    node_t* tail;
} typedef queue_t;

unsigned long long queue_size(queue_t*);
int queue_init(queue_t**);
int queue_push(queue_t*, void*);
int queue_pop(queue_t*, void **);
bool queue_is_empty(queue_t*);
int queue_destroy(queue_t**);
void queue_print(queue_t*);


#endif //IB109_QUEUE_MONOTHREAD_H
