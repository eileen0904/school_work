#include "utils.h"
#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct command {
    char *cmd[MAX];
    char *path;
    int n, arg, fin;
    struct command *next, *prev, *pipelist_n, *pipelist_p;
};
typedef struct command Command;

int fd[MAX * 2], argc = 0, HasNumPipe = 0, cmdNotFound = 0;
Command *head = NULL, *tail = NULL, *headlist = NULL;

char *read_command() {
    static char buf[buf_MAX];
    memset(buf, '\0', sizeof(buf));
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        printf("fgets error\n");
    }
    if (strcmp(buf, "\n") == 0)
        return NULL;
    size_t len = strlen(buf);
    buf[len - 1] = '\0';
    return buf;
}

Command *insert(Command* COM, char** str, int count) {
    Command* newcmd = (Command*)malloc(sizeof(Command));
    const char *pa = "./bin/";
    char fullPath[MAX];
    memset(fullPath, 0, sizeof(fullPath));
    int i = 0;
    newcmd->path = malloc(cmd_MAX * sizeof(char));

    if(head == NULL && tail == NULL){
        newcmd -> arg = 0;
        for(i = 0; i < count; i++){
            newcmd->cmd[i] = *(str+i);
            newcmd->n = 0;
        }
        newcmd->arg = count;
        newcmd->n = 0;
        newcmd->prev = NULL;
        newcmd->next = NULL;
        newcmd->pipelist_n = NULL;
        newcmd->pipelist_p = NULL;
        newcmd->fin = 0;
        strcat(fullPath, pa);
        strcat(fullPath, *(str));
        i = 0;
        while(fullPath[i]){
            newcmd->path[i] = fullPath[i];
            i++;
        }
        head = newcmd;
        tail = newcmd;
    }
    else{
        for (i = 0; i < count; i++) {
            newcmd->cmd[i] = str[i];
        }
        newcmd->arg = count;
        newcmd->n = 0;
        newcmd->fin = 0;
        strcat(fullPath, pa);
        strcat(fullPath, *(str));
        i = 0;
        while (fullPath[i]) {
            newcmd->path[i] = fullPath[i];
            i++;
        }
        newcmd->prev = COM;
        newcmd->next = NULL;
        newcmd->pipelist_n = NULL;
        newcmd->pipelist_p = NULL;
        COM->next = newcmd;
        tail = newcmd;
    }
    return newcmd;
}

void FreeList() { 
    Command *cur, *tmp;
    cur = head;
    while (cur != NULL) {
        tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    head = NULL, tail = NULL, headlist = NULL, argc = 0;
}

Command* parse(char *buf){
    const char delim[2] = " ";
    char* token, *str[MAX];
    int i = 0;
    Command *cur = NULL;
    if(!HasNumPipe) FreeList();
    else{cur = tail;}

    token = strtok(buf, delim);
    while (token) {
        if(token[0] == '|'){
            str[i++] = NULL;
            cur = insert(cur, str, i);
            for (int j = 0; j < i; j++) {
                str[j] = NULL;
            }
            i = 0;
            argc++;
            if (token[1] >= 48 && token[1] <= 57) {
                cur->n = token[1] - 48;
                HasNumPipe = 1;
                return cur;
            }
        }
        else {
            str[i++] = token;
        }
        token = strtok(NULL, delim);
    }
    str[i++] = NULL;
    cur = insert(cur, str, i);
    argc++;
    if(HasNumPipe) return cur;
    else{return head;}
}

void handle_sigusr1(int signum) {
    cmdNotFound = 1;
    for (int i = 0; i < 2 * argc; i++)
        close(fd[i]);
    for (int i = 0; i < argc + 1; i++)
        wait(NULL);
}

void run(Command* CMD) {
    // fd odd:read(out) 0:STDIN
    // fd even:write(in) 1:STDOUT
    pid_t pid;
    int i = 0, j = 0, status;
    Command* cur = NULL;

    for (i = 0; i < argc; i++) {
        if (pipe(fd + i * 2) < 0) {
            perror("pipe");
            exit(0);
        }
    }

    if(HasNumPipe && CMD->pipelist_p) cur = headlist;
    else{cur = CMD;}

    while(cur){
        if ((pid = fork()) == -1) {
            perror("fork");
            exit(0);
        }
        else if(pid == 0){
            if (cur->next != NULL) {  // if have next cmd
                if (dup2(fd[j + 1], 1) < 0) {  // stdin->pipe write
                    perror("dup2 : pipe write");
                    exit(0);
                }
            }
            if (j != 0) {  // if have previous cmd
                if (dup2(fd[j - 2], 0) < 0) {  // stdout->pipe read
                    perror("dup2 : pipe read");
                    exit(0);
                }
            }
            for (int k = 0; k < argc * 2; k++) {
                close(fd[k]);
            }
            if(execv(cur->path, cur->cmd) < 0){
                fprintf(stderr, "Unknown command: [%s].\n", *cur->cmd);
                kill(getppid(), SIGUSR1);
                exit(0);
            }
        }
        if (cur->pipelist_n) cur = cur->pipelist_n;
        else{cur = cur->next;}
        j += 2;
    }
    signal(SIGUSR1, handle_sigusr1);
    for (i = 0; i < 2 * argc; i++)
        close(fd[i]);
    for (i = 0; i < argc + 1; i++)
        wait(&status);
}

Command *DeleteCommand( Command *node){
    Command* ptr = head;
    if (head == NULL) {
        printf("Nothing to delete!\n");
        return NULL;
    }
    if(head == tail){
        head = NULL;
        tail = NULL;
    }
    else if (node == head) {
        head = head->next;
        head->prev = NULL;
        node->next = NULL;
    } else if(node == tail){
        tail = tail->prev;
        tail->next = NULL;
        node->prev = NULL;
        if(node->pipelist_p){
            node->pipelist_p->pipelist_n = NULL;
            node->pipelist_p = NULL;
        }
    }
    else{
        while (ptr->next != node) {
            ptr = ptr->next;
        }
        ptr->next = node->next;
        node->next->prev = ptr;
        node->next = NULL;
        node->prev = NULL;
        if (node->pipelist_p || node->pipelist_n){
            node->pipelist_p->pipelist_n = node->pipelist_n;
            node->pipelist_n->pipelist_p = node->pipelist_p;
            node->pipelist_p = NULL;
            node->pipelist_n = NULL;
        }
    }
    free(node);
}

int check(){
    Command * cur = head, *curr = head;
    headlist = NULL;

    while(cur){
        if(cur->n && !cur->fin){
            curr = cur;
            for(int i = 0; i < cur->n; i++){
                curr = curr->next;
                if(curr == NULL)
                    break;
            }
            if(curr == NULL){
                cur = cur->next;
                continue;
            }
            cur->pipelist_n = curr;
            curr->pipelist_p = cur;
            if(cur->pipelist_p == NULL){
                headlist = cur;
            }
        }
        cur = cur->next;
    }
    if(headlist) return 1;
    return 0;
}

int check_HasNumPipe(){
    Command *cur = head;
    while(cur){
        if(!cur->fin) return 0;
        cur = cur->next;
    }
    return 1;
}

void execute(){
    char* buf;
    int i = 0, env = 0;

    while (1) {
        env = 0;
        printf("%s", "% ");
        buf = read_command();

        if (buf == NULL)
            continue;

        if (strcmp(buf, "quit") == 0)
            break;

        char variable[10], value[20];
        memset(variable, 0, 10);
        memset(value, 0, 20);

        if(strncmp(buf, "printenv", 8) == 0){
            int j = 0;
            for (i = 9; i < strlen(buf); i++) {
                variable[j++] = buf[i];
            }
            char* val = getenv(variable);
            if (val == NULL)
                printf("\n");
            else
                printf("%s\n", val);
            env = 1;
        }

        if (strncmp(buf, "setenv", 6) == 0) {
            int idx = 0, j = 0, k = 0;
            for (i = 7; i < strlen(buf); i++) {
                if (buf[i] == ' ') {
                    idx = i;
                    break;
                }
                variable[j++] = buf[i];
            }
            for (i = idx + 1; i < strlen(buf); i++) {
                value[k++] = buf[i];
            }
            if (setenv(variable, value, 1) < 0) {
                perror("setenv: ");
            }
            env = 1;
        }

        Command *CMD = parse(buf);

        if(env){
            CMD->fin = 1;
            continue;
        }

        if ((HasNumPipe && check() && CMD->pipelist_p) || !HasNumPipe) {
            if(CMD->n) continue;

            run(CMD);

            if (cmdNotFound) {
                DeleteCommand(CMD);
                cmdNotFound = 0;
            }
            else{
                if (headlist) {
                    Command* cur = headlist;
                    while (cur) {
                        cur->fin = 1;
                        cur = cur->pipelist_n;
                    }
                } else {
                    Command* cur = head;
                    while (cur) {
                        cur->fin = 1;
                        cur = cur->next;
                    }
                }
            }
        } else if (!CMD->n && CMD->pipelist_p == NULL) {  // normal NumPipe
            run(CMD);

            if (cmdNotFound) {
                DeleteCommand(CMD);
                cmdNotFound = 0;
            }
            else{
                CMD->fin = 1;
            }
        }
        if(check_HasNumPipe()) HasNumPipe = 0;
    }
}
