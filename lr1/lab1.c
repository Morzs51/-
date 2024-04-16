#include "logger.h"
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    configure_logging(LOG_CONSOLE);
    start_logging();
    LOG_MESSAGE("Morozov i903b", 1); 
    sleep(1);
    finish_logging();
}