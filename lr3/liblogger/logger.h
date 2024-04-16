#ifndef LOGGER_H
#define LOGGER_H

#include <pthread.h>

enum LOG_MODE {
    LOG_CONSOLE,
    LOG_FILE,
};

typedef enum LOG_MODE LOG_MODE_T;

void configure_logging(LOG_MODE_T mode);
void start_logging();
void finish_logging();
void log_message(const char *file, const char *function, int line, const char *message, int priority);
void* logging_function();

#define LOG_MESSAGE(message, priority) log_message(__FILE__, __func__, __LINE__, message, priority)

typedef struct LogData {
    char *message;
    const char *file;
    const char *function;
    int line;
    int priority;
    struct LogData *next;
} LogData;

#endif