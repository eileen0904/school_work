#include "server_func.h"
#include "utils.h"

void listMail(redisContext *c, int newfd, char *usr_name){
    redisReply *reply = NULL;
    char info[BUF_MAX];
    reply = redisCommand(c, "LRANGE %s_mail_list 0 -1", usr_name);
    if (reply->type == REDIS_REPLY_ARRAY && reply->elements > 0){
        snprintf(info, BUF_MAX, "<id>\t<date>\t\t      <sender>\t   <message>\n");
        write(newfd, info, strlen(info));
        for (int j = 0; j < reply->elements; j++)
            write(newfd, reply->element[j]->str, strlen(reply->element[j]->str));
    }
    else if (reply->elements <= 0)
        write(newfd, "Empty !\n", strlen("Empty !\n"));
    freeReplyObject(reply);
}

int mailto(char *buf, redisContext *c, int newfd, char *usr_name){
    redisReply *reply = NULL;
    char msg[MSG_MAX] = {}, current_time[80] = {}, receiver[25] = {}, info[1024] = {};
    int i = 7, j = 0, HasNumpipe = 0, isRedi = 0;
    time_t rawtime;
    struct tm *TM;
    long long id = 1;

    time(&rawtime);
    TM = localtime(&rawtime);
    strftime(current_time, 80, "%Y-%m-%e %H:%M:%S", TM);

    while(buf[i] != ' '){
        receiver[j] = buf[i];
        i++;
        j++;
    }
    size_t len = strlen(buf);
    j = 0, i++;
    if(buf[i] == '<'){
        for (i = i + 2; i < len; i++){
            msg[j++] = buf[i];
        }
        msg[strlen(msg)] = '\0';
        size_t len = strlen(msg);
        isRedi = 1;
    }
    else{
        for (i = i; i < len; i++){
            msg[j++] = buf[i];
        }
        msg[strlen(msg)] = '\0';
        size_t len = strlen(msg);
        isRedi =  0;
    }

    reply = redisCommand(c, "GET %s", receiver);
    if (reply == NULL || reply->type != REDIS_REPLY_STRING){
        write(newfd, "User not found !\n", strlen("User not found !\n"));
        freeReplyObject(reply);
        return -1;
    }
    freeReplyObject(reply);

    if (isRedi){
        int fd[2];
        if (pipe(fd) == -1)
            perror("pipe");
        Command *redir = parse(msg);
        if (execute(redir, fd[1]) == 0)
            redir->fin = 1;
        close(fd[1]);
        read(fd[0], msg, sizeof(msg));
        close(fd[0]);
    }

    reply = redisCommand(c, "LLEN %s_mail_list", receiver);
    if (reply && reply->type == REDIS_REPLY_INTEGER)
        id = reply->integer;
    freeReplyObject(reply);

    sprintf(info, "% lld\t%s   %s\t   %s\n", id, current_time, usr_name, msg);
    info[strlen(info)] = '\0';

    reply = redisCommand(c, "LPUSH %s_mail_list %s", receiver, info);
    if (reply && reply->type == REDIS_REPLY_INTEGER && reply->integer != 0)
        write(newfd, "Send accept !\n", strlen("Send accept !\n"));
    freeReplyObject(reply);

    if(isRedi) return 1;
    else return 0;
}

void delMail(char *buf, redisContext *c, int newfd, char *usr_name){
    redisReply *reply = NULL;
    char mailid[10] = {}, delmail[1024] = {};
    int i = 8, j = 0, id;

    for(;i < strlen(buf); i++)
        mailid[j++] = buf[i];
    mailid[j] = '\0';
    id = atoi(mailid);

    reply = redisCommand(c, "LRANGE %s_mail_list 0 -1", usr_name);
    int delID = -1;
    if (reply->type == REDIS_REPLY_ARRAY && reply->elements > 0){
        for(i = 0; i < reply->elements; i++){
            delID = atoi(reply->element[i]->str);
            if(id == delID){
                strcpy(delmail, reply->element[i]->str);
                delmail[strlen(delmail)] = '\0';
                freeReplyObject(reply);
                break;
            }
        }

        reply = redisCommand(c, "LREM %s_mail_list 0 %s", usr_name, delmail);
        if (reply->integer > 0)
            write(newfd, "Delete accept !\n", strlen("Delete accept !\n"));
        else
            write(newfd, "Mail id unexist !\n", strlen("Mail id unexist !\n"));
        freeReplyObject(reply);
    }
}