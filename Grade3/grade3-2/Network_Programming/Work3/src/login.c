#include "server_func.h"

char *create_account(redisContext *c, int newfd){
    static char num[3];
    memset(num, '\0', sizeof(num));

    write(newfd, "Create account or login again ? <1/2> : ", strlen("Create account or login again ? <1/2> : "));
    read(newfd, num, 3);
    size_t len = strlen(num);
    num[len - 1] = '\0';

    if(atoi(num) == 1){
        return usr_register(c, newfd);
    }
    else if(atoi(num) == 2){
        return login(c, newfd);
    }
}

char *login(redisContext *c, int newfd){
    redisReply *reply = NULL;
    static char name[25];
    static char password[20];
    memset(name, '\0', sizeof(name));
    memset(password, '\0', sizeof(password));

    write(newfd, "user_name: ", strlen("user_name: "));
    read(newfd, name, 25);
    write(newfd, "password: ", strlen("password: "));
    read(newfd, password, 20);

    size_t len1 = strlen(name), len2 = strlen(password);
    name[len1 - 2] = '\0';
    password[len2 - 2] = '\0';

    reply = redisCommand(c, "GET %s", name);
    if(reply == NULL || reply->type != REDIS_REPLY_STRING){
        write(newfd, "User not found !\n", strlen("User not found !\n"));
        freeReplyObject(reply);
        return  create_account(c, newfd);
    }

    if(strcmp(reply->str, password) == 0){
        freeReplyObject(reply); //add
        return name;
    }
    else{
        freeReplyObject(reply); //add
        write(newfd, "Password error !\n", strlen("Password error !\n"));
        return login(c, newfd);
    }
}

char *usr_register(redisContext *c, int newfd){
    redisReply *reply = NULL;
    static char name[25];
    static char password[20];
    memset(name, '\0', sizeof(name));
    memset(password, '\0', sizeof(password));

    write(newfd, "your user name: ", strlen("your user name: "));
    read(newfd, name, 25);
    write(newfd, "your password: ", strlen("your password: "));
    read(newfd, password, 20);

    size_t len1 = strlen(name), len2 = strlen(password);
    name[len1 - 2] = '\0';
    password[len2 - 2] = '\0';

    reply = redisCommand(c, "GET %s", name);
    if (reply != NULL && reply->type == REDIS_REPLY_STRING){
        write(newfd, "Username already exist !\n", strlen("Username already exist !\n"));
        freeReplyObject(reply);
        return usr_register(c, newfd);
    }
    else{
        reply = redisCommand(c, "SET %s %s", name, password);
        if (reply == NULL){
            write(newfd, "ERROR SET\n", strlen("ERROR SET\n"));
            return NULL;
        }
        freeReplyObject(reply);

        write(newfd, "Create scucess !\n", strlen("Create scucess !\n"));
        reply = redisCommand(c, "LPUSH user_list %s", name);
        freeReplyObject(reply); //add

        return login(c, newfd);
    }
}