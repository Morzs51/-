#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include "logger.h"

#define SEC_NSEC 1000000000LL

void *long_thread(void *notused)
{
    int time;
    char message[256];
    time = 25;
    snprintf(message, sizeof(message), "этот поток выполняется %d секунд", time);
    LOG_MESSAGE(message, 1);
    sleep(time);
}

int main(void)
{
    uint64_t timeout;
    struct sigevent event;
    int rval;
    char message[256];
    pthread_t thread_id;
    configure_logging(LOG_CONSOLE);
    start_logging();
    LOG_MESSAGE("Morozov i903b", 1); 

    event.sigev_notify = SIGEV_UNBLOCK;
    pthread_create(&thread_id, NULL, long_thread, NULL);

    timeout = 10LL * SEC_NSEC;
    TimerTimeout(CLOCK_REALTIME, _NTO_TIMEOUT_JOIN, &event, &timeout, NULL);
    rval = pthread_join(thread_id, NULL);
    printf("Значение rval: %d\n", rval);
    printf("Значение ETIMEDOUT: %d\n", ETIMEDOUT);
    if (rval == ETIMEDOUT)
    {   
        snprintf(message, sizeof(message), "истекли 10 секунд поток %d выполняется!!!", thread_id);
        LOG_MESSAGE(message, 1);
    }
    sleep(5);
    TimerTimeout(CLOCK_REALTIME, _NTO_TIMEOUT_JOIN, &event, &timeout, NULL);
    rval = pthread_join(thread_id, NULL);
    printf("Значение rval: %d\n", rval);
    printf("Значение ETIMEDOUT: %d\n", ETIMEDOUT);
    if (rval == ETIMEDOUT)
    {
        snprintf(message, sizeof(message), "поток %d > 25 сек!!!", thread_id);
        LOG_MESSAGE(message, 1);
    }
    else
    {
        printf("поток %d завершон как надо\n", thread_id);
    }

    finish_logging();
    return 1;
}
