#include <stdio.h>
#include <time.h>
#include <sync.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include "logger.h"

barrier_t barrier;

void *thread1(void * not_used)
{
    char buf[27];
    time_t now;

    LOG_MESSAGE("Начало ожидания барьера в 1 потоке", 1);
    sleep(3);
    
    barrier_wait(&barrier);
    
    LOG_MESSAGE("Окончание ожидания барьера в 1 потоке", 1);
}

void *thread2(void * not_used)
{
    char buf[27];
    time_t now;

    LOG_MESSAGE("Начало ожидания барьера во 2 потоке", 1);
    sleep(2);
    
    barrier_wait(&barrier);
    
    LOG_MESSAGE("Окончание ожидания барьера во 2 потоке", 1);
}


int main()
{
    configure_logging(LOG_CONSOLE);
    start_logging();

    char buf[27];
    time_t now;
    int NUM_THREADS = 2;

    barrier_init(&barrier, NULL, NUM_THREADS + 1); 
    LOG_MESSAGE("Морозов И903Б", 1);
    pthread_create(NULL, NULL, thread1, NULL);
    pthread_create(NULL, NULL, thread2, NULL);

    LOG_MESSAGE("Начало ожидания барьера в main", 1);
    barrier_wait(&barrier);
    
    LOG_MESSAGE("Окончание ожидания барьера в main", 1);
    sleep(1);
    finish_logging();

    return 0;
}