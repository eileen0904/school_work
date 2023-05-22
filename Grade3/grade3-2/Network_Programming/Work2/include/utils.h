#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define BUF_MAX 5000
#define CMD_MAX 256
#define MAX 100

struct command {
    char* cmd[MAX];
    char* path;
    int n, arg, fin;
    struct command *next, *prev, *pipelist_n, *pipelist_p;
};
typedef struct command Command;

int execute(Command *CMD, int newfd);
char* read_command(int newfd);
Command* insert(Command* COM, char** str, int count);
void FreeList();
Command* parse(char* buf);
void handle_sigusr1(int signum);
void run(Command* CMD, int newfd);
Command* DeleteCommand(Command* node);
int check();
int check_HasNumPipe();