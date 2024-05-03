#define LOCKFREE

#ifndef IB109_TYPES_H
#define IB109_TYPES_H

struct node_t {
    void *obj;
    struct node_t *next;
} typedef node_t;

struct queue_t {
    node_t *head;
    node_t* tail;
} typedef queue_t;

#endif //IB109_TYPES_H
