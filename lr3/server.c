#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <string.h>
#include "logger.h"



void handle_message(int rcvid, int chid, char *message) {
    char response[512];
    snprintf(response, sizeof(response), "ответ на сообщение: %s", message);
    MsgReply(rcvid, EOK, response, strlen(response) + 1);
    LOG_MESSAGE(response, 1);
}


void server(void) {
    int rcvid;
    int chid;
    char log_buffer[256];
    char message[256];

    LOG_MESSAGE("Сервер запущен", 1);
    chid = ChannelCreate(0);
    if (chid == -1) {
        LOG_MESSAGE("Ошибка при создании канала", errno);
        return;
    }
    
    snprintf(log_buffer, sizeof(log_buffer), "id канала: %d", chid);
    LOG_MESSAGE(log_buffer, 1);
    sleep(1);
    snprintf(log_buffer, sizeof(log_buffer), "Pid: %d", getpid());
    LOG_MESSAGE(log_buffer, 1);

    while (1) {
        rcvid = MsgReceive(chid, message, sizeof(message), NULL);
        if (rcvid == -1) {
            LOG_MESSAGE("Ошибка при получении сообщения", errno);
            continue;
        }

        handle_message(rcvid, chid, message);
    }
}

int main(void) {
    configure_logging(LOG_CONSOLE);
    start_logging();

    server();

    finish_logging();
    return 0;
}
