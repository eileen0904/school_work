#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "utils.h"

#define buf_MAX 5000
#define cmd_MAX 256
#define MAX 100

int main() {
    setenv("PATH", "bin:.", 1);
    execute();
}