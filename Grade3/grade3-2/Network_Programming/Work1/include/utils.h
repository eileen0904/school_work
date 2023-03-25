#define buf_MAX 5000
#define cmd_MAX 256
#define MAX 100


typedef struct command Command;
void execute();
char *read_command();
Command* insert(Command* COM, char** str, int count);
void FreeList();
Command* parse(char* buf);
void PrintList();
void handle_sigusr1(int signum);
void run(Command* CMD);
Command* DeleteCommand(Command* node);
int check();
int check_HasNumPipe();