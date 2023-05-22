#include "client_t.h"

int bind_listen();
void init_client(client_t (*clients)[MAX_CLIENTS], int id);
void handle_client(client_t (*clients)[MAX_CLIENTS], struct sockaddr_in client_addr, int ID, int newfd, char s_fifo_name[20], char c_fifo_name[20]);
void open_fifo(int ser_fifo_fd[MAX_CLIENTS], int cli_fifo_fd[MAX_CLIENTS], int ID, char s_fifo_name[20], char c_fifo_name[20], int flag);
char* change_name(client_t (*clients)[MAX_CLIENTS], int ID, char* buf, int len);
char* yell(int ID, char* buf, int len);
int getID(char* buf);
char* tell(int ID, char* buf, int len);
