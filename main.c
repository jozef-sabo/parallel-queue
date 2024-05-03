#include <stdio.h>
#include <pthread.h>
#include "types.h"

#if defined(MONOTHREAD)
#include "queue_monothread.h"
#elif defined(LOCKFREE)
#include "queue_lockfree.h"
#elif defined(MUTEX)

#endif


#include "types.h"

queue_t *queue_glob;

void* vlakno(void *) {
    int test_int = 3;
    int test_int_2 = 4;
    int test_int_3 = 5;
    int test_int_4 = 6;

    for (int i = 0; i < 25000; ++i) {
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
//    pthread_create(&p3,0,vlakno,0);
//    pthread_create(&p4,0,vlakno,0);
//    pthread_create(&p5,0,vlakno,0);
//    pthread_create(&p6,0,vlakno,0);
//    pthread_create(&p7,0,vlakno,0);
//    pthread_create(&p8,0,vlakno,0);
//    pthread_create(&p9,0,vlakno,0);
//    pthread_create(&p10,0,vlakno,0);
//    pthread_create(&p11,0,vlakno,0);
//    pthread_create(&p12,0,vlakno,0);
    pthread_join(p1,&r);
    pthread_join(p2,&r);
//    pthread_join(p3,&r);
//    pthread_join(p4,&r);
//    pthread_join(p5,&r);
//    pthread_join(p6,&r);
//    pthread_join(p7,&r);
//    pthread_join(p8,&r);
//    pthread_join(p9,&r);
//    pthread_join(p10,&r);
//    pthread_join(p11,&r);
//    pthread_join(p12,&r);

    printf("%d\n", queue_is_empty(queue_glob));
    printf("Queue length: %llu\n", queue_size(queue_glob));

//    queue_print(queue);

    queue_destroy(&queue_glob);

    return 0;
}
