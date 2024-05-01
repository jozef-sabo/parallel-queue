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

queue_t *queue_glob;

int queue_init(queue_t **queue_ptr) {
    queue_t *new_queue = calloc(sizeof (queue_t), 1);
    if (new_queue == NULL) {
        return -1;
    }
    *queue_ptr = new_queue;
    return 0;
}

int queue_push(queue_t *queue, void* obj) {
    node_t *new_node = calloc(sizeof (node_t), 1);
    if (new_node == NULL) {
        return -1;
    }
    new_node->obj = obj;

    if (queue->head == NULL) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }

    return 0;
}

int queue_pop(queue_t *queue, void **poped) {
    if (queue->head == NULL) {
        return 1;
    }

    node_t *old_node = queue->head;
    if (queue->head == queue->tail) {  // only one element
        queue->head = NULL;
        queue->tail = NULL;

    } else {
        queue->head = old_node->next;
    }

    if (poped != NULL) {
        *poped = old_node->obj;
    }

    free(old_node);

    return 0;
}

bool queue_is_empty(queue_t *queue) { {
    return queue->head == NULL && queue->tail == NULL;
}

}

int queue_destroy(queue_t **queue_ptr) {
    while ((*queue_ptr)->head != NULL) {
        queue_pop(*queue_ptr, NULL);
    }
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

void* vlakno(void *) {
    int test_int = 3;
    int test_int_2 = 4;
    int test_int_3 = 5;
    int test_int_4 = 6;

    for (int i = 0; i < 2500000; ++i) {
        queue_push(queue_glob, &test_int);
        queue_push(queue_glob, &test_int_2);
        queue_push(queue_glob, &test_int_3);
        queue_push(queue_glob, &test_int_4);
        queue_push(queue_glob, &test_int_3);
        queue_push(queue_glob, &test_int_2);
    }
    printf("finished thread\n");

    pthread_exit(0);
}

int main(void) {


//    queue_t *queue;
    queue_init(&queue_glob);
    printf("%d\n", queue_is_empty(queue_glob));

    void *r;
    pthread_t p1,p2,p3, p4, p5, p6, p7,p8,p9, p10, p11, p12;
    pthread_create(&p1,0,vlakno,0);
    pthread_create(&p2,0,vlakno,0);
    pthread_create(&p3,0,vlakno,0);
    pthread_create(&p4,0,vlakno,0);
    pthread_create(&p5,0,vlakno,0);
    pthread_create(&p6,0,vlakno,0);
    pthread_create(&p7,0,vlakno,0);
    pthread_create(&p8,0,vlakno,0);
    pthread_create(&p9,0,vlakno,0);
    pthread_create(&p10,0,vlakno,0);
    pthread_create(&p11,0,vlakno,0);
    pthread_create(&p12,0,vlakno,0);
    pthread_join(p1,&r);
    pthread_join(p2,&r);
    pthread_join(p3,&r);
    pthread_join(p4,&r);
    pthread_join(p5,&r);
    pthread_join(p6,&r);
    pthread_join(p7,&r);
    pthread_join(p8,&r);
    pthread_join(p9,&r);
    pthread_join(p10,&r);
    pthread_join(p11,&r);
    pthread_join(p12,&r);

    printf("%d\n", queue_is_empty(queue_glob));

//    queue_print(queue);

    queue_destroy(&queue_glob);

    return 0;
}
