#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#define MAX_ARG 30
#define MAX_CMD 10

void run(char **);
char** splitArg(char *);
char** splitCmd(char *);

int main()
{
    char* cmd;
    while (1) {
        // receive command from stdin
        printf("shell> ");
        scanf("%[^\n]", cmd);
        getchar();

        // check if user type command 'quit'
        if (!strcmp(cmd, "quit"))
            return 0;

        // split multiple command

            // split multiple arguments
            char** args = splitArg(cmd);

            // test run command
            run(args);
    }
    return 0;
}

void run(char** cmd)
{
    // test run command
    pid_t pid = fork();
    int status;
    if (pid == 0) {
        if (execvp(cmd[0], cmd) < 0) {
            printf("%s: command error!\n", cmd[0]);
        }
        // perror(cmd[0]);
    } else {
        wait(&status);
        // printf("\n");
    }
}

char** splitArg(char* cmd)
{
    int i;
    char* token;
    char** tokens = (char **) malloc(MAX_ARG * sizeof(char *));
    for (i = 0; token = strsep(&cmd, " "); i++) {
        // check if command contain more than one space or contain no character
        if (token != NULL && token[0] != 0 && token[0] != ' ') {
            tokens[i] = token;
        } else {
            i--;
        }
    }
    tokens[i++] = NULL;
    realloc(tokens, i);

    return tokens;
}

char** splitCmd(char* cmd)
{

}