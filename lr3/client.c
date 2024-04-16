#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <stdlib.h>
#include <string.h> 
#include "logger.h"


int send_message(int coid, const char *smsg) {
    char rmsg[200];
    if (MsgSend(coid, smsg, strlen(smsg) + 1, rmsg, sizeof(rmsg)) == -1) {
        LOG_MESSAGE("Не удалось отправить сообщение", errno);
        return -1;
    }
    LOG_MESSAGE(rmsg, 1);
    return 0;
}

int main(void) {
    configure_logging(LOG_CONSOLE);
    start_logging();

    int coid;
    long serv_pid;
    char smsg[100];

    LOG_MESSAGE("Клиент запущен", 1);
    LOG_MESSAGE("Введите PID сервера: ", 1);
    scanf("%ld", &serv_pid);
    getchar();

    coid = ConnectAttach(0, serv_pid, 1, 0, 0);
    if (coid == -1) {
        LOG_MESSAGE("Ошибка подключения к серверу", errno);
        finish_logging();
        return 1;
    }

    while (1) {
        LOG_MESSAGE("Введите сообщение (или 'exit' для выхода): ",1);
        fgets(smsg, sizeof(smsg), stdin);

        if (strncmp(smsg, "exit", 4) == 0) {
            break;
        }

        if (send_message(coid, smsg) == -1) {
            break;
        }
    }

    ConnectDetach(coid);
    finish_logging();
    return 0;
}
