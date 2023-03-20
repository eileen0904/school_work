#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define buf_MAX 5000
#define cmd_MAX 256
#define MAX 100

char buf[buf_MAX], argv[MAX][cmd_MAX];
char path[6] = {"./bin/"};
char bef_pipe[MAX][50];
int argc, pipe_count, n, tempN = 0, pipe_list[MAX];
pid_t parent;

void read_command() {
    memset(buf, 0, sizeof(buf));
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        printf("fgets error\n");
        return;
    }
    if (strcmp(buf, "\n") == 0)
        return;
    buf[strlen(buf) - 1] = '\0';
}

void parse(int num_pipe_out, int idx) {
    int i = 0, j = 0, flag = 1;
    for (i = 0; i < MAX; i++) {
        for (int j = 0; j < cmd_MAX; j++) {
            argv[i][j] = '\0';
        }
    }

    argc = 0, pipe_count = 0, n = 0, i = 0;
    if (num_pipe_out) {
        while (bef_pipe[idx][i] != '\0') {
            argv[0][i] = bef_pipe[idx][i];
            i++;
        }
        argc++;
    }
    for (i = 0; i < strlen(buf); i++) {
        if (buf[i] != ' ') {
            if (buf[i] == '|') {
                pipe_count++;
                argc++;
                flag = 1;
                j = 0;
            } else if (buf[i] >= '0' && buf[i] <= '9') {
                n = buf[i] - '0';
            } else {
                if (flag) {
                    for (int k = 0; k < 6; k++) {
                        argv[argc][k] = path[k];
                    }
                    flag = 0;
                    j = 6;
                }
                argv[argc][j] = buf[i];
                j++;
            }
        }
    }
}

void handle_sigusr1(int signum) {
    for (int i = 0; i < argc; i++)
        wait(NULL);
    tempN++;
    wait(NULL);
}

int run() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(0);
    } else if (pid == 0) {
        if (execlp(argv[0], argv[0], NULL) < 0) {
            char temp[10];
            int i = 6, j = 0;
            while (argv[0][i] != '\0' && argv[0][i] != '-') {
                temp[j++] = argv[0][i++];
            }
            temp[j] = '\0';
            char* s = temp;
            printf("Unknown command: [%s].\n", s);
            kill(getppid(), SIGUSR1);
            // return getppid();
            exit(0);
        }
    } else {
        // printf("parent pid:%d\n", getppid());
        // printf("pid:%d\n", getpid());
        signal(SIGUSR1, handle_sigusr1);
        wait(NULL);
        return 1;
    }
}

void run_pipe() {
    // fd odd:read(out) 0:STDIN
    // fd even:write(in) 1:STDOUT
    pid_t pid;
    int fd[argc * 2], j = 0;
    char* cmd = &argv[0][0];

    for (int i = 0; i < argc; i++) {
        if (pipe(fd + i * 2) < 0) {
            perror("pipe");
            exit(0);
        }
    }

    while (strlen(cmd)) {
        if ((pid = fork()) == -1) {
            perror("fork");
            exit(0);
        } else if (pid == 0) {
            if (strlen(cmd + cmd_MAX)) {  // if have next cmd
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
            if (execlp(cmd, cmd, NULL) < 0) {
                char* temp = cmd + 6;
                fprintf(stderr, "Unknown command: [%s].\n", temp);
                kill(getppid(), SIGUSR1);
                exit(0);
            }
        } else if (pid < 0) {
            perror("error");
            exit(EXIT_FAILURE);
        }
        cmd += cmd_MAX;
        j += 2;
    }
    signal(SIGUSR1, handle_sigusr1);
    parent = getpid();
    for (int k = 0; k < argc * 2; k++)
        close(fd[k]);
}

void env_parse(int mod) {
    char variable[10], value[20];
    int j = 0, k = 0, idx = 0;
    memset(variable, 0, 10);
    memset(value, 0, 20);

    if (mod == 1) {
        for (int i = 9; i < strlen(buf); i++) {
            variable[j++] = buf[i];
        }
        char* val = getenv(variable);
        if (val == NULL)
            printf("\n");
        else
            printf("%s\n", val);
        return;
    } else if (mod == 2) {
        for (int i = 7; i < strlen(buf); i++) {
            if (buf[i] == ' ') {
                idx = i;
                break;
            }
            variable[j++] = buf[i];
        }
        for (int i = idx + 1; i < strlen(buf); i++) {
            value[k++] = buf[i];
        }
        if (setenv(variable, value, 1) < 0) {
            perror("setenv: ");
        }
    }
}

void num_pipe(int num_pipe_out) {
    int N = n, i = 0, j = 0, k = 0;
    int bef_num = 0, isNumpipe = 0;
    char cmp[10];

    while (argv[0][i] != '\0') {
        bef_pipe[bef_num][i] = argv[0][i];
        i++;
    }
    pipe_list[bef_num] = n;
    bef_num++;

    while (1) {
        tempN = 0, k = 0, isNumpipe = 0, num_pipe_out = 0;

        for (i = 0; i < bef_num; i++) {  // check whther numpipe exist
            if (pipe_list[i] <= 0) {
                k++;
            }
        }
        if (k == bef_num)
            break;

        printf("%s", "1% ");
        read_command();

        if (strcmp(buf, "\n") == 0) {
            for (i = bef_num - 1; i >= 0; i--) {
                if (pipe_list[i] > 0) {
                    pipe_list[i]++;
                }
            }
            continue;
        }

        if (strcmp(buf, "quit") == 0)
            break;

        memset(cmp, 0, sizeof(cmp));
        strncpy(cmp, buf, 8);
        if (strcmp(cmp, "printenv") == 0) {
            env_parse(1);
            for (i = bef_num - 1; i >= 0; i--) {
                pipe_list[i]--;
            }
            continue;
        }

        memset(cmp, 0, sizeof(cmp));
        strncpy(cmp, buf, 6);
        if (strcmp(cmp, "setenv") == 0) {
            env_parse(2);
            for (i = bef_num - 1; i >= 0; i--) {
                pipe_list[i]--;
            }
            continue;
        }

        for (i = 0; i < strlen(buf); i++) {
            if ((buf[i] >= '0' && buf[i] <= '9') || buf[i] == '|') {
                isNumpipe = 1;
                break;
            }
        }
        if (isNumpipe) {
            parse(num_pipe_out, -1);
            while (argv[0][j] != '\0') {
                bef_pipe[bef_num][j] = argv[0][j];
                j++;
            }
            pipe_list[bef_num] = n;
            for (j = bef_num - 1; j >= 0; j--) {
                pipe_list[j]--;
            }
            bef_num++;
        } else {
            for (i = 0; i < bef_num; i++) {
                if (pipe_list[i] == 1) {
                    num_pipe_out = 1;
                    parse(num_pipe_out, i);
                    run_pipe();
                    if (parent) {
                        for (j = 0; j < argc + 1; j++) {
                            wait(NULL);
                        }
                    }
                    parent = 0;
                    break;
                }
            }
            if (!num_pipe_out) {
                num_pipe_out = 0;
                parse(num_pipe_out, -1);
                run();
            }
            for (i = bef_num - 1; i >= 0; i--) {
                pipe_list[i]--;
            }
            for (i = bef_num - 1; i >= 0; i--) {
                if (pipe_list[i] > 0) {
                    pipe_list[i] += tempN;
                }
            }
        }
    }
}

int main() {
    char cmp[10];
    int num_pipe_out = 0;
    setenv("PATH", "bin:.", 1);
    while (1) {
        printf("%s", "3% ");
        read_command();

        if (strcmp(buf, "\n") == 0)
            continue;
        if (strcmp(buf, "quit") == 0)
            break;

        memset(cmp, 0, sizeof(cmp));
        strncpy(cmp, buf, 8);
        if (strcmp(cmp, "printenv") == 0) {
            env_parse(1);
            continue;
        }

        memset(cmp, 0, sizeof(cmp));
        strncpy(cmp, buf, 6);
        if (strcmp(cmp, "setenv") == 0) {
            env_parse(2);
            continue;
        }

        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < 50; j++) {
                bef_pipe[i][j] = '\0';
            }
        }

        parse(num_pipe_out, -1);

        if (n) {
            num_pipe(num_pipe_out);
        } else {
            if (pipe_count == 0) {
                int cmd_notfound = run();
                if (cmd_notfound != 1)
                    exit(0);
            } else {
                run_pipe();
                if (parent) {
                    for (int i = 0; i < argc + 1; i++) {
                        wait(NULL);
                    }
                }
                parent = 0;
            }
        }
    }
}