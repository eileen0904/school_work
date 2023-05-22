#ifndef CLIENT_T_H
#define CLIENT_T_H
#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CLIENTS 10
#define BUF_MAX 5000
#define EPOLL_SIZE 20

typedef struct {
    char addr[20]; //remote address
    int clientfd; //connection fd
    int uid; //User ID
    char name[25];
    int exist;
} client_t;

#endif