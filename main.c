#include <stdio.h>
#include <pthread.h>

#if defined(MONOTHREAD)
#include "queue_monothread.h"
#elif defined(LOCKFREE)
#include "queue_lockfree.h"
#elif defined(MUTEX)
#include "queue_mutex.h"
#endif

queue_t *queue_glob;

void push_elements(int number) {
    int test_int = 3;
    for (int i = 0; i < number; ++i) {
        queue_push(queue_glob, &test_int);
    }
}

void* push_thread(void *handle) {
    push_elements(30000);
//    printf("finished thread\n");
    return NULL;
}

void* pop_thread(void *handle) {

    for (int i = 0; i < 50000; ++i) {
        queue_pop(queue_glob, NULL);
    }
    return NULL;
}

int main(void) {


//    queue_t *queue;
    queue_init(&queue_glob);
//    printf("%d\n", queue_is_empty(queue_glob));

    void *r;
    pthread_t p1_pop,p2_pop,p3_pop, p4_pop, p5_pop, p6_pop, p7_pop,p8_pop,p9_pop, p10_pop, p11_pop, p12_pop;
    pthread_t p1_push,p2_push,p3_push, p4_push, p5_push, p6_push, p7_push,p8_push,p9_push, p10_push, p11_push, p12_push;
    push_elements(150000);

    pthread_create(&p1_push, 0, push_thread, 0);
    pthread_create(&p1_pop, 0, pop_thread, 0);

    pthread_create(&p2_push, 0, push_thread, 0);
    pthread_create(&p2_pop, 0, pop_thread, 0);


    pthread_create(&p3_push, 0, push_thread, 0);
    pthread_create(&p4_push, 0, push_thread, 0);
    pthread_create(&p3_pop, 0, pop_thread, 0);
    pthread_create(&p4_pop, 0, pop_thread, 0);

    pthread_create(&p5_push, 0, push_thread, 0);
    pthread_create(&p5_pop, 0, pop_thread, 0);
    pthread_create(&p6_pop, 0, pop_thread, 0);
    pthread_create(&p7_pop, 0, pop_thread, 0);
    pthread_create(&p8_pop, 0, pop_thread, 0);

    pthread_create(&p6_push, 0, push_thread, 0);
    pthread_create(&p7_push, 0, push_thread, 0);
    pthread_create(&p8_push, 0, push_thread, 0);
    pthread_create(&p9_push, 0, push_thread, 0);
    pthread_create(&p10_push, 0, push_thread, 0);
    pthread_create(&p11_push, 0, push_thread, 0);
    pthread_create(&p12_push, 0, push_thread, 0);
    pthread_create(&p9_pop, 0, pop_thread, 0);
    pthread_create(&p10_pop, 0, pop_thread, 0);
    pthread_create(&p11_pop, 0, pop_thread, 0);
    pthread_create(&p12_pop, 0, pop_thread, 0);

    pthread_join(p1_pop, &r);
    pthread_join(p2_pop, &r);
    pthread_join(p3_pop, &r);
    pthread_join(p4_pop, &r);
    pthread_join(p5_pop, &r);
    pthread_join(p6_pop, &r);
    pthread_join(p7_pop, &r);
    pthread_join(p8_pop, &r);
    pthread_join(p9_pop, &r);
    pthread_join(p10_pop, &r);
    pthread_join(p11_pop, &r);
    pthread_join(p12_pop, &r);

    pthread_join(p1_push, &r);
    pthread_join(p2_push, &r);
    pthread_join(p3_push, &r);
    pthread_join(p4_push, &r);
    pthread_join(p5_push, &r);
    pthread_join(p6_push, &r);
    pthread_join(p7_push, &r);
    pthread_join(p8_push, &r);
    pthread_join(p9_push, &r);
    pthread_join(p10_push, &r);
    pthread_join(p11_push, &r);
    pthread_join(p12_push, &r);



//    printf("%d\n", queue_is_empty(queue_glob));
//    printf("Queue length: %llu\n", queue_size(queue_glob));

//    queue_print(queue);

    queue_destroy(&queue_glob);

    return 0;
}
