#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>


const char* LOG_FILE_PATH = "log.txt";

static LogData *head = NULL;
static LogData *tail = NULL;
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
static LOG_MODE_T use_file_output = LOG_CONSOLE;
static pthread_t logging_thread;
static int logging_enabled = 0;

const char* get_time() {
    static char buffer[20];
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    return buffer;
}

void configure_logging(LOG_MODE_T mode) {
    use_file_output = mode;
}

void start_logging() {
    logging_enabled = 1;
    if (pthread_create(&logging_thread, NULL, logging_function, NULL) != 0) {
        perror("Ошибка create");
    }
}

void finish_logging() {
    logging_enabled = 0;
    if (pthread_join(logging_thread, NULL) != 0) {
        perror("ошибка join");
    }
}

void* logging_function() {
    while (logging_enabled) {
        pthread_mutex_lock(&log_mutex);
        if (head != NULL) {
            LogData* log = head;
            head = log->next;
            if (head == NULL) {
                tail = NULL;
            }
            pthread_mutex_unlock(&log_mutex);

            if(use_file_output == LOG_CONSOLE){
            printf("[%s] %s:%d %s - %s (приоритет - %d)\n", get_time(), log->file, log->line, log->function, log->message, log->priority);
            }
            else{
                FILE* log_file = fopen(LOG_FILE_PATH, "a");
                if (log_file == NULL){
                    perror("ошибка при открытии файла для записи");
                }
                fprintf(log_file, "[%s] %s:%d %s - %s (приоритет - %d)\n", get_time(), log->file, log->line, log->function, log->message, log->priority);
                fclose(log_file);
            }

            free(log->message);
            free(log);

        } else {
            pthread_mutex_unlock(&log_mutex);
            usleep(100000);
        }
    }
    return NULL;
}

void log_message(const char *file, const char *function, int line, const char *message, int priority) {
    LogData *log_data = malloc(sizeof(LogData));
    if (!log_data) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return;
    }

    log_data->message = strdup(message);
    if (!log_data->message) {
        fprintf(stderr, "Ошибка выделения памяти для message\n");
        free(log_data);
        return;
    }

    log_data->file = file;
    log_data->function = function;
    log_data->line = line;
    log_data->priority = priority;
    log_data->next = NULL;

    pthread_mutex_lock(&log_mutex);
    if (tail != NULL) {
        tail->next = log_data;
    }
    tail = log_data;
    if (head == NULL) {
        head = log_data;
    }
    pthread_mutex_unlock(&log_mutex);
}