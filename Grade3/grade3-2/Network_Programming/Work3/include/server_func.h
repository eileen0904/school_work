#include "client_t.h"

#define PORT 6001
#define MSG_MAX 500
#define MAX 100

//For handle client
int bind_listen();
void init_client(client_t (*clients)[MAX_CLIENTS], int id);
void handle_client(client_t (*clients)[MAX_CLIENTS], struct sockaddr_in client_addr, int ID, int newfd, char s_fifo_name[20], char c_fifo_name[20]);
void open_fifo(int ser_fifo_fd[MAX_CLIENTS], int cli_fifo_fd[MAX_CLIENTS], int ID, char s_fifo_name[20], char c_fifo_name[20], int flag);

//For basic function
char* change_name(client_t (*clients)[MAX_CLIENTS], int ID, char* buf, int len);
char* yell(int ID, char* buf, int len);
int getID(char* buf);
char* tell(int ID, char* buf, int len);

//For Login
char *create_account(redisContext *c, int newfd);
char *login(redisContext *c, int newfd);
char *usr_register(redisContext *c, int newfd);

//For Mail
void listMail(redisContext *c, int newfd, char *usr_name);
int mailto(char *buf, redisContext *c, int newfd, char *usr_name);
void delMail(char *buf, redisContext *c, int newfd, char *usr_name);

//For Group
char *gyell(char *buf, char *group_name, char *usr_name, redisContext *c);
void _gyell(char *msg, int newfd, int ser_fifo_fd, int cli_fifo_fd, redisContext *c);
void createGroup(char *buf, char *usr_name, int newfd, redisContext *c);
void addTo(char *buf, char *usr_name, int newfd, redisContext *c);
void delGroup(char *buf, char *usr_name, int newfd, redisContext *c);
void listGroup(char *buf, char *usr_name, int newfd, redisContext *c);
void leaveGroup(char *buf, char *usr_name, int newfd, redisContext *c);
void remove_member(char *buf, char *usr_name, int newfd, redisContext *c);
