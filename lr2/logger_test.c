#include "logger.h"
#include <unistd.h>
#include <stdlib.h>


void* test_logging(void* arg) {
    int priority = *(int*)arg;
    int i;
    for (i = 0; i < 5; ++i) {
        LOG_MESSAGE("Сообщение с приоритетом", priority);
        sleep(1);
    }
    free(arg);
    return NULL;
}

int main() {
    configure_logging(LOG_CONSOLE);
    start_logging();

    pthread_t threads[4];
    int priorities[4] = {16, 20, 16, 20};
    struct sched_param param;
    pthread_attr_t attr;
    int i;

    for (i = 0; i < 4; ++i) {
        int *priority = malloc(sizeof(int));
        *priority = priorities[i];
        pthread_attr_init(&attr);
        param.sched_priority = *priority;
        pthread_attr_setschedparam(&attr, &param);
        if (*priority == 16) {
            pthread_attr_setschedpolicy(&attr, SCHED_RR);
        } else {
            pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
        }
        pthread_create(&threads[i], &attr, test_logging, priority);
        pthread_attr_destroy(&attr);
    }

    // Ожидание завершения всех потоков
    for (i = 0; i < 4; ++i) {
        pthread_join(threads[i], NULL);
    }

    finish_logging();
    return 0;
}
