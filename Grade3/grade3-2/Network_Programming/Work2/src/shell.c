#include "shell.h"

void addfd(int epollfd, int fd, int enable_et) {
    struct epoll_event ev;
    ev.data.fd = fd;

    if(enable_et){
        ev.events = EPOLLIN;
        ev.events = EPOLLIN | EPOLLET;
    }
    
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

void shell(int newfd, int ser_fifo_fd, int cli_fifo_fd, int ID) {
    int epfd = epoll_create(EPOLL_SIZE);
    if (epfd < 0) {
        perror("epfd error");
        exit(-1);
    }
    static struct epoll_event events[2];
    addfd(epfd, newfd, 1);
    addfd(epfd, ser_fifo_fd, 1);

    setenv("PATH", "bin:.", 1);
    char* buf;
    int i = 0, special_cmd = 0;

    while(1){
    AGAIN:
        special_cmd = 0;
        write(newfd, "% ", strlen("% "));

        int epoll_events_count = epoll_wait(epfd, events, 2, -1);
        for (i = 0; i < epoll_events_count; i++){
            if (events[i].data.fd == newfd){
                buf = read_command(newfd);
                if (buf == NULL)
                    goto AGAIN;
                
                char variable[10], value[20];
                memset(variable, 0, 10);
                memset(value, 0, 20);

                if (strcmp(buf, "quit") == 0) {
                    write(cli_fifo_fd, buf, strlen(buf));
                    close(newfd);
                    close(ser_fifo_fd);
                    close(cli_fifo_fd);
                    exit(0);
                }
                else if (strcmp(buf, "who") == 0) {
                    client_t clients[MAX_CLIENTS];
                    char info[BUF_MAX], temp[10];
                    write(cli_fifo_fd, buf, strlen(buf));
                    read(ser_fifo_fd, clients, sizeof(client_t) * MAX_CLIENTS);
                    snprintf(info, BUF_MAX, "<ID>    <name>     <IP:port>          <indicate me>\n");
                    write(newfd, info, strlen(info));
                    for(int j = 0; j < MAX_CLIENTS; j++){
                        if (clients[j].exist) {
                            if (clients[j].uid == ID) {
                                snprintf(info, BUF_MAX, "   %d    %s    %s    <-(me)\n", clients[j].uid, clients[j].name, clients[j].addr);
                            } else {
                                snprintf(info, BUF_MAX, "   %d    %s    %s\n", clients[j].uid, clients[j].name, clients[j].addr);
                            }
                            write(newfd, info, strlen(info));
                        }
                    }
                    special_cmd = 1;
                }
                else if (strncmp(buf, "name", 4) == 0){
                    static char msg[80];
                    memset(msg, 0, sizeof(msg));
                    write(cli_fifo_fd, buf, strlen(buf));
                    read(ser_fifo_fd, msg, 80);
                    write(newfd, msg, strlen(msg));
                    special_cmd = 1;
                } 
                else if (strncmp(buf, "yell", 4) == 0) {
                    static char msg[MSG_MAX];
                    memset(msg, 0, sizeof(msg));
                    write(cli_fifo_fd, buf, strlen(buf));
                    read(ser_fifo_fd, msg, MSG_MAX);
                    write(newfd, msg, strlen(msg));
                    special_cmd = 1;
                }
                else if (strncmp(buf, "tell", 4) == 0){
                    static char msg[MSG_MAX];
                    memset(msg, 0, sizeof(msg));
                    write(cli_fifo_fd, buf, strlen(buf));
                    read(ser_fifo_fd, msg, MSG_MAX);
                    write(newfd, msg, strlen(msg));
                    special_cmd = 1;
                }
                else if (strncmp(buf, "printenv", 8) == 0) {
                    int j = 0, k = 0;
                    for (k = 9; k < strlen(buf); k++) {
                        variable[j++] = buf[k];
                    }
                    char* val = getenv(variable);
                    strcat(val, "\n");
                    if (val == NULL)
                        write(newfd, "\n", strlen("\n"));
                    else
                        write(newfd, val, strlen(val));
                    special_cmd = 1;
                } else if (strncmp(buf, "setenv", 6) == 0) {
                    int idx = 0, j = 0, k = 0, q = 0;
                    for (q = 7; q < strlen(buf); q++) {
                        if (buf[q] == ' ') {
                            idx = q;
                            break;
                        }
                        variable[j++] = buf[q];
                    }
                    for (q = idx + 1; q < strlen(buf); q++) {
                        value[k++] = buf[i];
                    }
                    if (setenv(variable, value, 1) < 0) {
                        perror("setenv: ");
                    }
                    special_cmd = 1;
                }

                Command* CMD = parse(buf);
                if (special_cmd) {
                    CMD->fin = 1;
                    goto AGAIN;
                }

                if(execute(CMD, newfd))
                    goto AGAIN;
            }
            if (events[i].data.fd == ser_fifo_fd){
                char* buff = malloc(sizeof(char*) * BUF_MAX);
                memset(buff, '\0', BUF_MAX);
                read(ser_fifo_fd, buff, BUF_MAX);
                write(newfd, buff, strlen(buff));
            }
        }
    }
}