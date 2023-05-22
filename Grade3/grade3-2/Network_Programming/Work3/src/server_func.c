#include "server_func.h"

char *serv_fifo_name = "/tmp/server", *clie_fifo_name = "/tmp/client";

int bind_listen() {
    struct sockaddr_in server_addr;
    int listenfd, newfd;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        return -1;
    }

    const int reuse = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt error\n");
        return -1;
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if (bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind error");
        return -1;
    }

    if (listen(listenfd, 5) != 0) {
        perror("listen error");
        return -1;
    }

    return listenfd;
}

void init_client(client_t (*clients)[MAX_CLIENTS], int id) {
    char no_name[] = "no_name";

    if(id == -1){ //all
        for (int i = 0; i < MAX_CLIENTS; i++) {
            (*clients)[i].clientfd = 0;
            (*clients)[i].uid = -1;
            (*clients)[i].exist = 0;
            memset((*clients)[i].addr, 0, sizeof((*clients)[i].addr));
            memset((*clients)[i].name, 0, sizeof((*clients)[i].name));
            strcpy((*clients)[i].name, no_name);
        }
    }
    else{
        (*clients)[id].clientfd = 0;
        (*clients)[id].uid = -1;
        (*clients)[id].exist = 0;
        memset((*clients)[id].addr, 0, sizeof((*clients)[id].addr));
        memset((*clients)[id].name, 0, sizeof((*clients)[id].name));
        strcpy((*clients)[id].name, no_name);
    }
}

void handle_client(client_t (*clients)[MAX_CLIENTS], struct sockaddr_in client_addr, int ID, int newfd, char s_fifo_name[20], char c_fifo_name[20]) {
    (*clients)[ID].uid = ID;
    (*clients)[ID].exist = 1;
    (*clients)[ID].clientfd = newfd;
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr.sin_addr), str, INET_ADDRSTRLEN);
    int port = ntohs(client_addr.sin_port);
    char s[20];
    sprintf(s, "%s:%d", str, port);
    strcpy((*clients)[ID].addr, s);

    sprintf(s_fifo_name, "%s%d", serv_fifo_name, ID);
    sprintf(c_fifo_name, "%s%d", clie_fifo_name, ID);
}

void open_fifo(int ser_fifo_fd[MAX_CLIENTS], int cli_fifo_fd[MAX_CLIENTS], int ID, char s_fifo_name[20], char c_fifo_name[20], int flag) {
    if(flag){ //client
        if ((ser_fifo_fd[ID] = open(s_fifo_name, O_RDONLY)) < 0) {
            fprintf(stderr, "%s open error: %s\n", s_fifo_name, strerror(errno));
        }
        if ((cli_fifo_fd[ID] = open(c_fifo_name, O_WRONLY)) < 0) {
            fprintf(stderr, "%s open error: %s\n", c_fifo_name, strerror(errno));
        }
    }
    else{ //server
        if ((ser_fifo_fd[ID] = open(s_fifo_name, O_WRONLY)) < 0) {
            fprintf(stderr, "%s open error: %s\n", s_fifo_name, strerror(errno));
        }
        if ((cli_fifo_fd[ID] = open(c_fifo_name, O_RDONLY)) < 0) {
            fprintf(stderr, "%s open error: %s\n", c_fifo_name, strerror(errno));
        }
    }
}

char *change_name(client_t (*clients)[MAX_CLIENTS], int ID, char* buf, int len) {
    static char msg[80], name[25];
    memset(msg, 0, sizeof(msg));
    memset(name, 0, sizeof(name));
    int i, j = 0;
    for(i = 5; i < len; i++){
        name[j++] = buf[i];
    }
    name[j] = '\0';
    for(i = 0; i < MAX_CLIENTS; i++){
        if (strcmp(name, (*clients)[i].name) == 0){
            sprintf(msg, "User %s already exist!\n", name);
            size_t len1 = strlen(msg);
            msg[len1] = '\0';
            return msg;
        }
    }
    bzero((*clients)[ID].name, 0);
    strcpy((*clients)[ID].name, name);
    sprintf(msg, "name change accept!\n");
    size_t len2 = strlen(msg);
    msg[len2] = '\0';

    return msg;
}

char* yell(int ID, char* buf, int len) {
    static char msg[MSG_MAX], text[MAX];
    int i, j = 0;
    memset(msg, 0, sizeof(msg));
    memset(text, 0, sizeof(text));

    for(i = 5; i < len; i++){
        text[j++] = buf[i];
    }

    sprintf(msg, "<user(%d) yelled>: %s\n", ID, text);
    msg[strlen(msg)] = '\0';

    return msg;
}

int getID(char *buf){
    int ID, i = 5, j = 0;
    char id[5];

    while(buf[i] >= 48 && buf[i] <= 57){
        id[j++] = buf[i++];
    }

    id[j] = '\0';
    ID = atoi(id);

    return ID;
}

char *tell(int ID, char *buf, int len){
    static char msg[MSG_MAX], text[MAX];
    int i = 5, j = 0;
    memset(msg, 0, sizeof(msg));
    memset(text, 0, sizeof(text));

    while ((buf[i] >= 48 && buf[i] <= 57) || (buf[i] == ' ')) {
        i++;
    }

    for(i; i < len; i++){
        text[j++] = buf[i];
    }

    sprintf(msg, "<user(%d) told you>: %s\n", ID, text);
    msg[strlen(msg)] = '\0';

    return msg;
}
