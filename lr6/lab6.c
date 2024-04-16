#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "logger.h"

int data_ready = 0;
int inf = 0;
char message[256];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;

void* consumer(void* not_used)
{
    while(inf != 5)
    {
        sleep(1);
        pthread_mutex_lock(&mutex);
        LOG_MESSAGE("ПОТРЕБИТЕЛЬ: W1", 1);
        while(!data_ready)
        {
            LOG_MESSAGE("ПОТРЕБИТЕЛЬ: W2", 1);
            pthread_cond_wait(&condvar, &mutex);// переводит поток в ожидающее состояние, пока не будет получен сигнал с помощью условной переменной
            LOG_MESSAGE("ПОТРЕБИТЕЛЬ: W3", 1);
        }
        snprintf(message, sizeof(message), "ПОТРЕБИТЕЛЬ: Полученные потребителем данные %d", inf);
        LOG_MESSAGE(message, 1);
        data_ready = 0;
        pthread_cond_signal(&condvar);//отправляет сигнал с помощью условной переменной
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* producer(void* not_used)
{
    while(inf != 5)
    {
        snprintf(message, sizeof(message), "ПРОИЗВОДИТЕЛЬ: Полученные производителем данные от h/w %d", inf);
        LOG_MESSAGE(message, 1);
        pthread_mutex_lock(&mutex);
        LOG_MESSAGE("ПРОИЗВОДИТЕЛЬ: WP1", 1);
        while(data_ready)
        {
            LOG_MESSAGE("ПРОИЗВОДИТЕЛЬ: WP2", 1);
            pthread_cond_wait(&condvar, &mutex);
        }
        data_ready = 1;
        inf++;
        LOG_MESSAGE("ПРОИЗВОДИТЕЛЬ: WP3", 1);
        pthread_cond_signal(&condvar);
        pthread_mutex_unlock(&mutex);
        
    }
    return NULL;
}

int main()
{
    configure_logging(LOG_CONSOLE);
    start_logging();
    LOG_MESSAGE("Start", 1);
    pthread_t consumer_thread, producer_thread;
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_join(consumer_thread, NULL);
    pthread_join(producer_thread, NULL);
    finish_logging();
    return 0;
}