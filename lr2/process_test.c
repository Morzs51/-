#include "logger.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    configure_logging(LOG_CONSOLE);
    start_logging();
    pid_t pid;
    pid = vfork();
    char message[256];
    switch(pid)
    {
        case -1:
            snprintf(message, sizeof(message), "Ошибка: %s", strerror(errno));
            LOG_MESSAGE(message, 1);
            sleep(1);
            finish_logging();
            exit(EXIT_FAILURE);

        case 0:
            snprintf(message, sizeof(message), "Дополнительный процесс с PID: %d", getpid());
            LOG_MESSAGE(message, 1);
            sleep(1);
            //finish_logging();
            exit(EXIT_SUCCESS);

        default:
            snprintf(message, sizeof(message), "Основной процесс с PID: %d, PID дочернего процесса: %d", getpid(), pid);
            LOG_MESSAGE(message, 1);
            wait(NULL);
            sleep(1);
            finish_logging();
            exit(EXIT_SUCCESS);
    }
}