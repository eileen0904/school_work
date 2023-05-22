#include "client_t.h"
#include "shell.h"
#include "server_func.h"

#define PORT 6001

client_t clients[MAX_CLIENTS];
int ID;
char buff[BUF_MAX];
char s_fifo_name[20], c_fifo_name[20];

int main(int argc, char* argv[]) {
    struct sockaddr_in client_addr;
    int listenfd, newfd;
    int ser_fifo_fd[MAX_CLIENTS], cli_fifo_fd[MAX_CLIENTS];

    if((listenfd = bind_listen()) < 0)
        exit(1);

    int epfd = epoll_create(EPOLL_SIZE);
    if (epfd < 0) {
        perror("epfd error");
        exit(1);
    }
    static struct epoll_event events[EPOLL_SIZE];
    addfd(epfd, listenfd, 1);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        ser_fifo_fd[i] = -1;
        cli_fifo_fd[i] = -1;
    }

    init_client(&(clients), -1);

    printf("======SERVER STARTED=======\n");

    while(1){
    AGAIN:
        int epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);
        if (epoll_events_count < 0) {
            perror("epoll failure");
            exit(1);
        }
        for (int i = 0; i < epoll_events_count; i++){
            int sockfd = events[i].data.fd;
            if(sockfd == listenfd){
                socklen_t clilen = sizeof(client_addr);
                if ((newfd = accept(listenfd, (struct sockaddr*)&client_addr, &clilen)) < 0) {
                    perror("accept error");
                    exit(1);
                }
                for (ID = 0; ID < MAX_CLIENTS; ID++) {
                    if (!clients[ID].exist)
                        break;
                    else if(ID == MAX_CLIENTS - 1){  // too many clients
                        write(newfd, "Too many clients\n", strlen("Too many clients\n"));
                        close(listenfd);
                        close(newfd);
                        goto AGAIN;
                    }
                }
                handle_client(&(clients), client_addr, ID, newfd, s_fifo_name, c_fifo_name);
                umask(0);
                if ((mkfifo(s_fifo_name, 0666) < 0) && (errno != EEXIST)) {
                    printf("server fifo create error:%s\n", strerror(errno));
                    exit(1);
                }
                if ((mkfifo(c_fifo_name, 0666) < 0) && (errno != EEXIST)) {
                    printf("client fifo create error:%s\n", strerror(errno));
                    exit(1);
                }

                pid_t SC = fork();
                if (SC == 0){
                    close(listenfd);
                    open_fifo(ser_fifo_fd, cli_fifo_fd, ID, s_fifo_name, c_fifo_name, 1);

                    for(int j = 0; j < MAX_CLIENTS; j++){
                        if (j == ID || ser_fifo_fd[j] == -1 || cli_fifo_fd[j] == -1) continue;
                        close(ser_fifo_fd[j]);
                        close(cli_fifo_fd[j]);
                        ser_fifo_fd[j] = -1;
                        cli_fifo_fd[j] = -1;
                    }

                    shell(newfd, ser_fifo_fd[ID], cli_fifo_fd[ID], ID);
                    exit(0);
                }

                open_fifo(ser_fifo_fd, cli_fifo_fd, ID, s_fifo_name, c_fifo_name, 0);
                addfd(epfd, cli_fifo_fd[ID], 1);
                close(newfd);
            }
            else {
                for (int j = 0; j < MAX_CLIENTS; j++) {
                    if (sockfd == cli_fifo_fd[j]) {
                        memset(buff, 0, sizeof(buff));
                        int len = read(cli_fifo_fd[j], buff, BUF_MAX);

                        if (len < 0) {
                            perror("read error");
                            exit(1);
                        } else if (len == 0) {
                            close(cli_fifo_fd[j]);
                            cli_fifo_fd[j] = -1;
                            init_client(&(clients), j);
                        } else {
                            if (strcmp(buff, "who") == 0) {
                                write(ser_fifo_fd[j], clients, sizeof(client_t) * MAX_CLIENTS);
                            } else if (strcmp(buff, "quit") == 0) {
                                close(ser_fifo_fd[j]);
                                close(cli_fifo_fd[j]);
                                ser_fifo_fd[j] = -1;
                                cli_fifo_fd[j] = -1;
                                init_client(&(clients), j);
                            } else if (strncmp(buff, "name", 4) == 0){
                                char *msg;
                                msg = change_name(&(clients), j, buff, len);
                                write(ser_fifo_fd[j], msg, strlen(msg));
                            }
                            else if(strncmp(buff, "yell", 4) == 0){
                                char *msg;
                                msg = yell(j, buff, len);
                                for(int k = 0; k < MAX_CLIENTS; k++){
                                    if (ser_fifo_fd[k] != -1)
                                        write(ser_fifo_fd[k], msg, strlen(msg));
                                }
                            } else if (strncmp(buff, "tell", 4) == 0){
                                char* msg;
                                int recv_id = getID(buff);
                                msg = tell(j, buff, len);
                                if(clients[recv_id].exist){
                                    write(ser_fifo_fd[j], "send accept!\n", strlen("send accept!\n"));
                                    write(ser_fifo_fd[recv_id], msg, strlen(msg));
                                }
                                else{
                                    write(ser_fifo_fd[j], "send error!\n", strlen("send error!\n"));
                                    write(ser_fifo_fd[recv_id], "User not exist!\n", strlen("User not exist!\n"));
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
