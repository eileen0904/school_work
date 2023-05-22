#include "server_func.h"
#include "utils.h"

char *gyell(char *buf, char *group_name, char *usr_name, redisContext *c){
    redisReply *reply = NULL;
    static char msg[MSG_MAX], info[1024], *not_found = "Group not found !\n";
    int i = 6, j = 0;

    memset(msg, 0, sizeof(msg));
    memset(info, 0, sizeof(info));

    while (buf[i] != ' '){
        group_name[j] = buf[i];
        i++;
        j++;
    }
    group_name[j] = '\0';
    j = 0;
    for (i = i + 1; i < strlen(buf); i++)
        msg[j++] = buf[i];
    msg[j] = '\0';

    reply = redisCommand(c, "LRANGE group_list 0 -1");
    if (reply && reply->type == REDIS_REPLY_ARRAY){
        for (i = 0; i < reply->elements; i++){
            if (strcmp(reply->element[i]->str, group_name) == 0){
                freeReplyObject(reply);
                sprintf(info, "<%s-%s>: %s\n", group_name, usr_name, msg);
                info[strlen(info)] = '\0';
                return info;
            }
        }
    }
    freeReplyObject(reply);
    return not_found;
}

void _gyell(char *buf, int newfd, int ser_fifo_fd, int cli_fifo_fd, redisContext *c){
    char msg[MSG_MAX] = {};

    write(cli_fifo_fd, buf, strlen(buf));
    read(ser_fifo_fd, msg, MSG_MAX);
    write(newfd, msg, strlen(msg));
}

void createGroup(char *buf, char *usr_name, int newfd, redisContext *c){
    redisReply *reply = NULL;
    char group_name[MAX] = {};
    int i = 12, j = 0, success = 1;

    for (;i < strlen(buf); i++)
        group_name[j++] = buf[i];
    group_name[j] = '\0';

    reply = redisCommand(c, "LRANGE group_list 0 -1");
    if (reply && reply->type == REDIS_REPLY_ARRAY){
        for (i = 0; i < reply->elements; i++){
            if (strcmp(group_name, reply->element[i]->str) == 0){
                write(newfd, "Group already exist !\n", strlen("Group already exist !\n"));
                freeReplyObject(reply);
                return;
            }
        }
    }
    if (success){
        freeReplyObject(reply);
        reply = redisCommand(c, "LPUSH group_list %s", group_name);
        if (reply && reply->type == REDIS_REPLY_INTEGER)
            write(newfd, "Create success !\n", strlen("Create success !\n"));
        freeReplyObject(reply);
        reply = redisCommand(c, "LPUSH %s_group %s", group_name, usr_name);
        freeReplyObject(reply);
    }
}

void addTo(char *buf, char *usr_name, int newfd, redisContext *c){
    redisReply *reply = NULL, *reply1 = NULL, *reply2 = NULL;
    char *group_name, *token;
    char not_found_list[MSG_MAX] = {}, already_in_list[MSG_MAX] = {}, send_list[MSG_MAX] = {};
    int count = 0, i = 0, j = 0, k = 0;
    int title = 1, first = 1, flag = 0, not_found = 0, already_in = 0, success = 0;
    const char delim[2] = " ";
    
    token = strtok(buf, delim);
    while (token){
        if (title)
            title = 0;
        else if (first){
            group_name = token;
            first = 0;
            reply = redisCommand(c, "LRANGE %s_group 0 -1", group_name);
            if (reply && reply->type == REDIS_REPLY_ARRAY){
                if (!reply->elements){
                    write(newfd, "Group Not Found !\n", strlen("Group Not Found !\n"));
                    freeReplyObject(reply);
                    return;
                }
                int owner = reply->elements - 1;
                if (strcmp(reply->element[owner]->str, usr_name)){
                    write(newfd, "You don't have permissions !\n", strlen("You don't have permissions !\n"));
                    freeReplyObject(reply);
                    return;
                }
            }
        }
        else{
            if (reply && reply->type == REDIS_REPLY_ARRAY){
                reply1 = redisCommand(c, "GET %s", token);
                if (reply1->type != REDIS_REPLY_STRING){ // user not found
                    strcat(not_found_list, token);
                    strcat(not_found_list, " ");
                    not_found = 1;
                    flag = 0;
                    freeReplyObject(reply1);
                    token = strtok(NULL, delim);
                    continue;
                }
                else { // user already in
                    for (i = 0; i < reply->elements; i++){
                        if (strcmp(token, reply->element[i]->str) == 0){
                            strcat(already_in_list, token);
                            strcat(already_in_list, " ");
                            already_in = 1;
                            flag = 1;
                        }
                    }
                }
                if (!flag){ // add user
                    reply2 = redisCommand(c, "LPUSH %s_group %s", group_name, token);
                    strcat(send_list, token);
                    strcat(send_list, " ");
                    success = 1;
                    freeReplyObject(reply2);
                }
                flag = 0;
                freeReplyObject(reply1);
            }
        }
        token = strtok(NULL, delim);
    }
    if (reply && reply->type == REDIS_REPLY_ARRAY){
        if (not_found){
            strcat(not_found_list, "not found !\n");
            write(newfd, not_found_list, strlen(not_found_list));
        }
        if (already_in){
            strcat(already_in_list, "already in group !\n");
            write(newfd, already_in_list, strlen(already_in_list));
        }
        if(success){
            strcat(send_list, "add success !\n");
            write(newfd, send_list, strlen(send_list));
        }
    }
    freeReplyObject(reply);
}

void delGroup(char *buf, char *usr_name, int newfd, redisContext *c){
    redisReply *reply = NULL, *reply1 = NULL;
    char group_name[MAX] = {};
    int i = 9, j = 0;

    for (; i < strlen(buf); i++)
        group_name[j++] = buf[i];
    group_name[j] = '\0';

    reply = redisCommand(c, "LRANGE %s_group 0 -1", group_name);
    if(reply && reply->type == REDIS_REPLY_ARRAY){
        if(!reply->elements){
            write(newfd, "Group not found !\n", strlen("Group not found !\n"));
            freeReplyObject(reply);
            return;
        }
        int owner = reply->elements - 1;
        if(strcmp(usr_name, reply->element[owner]->str) == 0){
            reply1 = redisCommand(c, "DEL %s_group", group_name); //delete key
            write(newfd, "Group delete success !\n", strlen("Group delete success !\n"));
            freeReplyObject(reply1);

            reply1 = redisCommand(c, "LREM group_list 0 %s", group_name);
            freeReplyObject(reply1);
        }
        else
            write(newfd, "You don't have permissions !\n", strlen("You don't have permissions !\n"));
    }
    freeReplyObject(reply);
}

void listGroup(char *buf, char *usr_name, int newfd, redisContext *c){
    redisReply *reply = NULL, *reply1 = NULL;
    char *info = " <owner>     <group>\n";
    char msg[MSG_MAX] = {};
    int first = 1, empty = 1;

    reply = redisCommand(c, "LRANGE group_list 0 -1");
    if(reply && reply->type == REDIS_REPLY_ARRAY){
        for(int i = 0; i < reply->elements; i++){ //group_list
            memset(msg, 0, sizeof(msg));
            reply1 = redisCommand(c, "LRANGE %s_group 0 -1", reply->element[i]->str); //owner in
            if (reply1 && reply1->type == REDIS_REPLY_ARRAY && reply1->elements){
                int owner = reply1->elements - 1;
                sprintf(msg, " %s\t     %s\n", reply1->element[owner]->str, reply->element[i]->str);
                for(int j = 0; j < reply1->elements; j++){ //check usr wheather in group
                    if(strcmp(usr_name, reply1->element[j]->str) == 0){
                        if(first){
                            write(newfd, info, strlen(info));
                            first = 0;
                        }
                        write(newfd, msg, strlen(msg));
                        empty = 0;
                        break;
                    }
                }
            }
            freeReplyObject(reply1);
        }
    }
    freeReplyObject(reply);
    
    if(empty)
        write(newfd, "Empty !\n", strlen("Empty !\n"));
}

void leaveGroup(char *buf, char *usr_name, int newfd, redisContext *c){
    redisReply *reply = NULL, *reply1 = NULL;
    char group_name[MAX] = {};
    int i = 11, j = 0;

    for (; i < strlen(buf); i++)
        group_name[j++] = buf[i];
    group_name[j] = '\0';

    reply = redisCommand(c, "%s_group", group_name);
    size_t num_of_members = reply->elements;
    freeReplyObject(reply);

    reply = redisCommand(c, "LREM %s_group 0 %s", group_name, usr_name);
    if (reply && reply->integer == 0){
        write(newfd, "Leave fault !\n", strlen("Leave fault !\n"));
        freeReplyObject(reply);
        return;
    }
    if (num_of_members == 1){
        reply1 = redisCommand(c, "LREM group_list %s", group_name);
        freeReplyObject(reply1);
    }

    write(newfd, "Leave accept !\n", strlen("Leave accept !\n"));
    freeReplyObject(reply);
}

void remove_member(char *buf, char *usr_name, int newfd, redisContext *c) {
    redisReply *reply = NULL, *reply1 = NULL, *reply2 = NULL;
    char *group_name, *token;
    char not_found_list[MSG_MAX] = {}, not_in_list[MSG_MAX] = {}, send_list[MSG_MAX] = {};
    int count = 0, i = 0, j = 0, k = 0;
    int title = 1, first = 1, flag = 0, not_found = 0, not_in = 0, success = 0;
    const char delim[2] = " ";

    token = strtok(buf, delim);
    while (token){
        if (title)
            title = 0;
        else if (first){
            group_name = token;
            first = 0;
            reply = redisCommand(c, "LRANGE %s_group 0 -1", group_name);
            if (reply && reply->type == REDIS_REPLY_ARRAY){
                if (!reply->elements){
                    write(newfd, "Group Not Found !\n", strlen("Group Not Found !\n"));
                    freeReplyObject(reply);
                    return;
                }
                int owner = reply->elements - 1;
                if (strcmp(reply->element[owner]->str, usr_name)){
                    write(newfd, "You don't have permissions !\n", strlen("You don't have permissions !\n"));
                    freeReplyObject(reply);
                    return;
                }
            }
        }
        else{
            if (reply && reply->type == REDIS_REPLY_ARRAY){
                reply1 = redisCommand(c, "GET %s", token);
                if (reply1->type != REDIS_REPLY_STRING){ // user not found
                    strcat(not_found_list, token);
                    strcat(not_found_list, " ");
                    not_found = 1;
                    flag = 0;
                    freeReplyObject(reply1);
                    token = strtok(NULL, delim);
                    continue;
                }
                else{
                    for (i = 0; i < reply->elements; i++){
                        if (strcmp(token, reply->element[i]->str) == 0){ // remove user
                            reply2 = redisCommand(c, "LREM %s_group 0 %s", group_name, token);
                            strcat(send_list, token);
                            strcat(send_list, " ");
                            success = 1;
                            freeReplyObject(reply2);
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag){ // user not in
                        strcat(not_in_list, token);
                        strcat(not_in_list, " ");
                        not_in = 1;
                    }
                }
                flag = 0;
                freeReplyObject(reply1);
            }
        }
        token = strtok(NULL, delim);
    }
    if (reply && reply->type == REDIS_REPLY_ARRAY){
        if (not_found){
            strcat(not_found_list, "not found !\n");
            write(newfd, not_found_list, strlen(not_found_list));
        }
        if (not_in){
            strcat(not_in_list, "is not in group !\n");
            write(newfd, not_in_list, strlen(not_in_list));
        }
        if (success){
            strcat(send_list, "remove success !\n");
            write(newfd, send_list, strlen(send_list));
        }
    }
    freeReplyObject(reply);
}
