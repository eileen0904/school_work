#include "client_t.h"
#include "utils.h"

#define MSG_MAX 500

void addfd(int epollfd, int fd, int enable_et);
void shell(int newfd, int ser_fifo_fd, int cli_fifo_fd, int ID);